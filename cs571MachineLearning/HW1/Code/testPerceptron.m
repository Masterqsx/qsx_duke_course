clear
clc
x1 = [-1,1;0,-1;1.5,1];
for i=1:3
    x12(i,:)=x1(i,:)/norm(x1(i,:));
end
y1 = [1,-1,1];
x3 = [-1,1;0,-1;10,1];
for i=1:3
    x32(i,:)=x3(i,:)/norm(x3(i,:));
end
x4 = [-1,1;0,-1;10/10,1/10];
x5 = [-1,1;0,-1;2,1;-1.5,-1];
y5 = [1,-1,1,-1];

figure;
hold on;
xlim([-2,2]);
ylim([-2,2]);
[w, n] = myPerceptron(x4, y1, 1, 0, 0);
grid on;
axis equal
xlabel('x');
ylabel('y');
title('Progression of the plane start with x_2 when x_3 changed');