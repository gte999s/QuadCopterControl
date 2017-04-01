function plot(obj)
init=eye(3);
  
final=obj*init;

figure;
plot3([0 init(1,1)],[0 init(2,1)],[0 init(3,1)],'.-',...
      [0 init(1,2)],[0 init(2,2)],[0 init(3,2)],'.-',...
      [0 init(1,3)],[0 init(2,3)],[0 init(3,3)],'.-');



hold on
plot3([0 final(1,1)],[0 final(2,1)],[0 final(3,1)],'--.',...
      [0 final(1,2)],[0 final(2,2)],[0 final(3,2)],'--.',...
      [0 final(1,3)],[0 final(2,3)],[0 final(3,3)],'--.');
  
  if obj.ang~=0
      b=obj.b./obj.ang;
      b=b*1;
      plot3([0 b(1)],[0 b(2)],[0 b(3)],'.-k')
  end
  
  xlim([-1 1])
  ylim([-1 1]);
  zlim([-1 1]);
  xlabel('x');
  ylabel('y');
  zlabel('z');
  title(['YPR:  ' num2str(obj.ypr') ]);
  grid on;
  view(134.5,28);
  legend('x','y','z','location','northeast','orientation','horizontal');