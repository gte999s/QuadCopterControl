function c=q2c(obj);
% Q2C computes a transformation matrix (c) from the given
% quaternion (q).
%
%  usage: c=q2c(q)
%
% Transformation matrix is of the form:
%
%     C = Cbn
%     q = qnb
%
%     where q(1)   = scalar part
%           q(2-4) = vector part
%
%    Vb = C * Vn
%    Ib = C'* In * C
%
q=obj.q;
q0=q(1); % scalar part
q1=q(2);
q2=q(3);
q3=q(4);
%
q1q2=q1*q2;
q1q3=q1*q3;
q1q0=q1*q0;
q2q3=q2*q3;
q2q0=q2*q0;
q3q0=q3*q0;
q1q1=q1*q1;
q2q2=q2*q2;
q3q3=q3*q3;
%
c(1,1)=1.0-2.0*(q2q2+q3q3);
c(1,2)=2.0*(q1q2+q3q0);
c(1,3)=2.0*(q1q3-q2q0);
c(2,1)=2.0*(q1q2-q3q0);
c(2,2)=1.0-2.0*(q1q1+q3q3);
c(2,3)=2.0*(q2q3+q1q0);
c(3,1)=2.0*(q1q3+q2q0);
c(3,2)=2.0*(q2q3-q1q0);
c(3,3)=1.0-2.0*(q1q1+q2q2);
%
