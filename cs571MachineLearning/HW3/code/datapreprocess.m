function D = datapreprocess(data)
    C = table2cell(data);
    [h,w] = size(C);
    for j = 1:w
        for i = 1:h
            if (C{i,j} == 'x')
                D(i,j) = -1;
            elseif (C{i,j} == 'o')
                D(i,j) = 1;
            elseif (C{i,j} == 'b')
                D(i,j) = 0;
            elseif (sum(C{i,j} == 'positive') == 8)
                D(i,j) = 1;
            elseif (sum(C{i,j} == 'negative') == 8)
                D(i,j) = 0;
            end
        end
    end
end