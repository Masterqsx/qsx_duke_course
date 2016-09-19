#ifndef __FUNCTION_H__
#define __FUNCTION_H__
template<typename R, typename A> 
class Function {
public:
  virtual R invoke(A arg) = 0;
  virtual ~Function() {}
};


class SinFunction : public Function<int, int>{
public:
	int n;
	SinFunction():n(0){}
	virtual int invoke(int arg) {
		n++;
		return 10000000*(sin(arg/100000.0)-0.5);
	}
};
#endif
