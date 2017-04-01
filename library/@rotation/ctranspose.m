function obj=ctranspose(obj)
obj.q=obj.qinv(obj.q);

tfrom=obj.from;
obj.from=obj.to;
obj.to=tfrom;
