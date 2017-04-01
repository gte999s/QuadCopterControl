function q=ea2q(obj,angles,sequence);
% 
% EA2Q forms an equivalent quaternion (q) for the given Euler 
% angles (angles) and rotation sequence (sequence).
%
%  usage: q=ea2q(angles,sequence)
%                
%  Angles is a 3x1 vector of rotation angles (radians)
%  Sequence is a string of three characters that may have any
%  of the following forms: 'rpy','ryp','pry','pyr','yrp','ypr'
%  where r,p,y stand for roll, pitch, and yaw.
%
%  Transformation matrix usage:
%
%        Vb = C * Vn
%        In = C' * Ib * C
%
%    so C = Cbn
%       q = qnb
%
%       where q(1)   = scalar part
%             q(2-4) = vector part
%
%
%
if abs(abs(angles(2))-pi/2)<.1
    warning('near pitch singularity');
end
c=ea2c(angles,sequence);
q=obj.c2q(c);
%

function c=ea2c(angles,sequence)
% 
% EA2C forms a coordinate transformation matrix (c) out of the
% given Euler angles (angles) and rotation sequence (sequence).
%
%  usage: c=ea2c(angles,sequence)
%                
%  Angles is a 3x1 vector of rotation angles (radians)
%  Sequence is a string of three characters that may have any
%  of the following forms: 'rpy','ryp','pry','pyr','yrp','ypr'
%  where r,p,y stand for roll, pitch, and yaw.
%
%  Transformation matrix usage:
%
%         C = Cbn
%
%        Vb = C * Vn
%        In = C' * Ib * C
%
if nargin == 1
  sequence = 'ypr';
end
%
c=zeros(3,3);
%
s1=sin(angles(1)); c1=cos(angles(1));
s2=sin(angles(2)); c2=cos(angles(2));
s3=sin(angles(3)); c3=cos(angles(3));
%
if (sequence == 'rpy')
  c(1,1)=c2*c3;
  c(1,2)=c1*s3+s1*s2*c3;
  c(1,3)=s1*s3-c1*s2*c3;
  c(2,1)=-c2*s3;
  c(2,2)=c1*c3-s1*s2*s3;
  c(2,3)=s1*c3+c1*s2*s3;
  c(3,1)=s2;
  c(3,2)=-s1*c2;
  c(3,3)=c1*c2;
elseif (sequence == 'ryp')
  c(1,1)=c2*c3;
  c(1,2)=c2*s3*c1+s2*s1;
  c(1,3)=c2*s3*s1-s2*c1;
  c(2,1)=-s3;
  c(2,2)=c3*c1;
  c(2,3)=c3*s1;
  c(3,1)=s2*c3;
  c(3,2)=s2*s3*c1-c2*s1;
  c(3,3)=s2*s3*s1+c2*c1;
elseif (sequence == 'pry')
  c(1,1)=c3*c2+s3*s1*s2;
  c(1,2)=s3*c1;
  c(1,3)=s3*s1*c2-c3*s2;
  c(2,1)=c3*s1*s2-s3*c2;
  c(2,2)=c3*c1;
  c(2,3)=s3*s2+c3*s1*c2;
  c(3,1)=c1*s2;
  c(3,2)=-s1;
  c(3,3)=c1*c2;
elseif (sequence == 'pyr')
  c(1,1)=c3*c2;
  c(1,2)=s3;
  c(1,3)=-c3*s2;
  c(2,1)=s1*s2-c1*s3*c2;
  c(2,2)=c1*c3;
  c(2,3)=c1*s3*s2+s1*c2;
  c(3,1)=s1*s3*c2+c1*s2;
  c(3,2)=-s1*c3;
  c(3,3)=c1*c2-s1*s3*s2;
elseif (sequence == 'yrp')
  c(1,1)=c2*c3-s2*s1*s3;
  c(1,2)=c2*s3+s2*s1*c3;
  c(1,3)=-s2*c1;
  c(2,1)=-c1*s3;
  c(2,2)=c1*c3;
  c(2,3)=s1;
  c(3,1)=s2*c3+c2*s1*s3;
  c(3,2)=s2*s3-c2*s1*c3;
  c(3,3)=c2*c1;
elseif (sequence == 'ypr')
  c(1,1)=c2*c3;
  c(1,2)=c2*s3;
  c(1,3)=-s2;
  c(2,1)=s1*s2*c3-c1*s3;
  c(2,2)=s1*s2*s3+c1*c3;
  c(2,3)=s1*c2;
  c(3,1)=c1*s2*c3+s1*s3;
  c(3,2)=c1*s2*s3-s1*c3;
  c(3,3)=c1*c2;
else
  error('ea2c: Don''t have that sequence');
end
%
