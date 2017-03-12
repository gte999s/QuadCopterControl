classdef sensorFusionEKFSysObj < matlab.System
    % Untitled3 Add summary here
    %
    % This template includes the minimum set of functions required
    % to define a System object with discrete state.

    % Public, tunable properties
    properties

    end

    properties(Nontunable)
        Avar        = single(ones(3,1))  % Accelerometer variance
        Mvar        = single(ones(3,1))  % Magnetometer variance
        Gvar        = single(ones(3,1))  % Gyroscope variance
        Ts = 1/200; % Operating Rate of the Filter
    end

    properties(DiscreteState)
        x_apriori     % Apriori State Estimate
        x_aposteriori % Aposteriori state estimate
        P_apriori     % Apriori Error Covariance Measurement
        P_aposteriori % Aposteriori Error Covariance Measurement
        z_apriori     % Apriori Measurement Prediction
        z_aposteriori % Aposteriori Measurement 
        A             % State update jacobian
        H             % Mesurement update jacobian
        Q             % Proccess Noise
        R             % Measurement Noise
    end

    % Pre-computed constants
    properties(Access = private)

    end

    methods(Access = protected)
        function setupImpl(o)
            % Perform one-time calculations, such as computing constants
            o.x_apriori       = complex(single([0 0 0 1 0 0 0 0 0 0]'));
            o.x_aposteriori   = complex(single([0 0 0 1 0 0 0 0 0 0]'));
            o.z_apriori       = complex(single(ones(6,1)));
            o.z_aposteriori   = complex(single(ones(6,1)));
            o.P_apriori       = complex(single(eye(10)));
            o.P_aposteriori   = complex(single(eye(10)));  
            o.Q               = complex(single(zeros(10)));
            o.R               = complex(single(zeros(6)));
            o.A               = o.Q;
            o.H               = complex(single(zeros(6,10)));
            
        end
        
        function [qNB,aBias,mBias] = stepImpl(o,a,w,m,g,h)
            %% [qNB,aBias,mBias] = stepImpl(o,a,w,m,g,h)
            %     a = acceleration in body
            %     w = angulare rate in body
            %     m = magnetometer in body
            %     g = acceleration vector due to gravity in Inertial
            %     h = magnetometer vector in Inertial
            %   qNB = rotation from Inertial to Body
            % aBias = estimated bias in Accelerometer
            % mBias = estimated biase in Magnetometer
            %% Update Q and R
            o.updateNoise;
            
            %% Update Apriori Estimate and State Update Jacobian
            o.x_apriori = o.getStateUpdate(w,o.x_aposteriori);
            o.A = o.getJacobian(w,o.x_apriori,true);
            
            %% Update apriori Error Covariance Estimate
            o.P_apriori = o.A*o.P_aposteriori*o.A' + o.Q;
            
            %% Get apriori measurement and Measurement jacobian
            o.z_apriori=o.getMeasurementUpdate([g;h],o.x_apriori);
            o.H        =o.getJacobian([g;h],o.x_apriori,false);
            
            %% Update Kalman gain
            K = (o.P_apriori*o.H') / (o.H*o.P_apriori*o.H' + o.R);
            
            %% Update aposteriori state estimate with measurement
            o.z_aposteriori = [a;m];
            o.x_aposteriori = o.x_apriori + K *(o.z_aposteriori-o.z_apriori);
            o.x_aposteriori(1:4)=o.x_aposteriori(1:4)....
                                 ./norm(o.x_aposteriori(1:4)); % norm Q            
            
            %% Update apostriori error covariance estimate
            o.P_aposteriori = (eye(size(K,1)) - K*o.H) * o.P_apriori;
            
            %% Ouput best estimates
            qNB=o.x_aposteriori(1:4);
            aBias=o.x_aposteriori(5:7);
            mBias=o.x_aposteriori(8:10);
            
        end
        
        function resetImpl(o)
            % Initialize / reset discrete-state properties
        end
    end
    
    methods(Access = protected)
        %% Kalman Update Methods        
        function xNew=getStateUpdate(o,w,x)
            %% Update kalman state
            OMEGA=(.5*[o.skew(w)  w
                              -w'        0]);
            xNew=blkdiag(expm(OMEGA*o.Ts),eye(3),eye(3))*x;
            xNew(1:4)=xNew(1:4)./norm(xNew(1:4));
            
        end
        
        function zNew=getMeasurementUpdate(o,gh,x)
            %% Update measurement estimate
            b_C_n = o.getC(x(1:4));
            zNew  = blkdiag(b_C_n,b_C_n)*gh;
            
        end
        
        function jacobian = getJacobian(o,input,x,doState)
            if doState
                jacobian=single(zeros(size(x,1),size(x,1)));
            else
                jacobian=single(zeros(size(input,1),size(x,1)));
            end
            for i=1:length(x)
                dx=100*eps(x(i));
                xtemp=x;
                xtemp(i)=xtemp(i)+dx*1i;
                if doState
                    jacobian(:,i)=imag(o.getStateUpdate(input,xtemp))./dx;
                else
                    jacobian(:,i)=imag(o.getMeasurementUpdate(input,xtemp))./dx;
                end
            end
        end
        
        function updateNoise(o)
           %% Update Q based on apostori state
           QqChi=[o.skew(o.x_apriori(1:3)) + o.x_apriori(4)*eye(3)
                    -o.x_apriori(1:3)'];
           o.Q=blkdiag((o.Ts/2)^2*QqChi*diag(o.Gvar)*(QqChi'),...
                        diag(o.Avar),diag(o.Mvar));
           o.R=blkdiag(diag(o.Avar),diag(o.Mvar));
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
