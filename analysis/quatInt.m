function main
imu=blowupData;


q=[0 0 0 1]';
theta=[0 0 0]';
qs=zeros(imu.gyro.Length,4);
thetas=qs(:,1:3);
time=zeros(imu.gyro.length,1);
for i=1:imu.gyro.length
    w=imu.gyro.data(i,:)';
    q=qint(q,w*2,1/200);
    qs(i,:)=q;
    time(i)=i*1/200;
    
    theta=theta+w.*(1/200);
    thetas(i,:)=theta;
end

figure;
subplot(211);
plot(time,qs);
subplot(212);
plot(time,thetas*180/pi);

function q=qint(q,w,Ts)
wX=[0       -w(3)   w(2)
    w(3)    0       -w(1)
    -w(2)   w(1)    0];
OMEGA=.5*[wX  w
          -w' 0];
      
q=expm(OMEGA*Ts)*q;
q=q./norm(q);