#include "PrintCommand.h"

/*
 * the exection of the print command.
 */
int PrintCommand::execute(list<string> params)
{
	int counter = 1;
	int flag=0;
	//erase print
	list<string> restOfLine;
	list<string>::iterator it = params.begin();
	it++;
	if(*it=="("){
       it++;
        counter++;
        flag=1;
	}
	string str = *(it);
	// if there is a text to print.
	if (str.begin()[0] == '"') { //if there is a " delete it.
		str.erase(str.begin() + 0); // delete the first ".
		str.erase(str.end() - 1); // delete the end ".
		cout << str << endl; // print the text that in " ".
		counter++; // count the var text string
		it++;
		if(flag){
		    counter++;
		}
	}
	else { // if the rest of the line is a expression.
		while (*it != "END") {
			restOfLine.push_back(*it); // push all the strings in a list
			counter++;
			it++;
		}
		// pop back "("
		if(flag){
		   restOfLine.pop_back();
		}
		Interpreter *inter = new Interpreter();
		inter->setVariables(*(this->symbolTable));
		Expression* expression = inter->interpret(restOfLine);
		double p = expression->calculate(); // calculate the expression.
		cout << p << endl; // print the expression.
	}
	return counter + 1;
}