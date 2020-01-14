#include "ExpressionInterpreter.h"

using namespace std;

/*/
 * the calculate function that calculate the expression due to the operration.
 */
double Plus::calculate() {
	return (ex1->calculate() + ex2->calculate());
	}
double Minus::calculate() {
	return (ex1->calculate() - ex2->calculate());
	}
double Mul::calculate() {
	return (ex1->calculate() * ex2->calculate());
	}
double Div::calculate() {
	return (ex1->calculate() / ex2->calculate());
}

double Value::calculate() {
	return this->d;
}
double Variable::calculate() {
    return value;
}
double Bigger::calculate() {
    if(ex1->calculate()>ex2->calculate()){
        return 1;
    }else{
        return 0;
    }
}
double Smaller::calculate() {
    if(ex1->calculate()<ex2->calculate()){
        return 1;
    }else{
        return 0;
    }
}
double BiggerOrequal::calculate() {
    if(ex1->calculate()>=ex2->calculate()){
        return 1;
    }else{
        return 0;
    }
}
double SmallerOrequal::calculate() {
    if(ex1->calculate()<=ex2->calculate()){
        return 1;
    }else{
        return 0;
    }
}
double Equal::calculate() {
    if(ex1->calculate()==ex2->calculate()){
        return 1;
    }else{
        return 0;
    }
}
double NotEqual::calculate() {
    if(ex1->calculate()!=ex2->calculate()){
        return 1;
    }else{
        return 0;
    }
}

/*
 * set the value of the Vaiable .
 */
void Variable::setValue(double d)
{
		this->value = d;
}


/*
 * operaors used with variable
 */
Variable& Variable::operator++() {
	(this->value)++;
	return *this;
}
Variable& Variable::operator--() {
	(this->value)--;
	return *this;
}
Variable& Variable::operator--(int) {
    Variable* v=this;
	--(this->value);
	return *v;
}
Variable& Variable::operator++(int) {
    Variable* v=this;
    ++(this->value);
    return *v;
}
Variable& Variable::operator+=(double d) {
	(this->value) += d;
	return *this;
}
Variable& Variable::operator-=(double d) {
	(this->value) -= d;
	return *this;
}

/*
 * get the name of the variable
 */
string Variable::getName() {
	return this->name;
}

double UPlus::calculate() {
	return (ex->calculate());
}
double UMinus::calculate() {
	return ((-1)*ex->calculate());
}

/*
 * the constructor of the interpreter insert the operator preferation
 */
Interpreter::Interpreter() {
    map<string, int> operators;
    this->operatorsMap = operators;
    operatorsMap["^"] = 1;
    operatorsMap["+"] = 1;
    operatorsMap["=="]=1;
    operatorsMap["!="]=1;
    operatorsMap[">="]=1;
    operatorsMap["<="]=1;
    operatorsMap[">"]=1;
    operatorsMap["<"]=1;
    operatorsMap["-"] = 1;
    operatorsMap["*"] = 2;
    operatorsMap["/"] = 2;
}

/*
 * the function get a string and return if it is a operator or not.
 */
bool Interpreter::isOperator(string ope) {
	map<string, int>::iterator operatorIt;
	for (operatorIt = this->operatorsMap.begin();operatorIt != this->operatorsMap.end();++operatorIt) {
		if (ope == operatorIt->first) {
			return true;
		}
	}
	return false;
}

/*
 * the function get a string and return if it is a variable or not.
 */
bool Interpreter::isVariables(string var) {
	list<Variable*>::iterator listIt;
	for(listIt = (this->variables).begin(); listIt != (this->variables).end(); ++listIt){
		if (var == (*listIt)->getName()) {
			return true;
		}
	}
	return false;
}

/*
 * the function get a string and return if it is a number or not.
 */
bool Interpreter::isNumber(string s) {
	unsigned int index=0;
	int count = 0;
	for (index=0;index<s.length(); index++){
		if (((s[index]) < '0' || (s[index]) > '9') && s[index] != '.') {
			return false;
		}
		if ((s[index]) == '.') {
			count++;
		}
		if (count > 1) {
			return false;
		}
	}
	return !s.empty();
}

/*
 * the function get a map of the variables defined in the input file(program),and
 * insert it as a Variable object that is a expression .
 */
void Interpreter::setVariables(map<string,Var> varsmap){
    map<string, Var>::iterator it;
    bool flag=false;
    for (it = varsmap.begin(); it != varsmap.end(); ++it)
    {
        flag=false;
        string name=it->first;
        double value=(it->second).value;
        list<Variable*>::iterator f=this->variables.begin();
        if(!this->variables.empty()) {
            for (f = this->variables.begin(); f != this->variables.end(); ++f) {
                Variable *v = *f;
                if (v->getName() == it->first) {
                    (*f)->setValue(value);
                    flag = true;
                }
            }
        }
       if(!flag){
           Variable *v = new Variable(name, value);
           (this->variables).push_back(v);

       }
    }
}

/*
 * func get the name of the var and return it as Variable object .
 */
Variable* Interpreter::returnVar(string var) {
	list<Variable*>::iterator itList = (this->variables).begin();
	while (itList != (this->variables).end()) {
		if (var == (*itList)->getName()) {
			return *itList;
		}
		itList++;
	}
    return nullptr;
}

/*
 * the funtion use a shunting yard algorithm that solve an expression .
 */
Expression * Interpreter::interpret(list<string> expressionIn)
{
	stack<string> operatorsStack;
	queue<string> resultQueue;
	//list<string> expr = (this->checkValidity(expressionIn));
	list<string>::iterator it = expressionIn.begin();
	list<string>::iterator tmp = expressionIn.begin();
	while (it != expressionIn.end()) {
		string currentExpr = *it;
		tmp = it;
		//check if number or variable push to Resultqueue .
		if (isNumber(currentExpr) || isVariables(currentExpr)) {
			resultQueue.push(currentExpr);
		}
		//if it is ( push to operator stack
		else if (currentExpr == "(") {
			operatorsStack.push(currentExpr);
		}
		//if it is ) pop each elemnt in the operatorStack to put to resultQueue.
		else if (currentExpr == ")") {
			while (operatorsStack.top() != "(") {
				resultQueue.push(operatorsStack.top());
				operatorsStack.pop();
			}
			operatorsStack.pop();
		}
		//else we get operator and if there is operator on the stack,
		// check the favorite operation betwen it and the previous.
		else if (!operatorsStack.empty()) {
			if (operatorsStack.top() != "(") {
				if (operatorsMap[currentExpr] < operatorsMap[operatorsStack.top()]) {
					while (!operatorsStack.empty()) {
						resultQueue.push(operatorsStack.top());
						operatorsStack.pop();
					}
				}
				//if there is - operotor put 0 before .
				if ((currentExpr == "-" && (it == expressionIn.begin() || *(--tmp) == "("))) {
					resultQueue.push("0");
				}
				operatorsStack.push(currentExpr);
			}
			else {
				if ((currentExpr == "-" && (it == expressionIn.begin() || *(--tmp) == "("))) {
					resultQueue.push("0");
				}
				operatorsStack.push(currentExpr);

			}
		}
		//if it is operator push to operator stack
		else if (isOperator(currentExpr)) {
			if ((currentExpr == "-" && (it == expressionIn.begin() || *(--tmp) == "("))) {
				resultQueue.push("0");
			}
			operatorsStack.push(currentExpr);
		}

		it++;
	}
	//put all the rest operator in the resultQueue
	while (!operatorsStack.empty()) {
		resultQueue.push(operatorsStack.top());
		operatorsStack.pop();
	}
	stack<Expression*> tempStack;
	while (!resultQueue.empty()) {
	    //while there is a number or variable push to the temp stack
	    //that will help us to make the last expression.
		while ((isNumber(resultQueue.front()) || isVariables(resultQueue.front()))&&
            !resultQueue.empty()){
			if (isNumber(resultQueue.front())) {
				tempStack.push(new Value(std::stod(resultQueue.front())));
			}
			else if (isVariables(resultQueue.front())) {
				tempStack.push(returnVar(resultQueue.front()));
			}
            resultQueue.pop();
		}
        string op="";
        if(!resultQueue.empty()) {
            op = resultQueue.front();
            resultQueue.pop();
        }
		Expression *exp1 = tempStack.top();
		tempStack.pop();
        Expression *exp2;
		if(!tempStack.empty()) {
            exp2 = tempStack.top();
            tempStack.pop();
        }else{
            tempStack.push(exp1);
            continue;
		}
		//check the operator to create the appropiate operation .
		if (op == "+")
			tempStack.push(new Plus(exp2, exp1));
		if (op == "-")
			tempStack.push(new Minus(exp2, exp1));
		if (op == "*")
			tempStack.push(new Mul(exp2, exp1));
		if (op == "/")
			tempStack.push(new Div(exp2, exp1));
        if (op == ">=")
            tempStack.push(new BiggerOrequal(exp2, exp1));
        if (op == "<=")
            tempStack.push(new SmallerOrequal(exp2, exp1));
        if (op == "==")
            tempStack.push(new Equal(exp2, exp1));
        if (op == "!=")
            tempStack.push(new NotEqual(exp2, exp1));
        if (op == ">")
            tempStack.push(new Bigger(exp2, exp1));
        if (op == "<")
            tempStack.push(new Smaller(exp2, exp1));
	}
	return tempStack.top();
}

