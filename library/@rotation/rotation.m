classdef rotation
    properties
        q   = [1 0 0 0]';
        seq   = 'ypr';
        isdeg = true;
        from  = 1;
        to    = 2;
        desc;
        do_qnorm=true;
        versioninfo
    end
    properties (Dependent = true)
        ypr
        rpy
        b
        ctm
        ang
        israd
    end

    %access methods
    methods
        
        function israd=get.israd(obj)
            israd=~obj.isdeg;
        end
        
        function ypr=get.ypr(obj)
            rpy=obj.q2ea;
            ypr=rpy([3 2 1]);
            if obj.isdeg
                ypr=ypr*180/pi;
            end
        end
        
        function rpy=get.rpy(obj)
            rpy=obj.q2ea;
            if obj.isdeg
                rpy=rpy*180/pi;
            end
        end
        
        function b=get.b(obj)
            b=obj.q2b;
            if obj.isdeg
                b=b*180/pi;
            end
        end        
        
        function ang=get.ang(obj)
            ang=norm(obj.b);
        end
        
        function ctm=get.ctm(obj)
            ctm=obj.q2c;
        end        
        
    end
    
    %set methods
    methods
        
        function obj=set.isdeg(obj,isdeg)
           obj.isdeg=isdeg;
           if isdeg
               %display('Units in Degs');
           else
               %display('Units in Rads');
           end
        end
        
        function obj=set.israd(obj,israd)
           obj.isdeg=~israd;
        end
        
        function obj=set.ypr(obj,ypr)
            rpy=ypr([3 2 1]);
            if obj.isdeg
                rpy=rpy*pi/180;
            end
            obj.q=obj.ea2q(rpy,obj.seq);
        end
        
        function obj=set.rpy(obj,rpy)
            if obj.isdeg
                rpy=rpy*pi/180;
            end
            obj.q=obj.ea2q(rpy,obj.seq);
        end
        
        function obj=set.b(obj,b)
            if obj.isdeg
                b=b*pi/180;
            end
            obj.q=obj.b2q(b);
        end
        
        function obj=set.q(obj,q)
            if obj.do_qnorm
                q=obj.qnorm(q);
            else
                q=q;
            end
            if q(1)<0
                q=q*-1;
            end
            obj.q=q;
        end
        
        function obj=set.ctm(obj,ctm)
            obj.q=obj.c2q(ctm);
        end
        
        function varargout=subsref(obj,s)
            if length(obj)==1 | (length(s)~=1 | ~strcmp(s(1).type,'.'))
                [varargout{1:nargout}]=builtin('subsref',obj,s);
                return 
            end
            alldata=[];
            for i=1:length(obj)
                data=[];
                data=obj(i).(s(1).subs);
                if size(data,1)>1 & size(data,2)<=1
                    data=data';
                end
                if ~ischar(data)
                    alldata=[alldata;data];
                else
                    alldata={alldata
                             data};
                end
            end
            
            varargout={alldata};
            
        end
    end

    methods
        function roto=rotation(rot,type,isdegin)
            switch nargin
                case 0                
                case 1
                    if isa(rot,'rotation')
                        roto=rot;                    
                    elseif length(rot)==4
                        roto=rotationconstructor(roto,rot,'quat',true);
                    elseif isequal(size(rot), [3 1]) | isequal(size(rot),[1 3])
                        roto=rotationconstructor(roto,rot,'ea',true);
                    elseif isequal(size(rot),[3 3])
                        roto=rotationconstructor(roto,rot,'ctm',true);
                    end
                case 2
                    roto=rotationconstructor(roto,rot,type,true);
                case 3
                    roto=rotationconstructor(roto,rot,type,isdegin);
            end
            
            
        end

    end            
end

function roto=rotationconstructor(roto,rot,type,isdegin)
%   roto=rotation;       
    
%     roto.isdeg=true;
%     roto.seq='ypr';
%     roto.ctm=eye(3);

   roto.versioninfo='$Id: rotation.m,v 1.9 2009/12/02 17:28:05 deschetn Exp $';

    if isempty(rot)
        return
    end
    
    if roto.isdeg~=isdegin
        roto.isdeg=isdegin;
    end
    if rstrcmp('quat',type)
        roto.q=rot;       
    elseif rstrcmp('ea',type)
        if roto.isdeg
            rot=rot*pi/180;
        end
        roto.q=roto.ea2q(rot([3 2 1]),roto.seq);
    elseif rstrcmp('ctm',type)
        roto.q=roto.c2q(rot);
    end        

end
