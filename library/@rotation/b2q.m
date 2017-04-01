function q=b2q(obj,b)
%
% B2Q converts a Bortz vector (b) to a quaternion (q).
%
%  usage: q=b2q(b)
%
%     q = qnb
%
%     where q(1)   = scalar part
%           q(2-4) = vector part
%
qs=1.0;
qv=[0;0;0];
%
theta=sqrt(b(1)*b(1)+b(2)*b(2)+b(3)*b(3));
%
if (theta > 1.0e-20)
  ux=b(1)/theta;
  uy=b(2)/theta;
  uz=b(3)/theta;
  ct=cos(theta/2);
  st=sin(theta/2);
  qs=ct;
  qv=st*[ux;uy;uz];
end
%
q=[qs;qv];
%
