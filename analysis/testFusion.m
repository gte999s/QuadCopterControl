function [qs,biasA,biasM,Ps]=testFusion
Ts=1/200;
imu=blowupData;

[aVar,aMean]=getStat(imu.accel,.1,2);
[mVar,mMean]=getStat(imu.mag,.1,2);
[gVar,gMean]=getStat(imu.gyro,.1,1);

gVar=gVar;
P=eye(4)*2e-3;
x=zeros(4,1);
x(4)=1;
qtemp=[0 0 0 1]';
qs=nan(imu.accel.length/2,4);
qints=qs;
Ps=nan(imu.accel.length/2,4*4);
time=nan(imu.accel.length/2,1);
bs=nan(imu.accel.length/2,3);
vs=bs;
vsNorm=vs(:,1);
count=1;
for index=10:1:(imu.accel.length-1)
    w=imu.gyro.Data(index,:)'-gMean;
    a=imu.accel.Data(index,:)';
    R=blkdiag(diag(aVar),diag(mVar));
    m=imu.mag.Data(floor(index/2),:)';
    
    QqChi=[skew(x(1:3)) + x(4)*eye(3)
            -x(1:3)'];
    Q=blkdiag((Ts/2)^2*QqChi*diag(gVar)*(QqChi'));
    
    [x,P]=sensorFusionEKF(Ts,w,a,m,x,P,Q,R,aMean./norm(aMean),mMean);
    
    qs(count,:)=x(1:4);
    qtemp=qint(qtemp,w*4,Ts);
    qints(count,:)=qtemp;
    Ps(count,:)=P(:);
    bs(count,:)=q2b(x(1:4));
    vs(count,:)=(q2c(x(1:4)))*[0;0;1];
    vsNorm(count)=norm(vs(count,:));
    time(count)=imu.gyro.Time(index);
    count=count+1;
end

% figure;
% subplot(311);
% plot(time,qs);grid on;
% subplot(312);
% plot(time,biasA);grid on;
% subplot(313);
% plot(time,biasM);grid on;
% linkaxes(findobj(gcf,'type','axes'),'x');
figure;
plot(time,Ps);grid on;

figure;
subplot(311);
imu.accel.plot;hold all;
plot(time,vs,'--');
subplot(312);
imu.mag.plot;

subplot(313);
imu.gyro.plot;
linkaxes(findobj(gcf,'type','axes'),'x');

figure;
subplot(211);
plot(time,qs);
subplot(212);
plot(time,qints,'--');grid on;


function q=qint(q,w,Ts)
wX=[0       -w(3)   w(2)
    w(3)    0       -w(1)
    -w(2)   w(1)    0];
OMEGA=.5*[wX  w
          -w' 0];
      
q=expm(OMEGA*Ts)*q;
q=q./norm(q);
    
function s=skew(w)
s=[0       -w(3)   w(2)
    w(3)    0       -w(1)
    -w(2)   w(1)    0];

function [v,m]=getStat(data,start,stop)
b=data.Time > start & data.Time < stop;
v=var(data.Data(b,:))';
m=mean(data.Data(b,:))';



