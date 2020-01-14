#ifndef PROJECT_EXPRESSIONINTERPRETER_H
#define PROJECT_EXPRESSIONINTERPRETER_H
#include "Expression.h"
#include "ConnectCommand.h"
#include <iostream>
#include <map>
#include <string>
#include <list>
#include <stack>
#include <queue>

using namespace std;
/*
 * the binaryOperator is a type of expression
 */
class BinaryOperator : public Expression {
protected:
	Expression* ex1;
	Expression* ex2;
public:
	BinaryOperator(Expression* e1, Expression* e2) {
    this->ex1=e1;
    this->ex2=e2;
}
	virtual double calculate() = 0;
	virtual ~BinaryOperator() {}

};

/*
 * the operators is a tyoe of binaryOpeator takes two expression, and calculate them.
 */
class Plus : public BinaryOperator {
public:
	Plus(Expression* e1, Expression* e2) : BinaryOperator(e1, e2) {}
	double calculate();
};
class Minus :public BinaryOperator {
public:
	Minus(Expression* e1, Expression* e2) : BinaryOperator(e1, e2) {}
	double calculate();
};
class Mul :public BinaryOperator {
public:
	Mul(Expression* e1, Expression* e2) : BinaryOperator(e1, e2) {}
	double calculate();
};
class Div :public BinaryOperator {
public:
	Div(Expression* e1 , Expression* e2) : BinaryOperator(e1, e2) {}
	double calculate();
};
class BiggerOrequal:public BinaryOperator{
public:
    BiggerOrequal(Expression* e1 , Expression* e2) : BinaryOperator(e1, e2) {}
    double calculate();
};
class SmallerOrequal:public BinaryOperator{
public:
    SmallerOrequal(Expression* e1 , Expression* e2) : BinaryOperator(e1, e2) {}
    double calculate();
};

class Equal:public BinaryOperator{
public:
    Equal(Expression* e1 , Expression* e2) : BinaryOperator(e1, e2) {}
    double calculate();
};
class NotEqual:public BinaryOperator{
public:
    NotEqual(Expression* e1 , Expression* e2) : BinaryOperator(e1, e2) {}
    double calculate();
};
class Bigger:public BinaryOperator{
public:
    Bigger(Expression* e1 , Expression* e2) : BinaryOperator(e1, e2) {}
    double calculate();
};
class Smaller:public BinaryOperator{
public:
    Smaller(Expression* e1 , Expression* e2) : BinaryOperator(e1, e2) {}
    double calculate();
};


class Value : public Expression {
	double d;
public:
	Value(double v) : d(v) {};
	double calculate();
};

class Variable : public Expression {
protected:
	double value;
	string name;
public:
	Variable(string VarName, double d) : value(d) ,name(VarName)  {}
	void setValue(double d);
	double calculate();
	Variable& operator ++();
	Variable& operator++(int);
	Variable& operator --();
	Variable& operator--(int);
	Variable& operator +=(double d);
	Variable& operator -=(double d);
	string getName();
};

class UnaryOperator : public Expression {
protected:
	Expression* ex;
public:
	UnaryOperator(Expression* e) : ex(e) {};
	virtual double calculate() = 0;

};
class UPlus : public UnaryOperator {
public:
	UPlus(Expression* e) : UnaryOperator(e) {};
	double calculate();
};
class UMinus : public UnaryOperator {
public:
	UMinus(Expression* e) : UnaryOperator(e) {};
	double calculate();
};

/*
 * the interpreter takes an string of expression and convert it to Expression Object.
 * and the setVariable func that get a map include the variable we want
 * and insert them to the list<Variable*> .
 */
class Interpreter {
private:
	map <string, int> operatorsMap;
	list <Variable*> variables;
public:
	Interpreter();
	void setVariables(map<string,Var> varsmap);
	//void setVariables(string variablesString);
	Variable * returnVar(string var);
	bool isOperator(string op);
	bool isNumber(string s);
	bool isVariables(string var);
	Expression* interpret(list<string> expr);
	list<string> checkValidity(string exp);
	//~Interpreter();
};
#endif