function p = histTest(x, para)
      if (x > max(para(:, 2)))
          x = max(para(:, 2));
      elseif (x < min(para(:, 2)))
          x = min(para(:, 2));
      end
      p = para(discretize(x,para(:, 2)) , 1) + eps;
end