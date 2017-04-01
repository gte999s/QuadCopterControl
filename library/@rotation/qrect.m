function q=qrect(obj,q);
%
% q = [ q1, q2, q3, q4 ]' 
%
%  where q(1)   = scalar part
%        q(2-4) = vector part
%
% q = qnb -> Cbn
%
if (q(1) < 0.0),
  q=-q;
end
%
