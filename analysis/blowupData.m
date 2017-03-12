function imu=blowupData
data=load('imuData');
data=data.data.signals.values;

l=size(data,1);
time=(0:(l*4-1))*.001;
accel=timeseries(...
[...  
    reshape(data(:,1:4)',1,l*4)
    reshape(data(:,5:8)',1,l*4)
    reshape(data(:,9:12)',1,l*4)
    ]',time);

gyro=timeseries(...
[...  
    reshape(data(:,13:16)',1,l*4)
    reshape(data(:,17:20)',1,l*4)
    reshape(data(:,21:24)',1,l*4)
    ]',time);

time=(0:(l*2-1))*.002;
mag=timeseries(...
[...  
    reshape(data(:,25:26)',1,l*2)
    reshape(data(:,27:28)',1,l*2)
    reshape(data(:,29:30)',1,l*2)
    ]',time);

imu.accel=accel;
imu.gyro=gyro;
imu.mag=mag;