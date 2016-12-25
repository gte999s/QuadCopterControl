function [x,P]=sensorFusionEKF(w,a,m,x_last,P_last,Q,R)
g=[0;0;1];
h=[100;0;100];
% Update Apriori Estimate and State Update Jacobian
[x_apriori,A]=complexStepDeriv(@stateUpdateFcn,x_last,w);

% Update apriori Error Covariance Estimate
P_apriori = A*P_last*A' + Q;

% Get apriori measurement and Measurement jacobian
[z_apriori,H]=complexStepDeriv(@measurementFcn,x_apriori,g,h);

% Update Kalman gain
K = (P_apriori*H') / (H*P_apriori*H' + R);

% Update aposteriori state estimate with measurement
z = [a;m];
x = x_apriori + K *(z-z_apriori);
x(1:4)=x(1:4)./norm(x(1:4));

% Update apostriori error covariance estimate
P = (eye(size(K,1)) - K*H) * P_apriori;


function xNew=stateUpdateFcn(x,w)
Ts=5/1000;
q=x(1:4);

wX=[0       -w(3)   w(2)
    w(3)    0       -w(1)
    -w(2)   w(1)    0];
OMEGA=.5*[wX  w
          -w' 0];
Z=zeros(3);
I=eye(3);
xNew=[exp(OMEGA*Ts) Z Z
      Z             I Z
      Z             Z I] * x;
xNew(1:4)=xNew(1:4)./norm(xNew(1:4));


function zNew=measurementFcn(x,g,h)
b_C_n=getC(x(1:4));
Z=zeros(3);
z=[b_C_n  Z
   Z      b_C_n]*[g,h];
zNew=z+x(5:10);


function C=getC(q)
s=q.^2;
C=[s(1)-s(2)-s(3)+s(4)        2*(q(1)*q(2)+q(3)*q(4))    2*(q(1)*q(3)-q(2)*q(4))
   2*(q(1)*q(2)-q(3)*q(4))   -s(1)+s(2)-s(3)+s(4)        2*(q(2)*q(3)+q(4)*q(1))
   2*(q(1)*q(3)+q(2)*q(4))    2*(q(2)*q(3)-q(4)*q(1))   -s(1)-s(2)+s(3)+s(4)];
   
C=(1/sqrt(norm(q(1:3))^2+q(4)^2))*C;


function [xnew,jacobian]=complexStepDeriv(fcn,varargin)
xnew=feval(fcn,varargin{:});

jacobian=zeros(size(xnew,1),size(x,2));

for i=1:length(x)
    dx=100*eps(x(i));
    xtemp=x;
    xtemp(i)=xtemp(i)+dx*1i;
    jacobian(:,i)=imag(feval(fcn,xtemp,w))/dx;
end
    
