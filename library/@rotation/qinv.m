function q=qinv(obj,q);
%
% q = [ q1, q2, q3, q4 ]' 
%
%   where q(1)   = scalar part
%         q(2-4) = vector part
%
% q = qnb -> Cbn
%
q(1)= q(1);
q(2)=-q(2);
q(3)=-q(3);
q(4)=-q(4);
%
