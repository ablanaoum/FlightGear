//
// Created by abla on 08/01/2020.
//

#include "DefineVarCommand.h"

using namespace std;

/*
 * the execution of the DefineVarCommand that define the var due to the
 * strings (input) we get, and insert it to the symbolTable that have a whole variables.
 */
int DefineVarCommand::execute(list<string> params) {
	map<string, Var>::iterator itSymbol;
	list <string> s;
	int size;
	int counter = 1;
	string type;
	//itSymbol = symbolTable->begin();
	list<string>::iterator itList = params.begin();
	//the first is var
	string inputvar = *(++itList);

	unsigned int i = 0;
	//checking the validty of the var name.
	if (inputvar[i] >= '0' && inputvar[i] <= '9') {
		throw("ERROR");
	}

	i++;
	while (inputvar[i] != '=' && i < inputvar.length()) {
		if (!(inputvar[i] >= '0' && inputvar[i] <= '9') && !(inputvar[i] >= 'a' && inputvar[i] <= 'z')
			&& !(inputvar[i] >= 'A' && inputvar[i] <= 'Z')) {
			throw("ERROR");
		}

		i++;
	}
	counter++;
	
	if (*(++itList) != "END") {
		//save -> or -< or =
		size = (*itList).size();
		i = 0;
		type = *itList;
		counter++;
		//// saving the expression in a list
		list<string>::iterator tempit;
		++itList;
		tempit = itList;
		//catch the rest of the sentance
		while (*(tempit) != "END") {
			s.push_back(*tempit);
			counter++;
			tempit++;
		}
	}
	Var newV;
	// if there is a "->" or "<-" then we take the path.
	if (type == "->" || type == "<-") {
		//in the path there is a sim word before.
		if ((*itList) == "sim") {
			itList++;
			if ((*itList)[0] == 34 && (*itList)[(*itList).size() - 1] == 34) {
				// take the path without the " in the beginning and in the end
				string temp;
				i = 0;
				size = (*itList).size();
				//take all the path char by char.
				for (int j = 1; j < size - 1; j++) {
					temp += ((*itList)[j]);
					i++;
				}
				//update the fields of the struscts of each variable.
				newV.sim = temp;
				newV.type = type;
				newV.value=0;
			}
		}
		else {
			throw("ERROR");
		}
	}

	//if there is a "=" in the line then there ia expression.
	else if (type == "=") {
		Interpreter* inter = new Interpreter();
		inter->setVariables(*(this->symbolTable));
		Expression* expression = inter->interpret(s);
		double p = expression->calculate(); // calculate the expression.
		newV.value = p; //update the value in the var struct.

	}

	//then there is just a var.
	else {
		newV.type = "";
	}
	//update the appropriate struct to the var.

	symbolTable->insert(std::pair<std::string, Var>(inputvar, newV));
	return counter + 1;
}