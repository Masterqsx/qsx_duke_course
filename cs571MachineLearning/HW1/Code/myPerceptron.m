function [w, n] = myPerceptron(x, y, display, offset, error)
   [len,wid] = size(x);
   flag = 1;
   w = zeros(1,wid);
   n = 0;
   count = 0;
   if (display == 1)
       plot(0, 0, 'rx');
       text(0.1, -0.1,['[',num2str(0),', ',num2str(0),']']);
   end
   while(flag > error & count < 4000)
       flag = 0;
       count = count + 1;
       for i = 1:len
           ii = mod((i - 1 + offset),len)+1;
           if y(ii)*(w*x(ii,:)')<=0
               w = w + y(ii) * x(ii,:);
               if (display ~= 2)
                    n = n + 1;
               end
               if (display == 1)
                   w
                   p1 = [-w(2), w(1)];
                   p2 = -p1;
                   xx = linspace(0,w(1));
                   yy = linspace(0,w(2));
                   px = linspace(p1(1), p2(1));
                   py = linspace(p1(2), p2(2));
                   plot(xx,yy,'--');
                   plot(px,py);
                   plot(w(1),w(2),'rx');
                   text(w(1)+0.1,w(2)-0.1,['[',num2str(w(1)),', ',num2str(w(2)),']']);
               end
               
               flag = flag + 1;
           end
       end
       if (display == 2)
         n = [n,flag];
       end
   end
end