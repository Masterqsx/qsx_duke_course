#include <stdio.h>
#include <stdlib.h>

class MyClass {
private:
  int x;
  int y;
public:
  void setPoints(int newx, int newy) { 
    x = newx;
    y = newy;
  }
  void doStuff(const MyClass & p);
  int computeSomething() const {
    return x *3 + y -2;
  }
};

void printMessage(const MyClass * m1) {
  printf("%p has %d\n", m1, m1->computeSomething());
}
void MyClass::doStuff(const MyClass & p) {
  x = p.y + 3;
  y = p.x - 4;
  printMessage(this);
  printMessage(&p);
}

int main(void) {
  MyClass a;
  MyClass b;
  MyClass c;
  a.setPoints(1,1);//a(x:1 y:1)
  b.setPoints(22,40);//b(x:22 y:40)
  c.setPoints(9,3);//c(x:9 y:3)
  a.doStuff(b);//a(x:43 y:18) out: 3*43+18-2 3*22+40-2
  b.doStuff(c);//b(x:6 y:5)   out: 3*6+5-2   3*9+3-2
  c.doStuff(a);//c(x:21 y:39) out: 3*21+39-2 3*43+18-2
  return EXIT_SUCCESS;
}
