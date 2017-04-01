function q=qmult(obj,q1,q2);
%
% For two rotations
%
%   q1 = qna corresponds to Can for use with Va = Can * Vn
%   q2 = qab corresponds to Cba for use with Vb = Cba * Va
%
% the total rotation will be
%
%    q = qnb = qna * qab corresponding to Cbn = Cba * Can
%                        for use with Vb = Cbn * Vn
%
% q = [ q1, q2, q3, q4 ]' 
%
%  where q(1) = scalar part
%        q(2-4) = vector part
%
q=zeros(4,1);
%
q(1)=q1(1)*q2(1)-q1(2)*q2(2)-q1(3)*q2(3)-q1(4)*q2(4);
q(2)=q1(2)*q2(1)+q1(1)*q2(2)-q1(4)*q2(3)+q1(3)*q2(4); 
q(3)=q1(3)*q2(1)+q1(4)*q2(2)+q1(1)*q2(3)-q1(2)*q2(4);
q(4)=q1(4)*q2(1)-q1(3)*q2(2)+q1(2)*q2(3)+q1(1)*q2(4); 
%
q=obj.qnorm(q);
%
