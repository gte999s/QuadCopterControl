function angles=q2ea(obj);
% 
% Q2EA forms Euler angles (angles) from a given quaternion (q)
% and for the specified rotation sequence (sequence).
%
%  usage: angles=q2ea(q,sequence)
%
%  Sequence is a string of three characters that may have any
%  of the following forms: 'rpy','ryp','pry','pyr','yrp','ypr'
%  where r,p,y stand for roll, pitch, and yaw.
%
%  Transformation matrix usage:
%
%        Vb = C * Vn
%        In = C' * Ib * C
%
%   so C = Cbn 
%      q = qnb
%
%     where q(1)   = scalar part
%           q(2-4) = vector part
%
%
%
sequence=obj.seq;
c=obj.q2c;
angles=c2ea(c,sequence);
%
function angles=c2ea(c,sequence);
% 
% C2EA forms Euler angles (angles) from a given coordinate 
% transformation matrix (c) and rotation sequence (sequence).
%
%  usage: angles=c2ea(c,sequence)
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
th1=0.0; th2=0.0; th3=0.0;
%
if nargin == 1
  sequence = 'ypr';
end
%
if (sequence == 'rpy')
  th1=atan2(-c(3,2),c(3,3) );
  th2= safe_asin( c(3,1) );
  th3=atan2(-c(2,1),c(1,1) );
elseif (sequence == 'ryp')
  th1=atan2( c(2,3),c(2,2) );
  th2=atan2( c(3,1),c(1,1) );
  th3= safe_asin(-c(2,1) );
elseif (sequence == 'pry')
  th1= safe_asin(-c(3,2) );
  th2=atan2( c(3,1),c(3,3) );
  th3=atan2( c(1,2),c(2,2) );
elseif (sequence == 'pyr')
  th1=atan2(-c(3,2),c(2,2) );
  th2=atan2(-c(1,3),c(1,1) );
  th3= safe_asin( c(1,2) );
elseif (sequence == 'yrp')
  th1= safe_asin( c(2,3) );
  th2=atan2(-c(1,3),c(3,3) );
  th3=atan2(-c(2,1),c(2,2) );
elseif (sequence == 'ypr')
 th1=atan2( c(2,3),c(3,3) );
  th2= safe_asin(-c(1,3) );
  th3=atan2( c(1,2),c(1,1) );
else
  error('c2ea: Don''t have that sequence');
end
%
angles=[th1;th2;th3];


function x=safe_asin(x)

    if x>1
        x=1;
    elseif x<-1
        x=-1;
    end
    
    x=asin(x);
