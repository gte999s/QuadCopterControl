classdef sensorFusionEKFSysObj < matlab.System
    % Untitled3 Add summary here
    %
    % This template includes the minimum set of functions required
    % to define a System object with discrete state.

    % Public, tunable properties
    properties

    end

    properties(Nontunable)
        Avar        = single(ones(3,1))         % Accelerometer variance
        AvarDisable = single(repmat(1e4,3,1));  % Accelerometer variance to disable accel measurements
        accelMagDevThresh = single(.1)          % Allowed deviaton from unit norm to use accel measurement
        Mvar        = single(ones(3,1))         % Magnetometer variance
        Gvar        = single(ones(3,1))         % Gyroscope variance
        MagScaleFactor = single(100)            % Scale factor to numerically scale magnetometer readings    
        Pinit          = single(ones(7,1))
        Ts = single(1/200);                     % Operating Rate of the Filter
    end

    properties(DiscreteState)
        x_apriori     % Apriori State Estimate
        x_aposteriori % Aposteriori state estimate
        P_apriori     % Apriori Error Covariance Measurement
        P_aposteriori % Aposteriori Error Covariance Measurement
        A             % State update jacobian
        H             % Mesurement update jacobian
        Q             % Proccess Noise
        R             % Measurement Noise
        MvarScaled    % Scaled magnetometer variance
        useAccel      % Flag, 1 = Accel measurements are being used, 0 = Accel meaurements are not being used
    end

    % Pre-computed constants
    properties(Access = private)

    end

    methods(Access = protected)
        function setupImpl(o)
            % Perform one-time calculations, such as computing constants
            o.x_apriori       = complex(single([0 0 0 1 0 0 0 ]'));
            o.x_aposteriori   = complex(single([0 0 0 1 0 0 0 ]'));
            o.P_apriori       = complex(single(eye(7)));
            o.P_aposteriori   = complex(diag(o.Pinit));            
            o.Q               = complex(single(zeros(7)));
            o.R               = complex(single(zeros(6)));
            o.A               = o.Q;
            o.H               = complex(single(zeros(6,7)));
            o.useAccel        = true;
            o.MvarScaled      = o.Mvar./o.MagScaleFactor^2;
        end
        
        function [qNB,mBias,P,useAccel] = stepImpl(o,a,w,m,g,h)
            %% [qNB,aBias,mBias] = stepImpl(o,a,w,m,g,h)
            %     a = acceleration in body
            %     w = angulare rate in body
            %     m = magnetometer in body
            %     g = acceleration vector due to gravity in Inertial
            %     h = magnetometer vector in Inertial
            %   qNB = rotation from Inertial to Body
            % aBias = estimated bias in Accelerometer
            % mBias = estimated biase in Magnetometer
            
            %% Normalize Accelerometer Vector
            a_norm=a./norm(a);
            
            %% Scale Magnetometer reading
            m=m./o.MagScaleFactor;
            h=h./o.MagScaleFactor;
                        
            %% Update Q and R
            o.updateNoise(a,a_norm);
            
            %% Update Apriori Estimate and State Update Jacobian
            o.x_apriori = o.getStateUpdate(w,o.x_aposteriori);
            o.A = o.getJacobian(w,o.x_apriori,true);
            
            %% Update apriori Error Covariance Estimate
            o.P_apriori = o.A*o.P_aposteriori*o.A' + o.Q;
            
            %% Get apriori measurement and Measurement jacobian
            z_apriori=o.getMeasurementUpdate([g;h],o.x_apriori);
            o.H        =o.getJacobian([g;h],o.x_apriori,false);                        
            
            %% Update Kalman gain
            K = (o.P_apriori*o.H') / (o.H*o.P_apriori*o.H' + o.R);
            
            %% Update aposteriori state estimate with measurement
            z_aposteriori = [a_norm;m];
            o.x_aposteriori = o.x_apriori + K *(z_aposteriori-z_apriori);
            o.x_aposteriori(1:4)=o.x_aposteriori(1:4)....
                                 ./norm(o.x_aposteriori(1:4)); % norm Q            
            
            %% Update apostriori error covariance estimate
            o.P_aposteriori = (eye(size(K,1)) - K*o.H) * o.P_apriori;
            
            %% Ouput best estimates
            qNB=real(o.x_aposteriori([4 1:3])); % put scalar first to be compatible with other tools
            mBias=real(o.x_aposteriori(5:7));
            
            ds=o.getDiscreteStateImpl;
            P=diag(real(ds.P_aposteriori));
            useAccel=ds.useAccel;
            
        end
        
        function resetImpl(o)
            % Initialize / reset discrete-state properties
        end

        function ds = getDiscreteStateImpl(obj)
            % Return structure of properties with DiscreteState attribute
            ds.x_apriori = obj.x_apriori;
            ds.x_aposteriori = obj.x_aposteriori;
            ds.P_apriori = obj.P_apriori;
            ds.P_aposteriori = obj.P_aposteriori;
            ds.A = obj.A;
            ds.H = obj.H;
            ds.Q = obj.Q;
            ds.R = obj.R;
            ds.useAccel = obj.useAccel;
        end



    end
    
    methods(Access = protected)
        %% Kalman Update Methods        
        function xNew=getStateUpdate(o,w,x)
            %% Update kalman state
            OMEGA=(.5*[o.skew(w)        w
                             -w'        0]);
            xNew=blkdiag(expm(OMEGA*o.Ts),eye(3))*x;
            xNew(1:4)=xNew(1:4)./norm(xNew(1:4));
            
        end
        
        function zNew=getMeasurementUpdate(o,gh,x)
            %% Update measurement estimate
            b_C_n = o.getC(x(1:4));
            zNew  = blkdiag(b_C_n,b_C_n)*gh+[0;0;0;x(5:7)];
            
        end
        
        function jacobian = getJacobian(o,input,x,doState)
            if doState
                jacobian=single(zeros(size(x,1),size(x,1)));
            else
                jacobian=single(zeros(size(input,1),size(x,1)));
            end
            for i=1:length(x)
                dx=10000*eps(x(i));
                xtemp=x;
                xtemp(i)=xtemp(i)+dx*1i;
                if doState
                    jacobian(:,i)=imag(o.getStateUpdate(input,xtemp))./dx;
                else
                    jacobian(:,i)=imag(o.getMeasurementUpdate(input,xtemp))./dx;
                end
            end
        end
        
        function updateNoise(o,a,a_norm)
           %% Schedule the accel variance to gate when accel measurements are used
           % i.e. if the body is under heavy accel, rely on gyro and mag
           if abs(dot(a,a_norm)-1) > o.accelMagDevThresh
               o.useAccel = false;
           else
               o.useAccel = true;
           end
            
           %% Update Q based on apostori state
           QqChi=[o.skew(o.x_apriori(1:3)) + o.x_apriori(4)*eye(3)
                    -o.x_apriori(1:3)'];
           o.Q=blkdiag((o.Ts/2)^2*QqChi*diag(o.Gvar)*(QqChi'),...
                        o.Ts*diag(o.MvarScaled));
           if o.useAccel
               o.R=blkdiag(diag(o.Avar),diag(o.MvarScaled));
           else
               o.R=blkdiag(diag(o.AvarDisable),diag(o.MvarScaled));
           end
           
        end
    end
    
    methods(Access = protected, Static=true)
       %% Helper Functions
       function s=skew(w)
           s=[0       -w(3)   w(2)
               w(3)    0       -w(1)
               -w(2)   w(1)    0];
       end
       
       function C=getC(q)
           s=q.^2;
           C=[s(1)-s(2)-s(3)+s(4)        2*(q(1)*q(2)+q(3)*q(4))    2*(q(1)*q(3)-q(2)*q(4))
               2*(q(1)*q(2)-q(3)*q(4))   -s(1)+s(2)-s(3)+s(4)        2*(q(2)*q(3)+q(4)*q(1))
               2*(q(1)*q(3)+q(2)*q(4))    2*(q(2)*q(3)-q(4)*q(1))   -s(1)-s(2)+s(3)+s(4)];
           
           C=(1/sqrt(norm(q(1:3))^2+q(4)^2))*C;
       end

       
        
        
    end
end
