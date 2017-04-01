function disp(obj)
if obj.isdeg
    unit='deg';
else
    unit='rad';
end

if ~isempty(obj.desc)
    display(obj.desc)
end

display(['From: ' num2str(obj.from) ' To: ' num2str(obj.to) ]);
display('--------------------------------');
display(sprintf('%11s \t %11s',['YPR(' unit ')'],['Bortz(' unit ')']));
display(sprintf('% 11.3f \t % 11.3f',obj.ypr(1),obj.b(1)));
display(sprintf('% 11.3f \t % 11.3f',obj.ypr(2),obj.b(2)));
display(sprintf('% 11.3f \t % 11.3f',obj.ypr(3),obj.b(3)));