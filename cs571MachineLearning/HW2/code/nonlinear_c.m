function y = nonlinear_c(theta, x, cons)
    y = 1 ./ (exp(-1 * (theta' * x + cons)) + 1);
    y = y';
end