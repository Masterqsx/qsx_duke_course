#include<sstream>
#include<climits>

using namespace std;

class Expression{
	public:
		virtual ~Expression(){}
		virtual std::string toString() const=0;
		virtual long evaluate() const = 0;
};

class MathExpression:public Expression{
	protected:
		string expre;long eval;
	public:
		MathExpression(long passing_num){
			stringstream strstream;
			strstream<<passing_num;
			expre=strstream.str();
			strstream.str("");
			strstream.clear();
			eval=passing_num;
		}
		
		MathExpression(Expression* lhs,Expression* rhs,char op){
			expre='('+lhs->toString()+' '+op+' '+rhs->toString()+')';
			if(op=='+')
				eval=lhs->evaluate()+rhs->evaluate();
			if(op=='-')
				eval=lhs->evaluate()-rhs->evaluate();
			if(op=='*')
				eval=lhs->evaluate()*rhs->evaluate();
			if(op=='/'){
				if(rhs->evaluate()==0)
					eval=LONG_MAX;
				else
					eval=lhs->evaluate()/rhs->evaluate();
			}
		}
		
		virtual std::string toString() const{
			return expre;
		}
		
		virtual long evaluate() const{
			return eval;
		}
};

class NumExpression:public MathExpression{
	public:
		NumExpression(long passing_num):MathExpression(passing_num){}
};

class PlusExpression:public MathExpression{
	public:
		PlusExpression(Expression * lhs, Expression * rhs):MathExpression(lhs,rhs,'+'){
			delete lhs;delete rhs;
		}	
};

class MinusExpression:public MathExpression{
	public:
		MinusExpression(Expression * lhs, Expression * rhs):MathExpression(lhs,rhs,'-'){
			delete lhs;delete rhs;
		}	
};

class TimesExpression:public MathExpression{
	public:
		TimesExpression(Expression * lhs, Expression * rhs):MathExpression(lhs,rhs,'*'){
			delete lhs;delete rhs;
		}	
};

class DivExpression:public MathExpression{
	public:
		DivExpression(Expression * lhs, Expression * rhs):MathExpression(lhs,rhs,'/'){
			delete lhs;delete rhs;
		}	
};
