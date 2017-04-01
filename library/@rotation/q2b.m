function b=q2b(obj)
%
% Q2B converts a quaternion (q) to a Bortz vector (b).
%
%  usage: b=q2b(q)
%
%     q = qnb
%
%     where q(1)   = scalar part
%           q(2-4) = vector part
%
q=obj.q;
b=zeros(3,1);
%
if (q(1) < 0.0)
  q=-q;
end
%
qs=q(1);
qv=[q(2);q(3);q(4)];
%
theta=2*acos(qs);
%
if (theta > 1.0e-20) 
  st=sin(theta/2);
  ux=qv(1)/st;
  uy=qv(2)/st;
  uz=qv(3)/st;
  b=theta*[ux;uy;uz];
end
%
