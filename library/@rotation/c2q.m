function q=c2q(obj,c);
% C2Q computes a quaternion (q) from the given transformation
% matrix (c).
%
%  usage: q=c2q(c)
%
% Transformation matrix is of the form:
%
%     C = Cbn
%
%    Vb = C * Vn
%    Ib = C'* In * C
%
%     q = qnb
%
%     where q(1)   = scalar part
%           q(2-4) = vector part
%
q=zeros(4,1);
r=[c(1,1),c(2,2),c(3,3),c(1,1)+c(2,2)+c(3,3)];
[rmax,k]=max(r);
%
if k==1,
  q(2)=sqrt(1.0+2.0*r(1)-r(4))/2.0;
  s=4.0*q(2);
  q(3)=(c(1,2)+c(2,1))/s;
  q(4)=(c(3,1)+c(1,3))/s;
  q(1)=(c(2,3)-c(3,2))/s;
elseif k==2,
  q(3)=sqrt(1.0+2.0*r(2)-r(4))/2.0;
  s=4.0*q(3);
  q(4)=(c(2,3)+c(3,2))/s;
  q(1)=(c(3,1)-c(1,3))/s;
  q(2)=(c(1,2)+c(2,1))/s;
elseif k==3,
  q(4)=sqrt(1.0+2.0*r(3)-r(4))/2.0;
  s=4.0*q(4);
  q(1)=(c(1,2)-c(2,1))/s;
  q(2)=(c(3,1)+c(1,3))/s;
  q(3)=(c(2,3)+c(3,2))/s;
elseif k==4,
  q(1)=sqrt(1.0+r(4))/2.0;
  s=4.0*q(1);
  q(2)=(c(2,3)-c(3,2))/s;
  q(3)=(c(3,1)-c(1,3))/s;
  q(4)=(c(1,2)-c(2,1))/s;
end;
%
q=obj.qnorm(q);
q=obj.qrect(q);
%
