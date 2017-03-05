function [alpha, label, data, bias] = my_SVMtrain(data, label, kernel)
    [n, p] = size(data);
    H = (label * label') .* kernel(data, data);
    f = -1.* ones(n, 1);
    A = -1 .* eye(n);
    b = zeros(n, 1);
    Aeq = label';
    beq = 0;
    alpha = quadprog(H,f,A,b,Aeq,beq);
    for i = 1 : length(alpha)
        if (alpha(i) < 0.0001)
            alpha(i) = 0;
        end
    end
    bias = 0;
%     H0_index = find(label ~= 1);
%     H1_index = find(label == 1);
%     H0_index = H0_index(1);
%     H1_index = H1_index(1);
    support_H0 = -realmax;
    support_H1 = realmax;
    for i = 1 : length(alpha)
        if label(i) == 1
            support_H1 = min(support_H1, (alpha .* label)' *  kernel(data, data(i, :)));
        end
        if label(i) ~= 1
            support_H0 = max(support_H0, (alpha .* label)' *  kernel(data, data(i, :)));
        end
    end
    bias = -(support_H1 + support_H0) / 2;
end