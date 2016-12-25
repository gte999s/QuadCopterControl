function main

imu=blowupData;

aVar=getVar(imu.accel,.1,2);
mVar=getVar(imu.mag,.1,2);
R=blkdiag(diag(aVar),diag(mVar));
Q=zeros(10);
P=eye(10);

m=zeros(3,1);
for index=1:imu.accel.length
    w=imu.gyro.Data(i,:)';
    a=imu.accel.Data(i,:)';
    if mod(index,2)==0
        m=imu.mag.Data(index/2,:)';
    end
    
    [x,P]=sensorFusionEKF(w,a,m,x,P,Q,R);
    
end
    

function v=getVar(data,start,stop)
b=data.Time > start & data.Time < stop;
v=var(data.Data(b,:))';