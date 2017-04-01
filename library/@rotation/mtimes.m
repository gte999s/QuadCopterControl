function a=mtimes(left,right)
if isa(right,'rotation') && isa(left,'rotation')
    %   left = qna corresponds to Can for use with Va = Can * Vn
    %   right = qab corresponds to Cba for use with Vb = Cba * Va
    %
    % the total rotation will be
    %
    %    q = qnb = qna * qab corresponding to Cbn = Cba * Can
    %                        for use with Vb = Cbn * Vn
    a=left;
    a.q=left.qmult(left.q,right.q);
    a.from=right.from;
    a.to=left.to;
elseif size(right,1)==3
    a=left.ctm*right;
elseif size(right,1)==4
    a=zeros(size(right));
    for i=1:size(right,2)
        a(:,i)=left.qmult(left.q,right(:,i));
    end
elseif isa(right,'rotation') && isa(left,'double') && size(left,1)==4
    a=zeros(size(left));
    for i=1:size(left,2)
        a(:,i)=right.qmult(left(:,i),right.q);
    end    
end
