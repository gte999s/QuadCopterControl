function rss=main(data)
for i=1:size(data,1)
    rss(i)=norm(data(i,:));
end