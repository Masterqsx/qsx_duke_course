function confidence = my_SVMpredict(alpha, train_y, train_data, bias, data, kernel)
    confidence = ((alpha .* train_y)' *  kernel(train_data, data))' + bias;
end