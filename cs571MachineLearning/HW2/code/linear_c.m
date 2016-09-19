function y = linear_c(theta, x, cons)
    y = theta' * x + cons;
    y = y';
end