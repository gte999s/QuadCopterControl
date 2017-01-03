function [x,P]=sensorFusionEKF(Ts,w,a,m,x_last,P_last,Q,R,g,h)

% Update Apriori Estimate and State Update Jacobian
[x_apriori,A]=stateUpdateFcn(Ts,x_last,w,true);

% Update apriori Error Covariance Estimate
P_apriori = A*P_last*A' + Q;

% Get apriori measurement and Measurement jacobian
[z_apriori,H]=measurementFcn(x_apriori,g,h,true);

% Update Kalman gain
K = (P_apriori*H') / (H*P_apriori*H' + R);

% Update aposteriori state estimate with measurement
z = [a;m];
x = x_apriori + K *(z-z_apriori);
x(1:4)=x(1:4)./norm(x(1:4));

% Update apostriori error covariance estimate
P = (eye(size(K,1)) - K*H) * P_apriori;


function [xNew,jacobian]=stateUpdateFcn(Ts,x,w,doJacobian)

wX=[0       -w(3)   w(2)
    w(3)    0       -w(1)
    -w(2)   w(1)    0];
OMEGA=.5*[wX  w
          -w' 0];

xNew=blkdiag(expm(OMEGA*Ts))*x;
xNew(1:4)=xNew(1:4)./norm(xNew(1:4));

if ~doJacobian
    return;
end

jacobian=zeros(size(xNew,1),size(xNew,1));

for i=1:length(x)
    dx=100*eps(xNew(i));
    xtemp=xNew;
    xtemp(i)=xtemp(i)+dx*1i;
    jacobian(:,i)=imag(stateUpdateFcn(Ts,xtemp,w,false))./dx;
end


function [zNew,jacobian]=measurementFcn(x,g,h,doJacobian)
b_C_n=getC(x(1:4));

zNew=blkdiag(b_C_n,b_C_n)*[g;h];

if ~doJacobian
    return;
end

jacobian=zeros(size(zNew,1),size(x,1));

for i=1:length(x)
    dx=100*eps(x(i));
    xtemp=x;
    xtemp(i)=xtemp(i)+dx*1i;
    jacobian(:,i)=imag(measurementFcn(xtemp,g,h,false))./dx;
end


function C=getC(q)
s=q.^2;
C=[s(1)-s(2)-s(3)+s(4)        2*(q(1)*q(2)+q(3)*q(4))    2*(q(1)*q(3)-q(2)*q(4))
   2*(q(1)*q(2)-q(3)*q(4))   -s(1)+s(2)-s(3)+s(4)        2*(q(2)*q(3)+q(4)*q(1))
   2*(q(1)*q(3)+q(2)*q(4))    2*(q(2)*q(3)-q(4)*q(1))   -s(1)-s(2)+s(3)+s(4)];
   
C=(1/sqrt(norm(q(1:3))^2+q(4)^2))*C;



    
