function y=signal_image_generator(n,Es)
    s=sqrt(Es/n);
    y=eye(n)*s;
    