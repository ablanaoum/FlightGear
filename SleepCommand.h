//
// Created by abla on 09/01/2020.
//


#ifndef SLEEP_COMMAND_H
#define SLEEP_COMMAND_H
#include "Command.h"
#include <map>
#include <list>
#include "Expression.h"
#include "ExpressionInterpreter.h"
#include "ConnectCommand.h"
#include <chrono>
#include <thread>

/*
* SleepCommand Class.
stop the tread according to the token time.
*/
class SleepCommand : public Command {
private:
	map<string, Var> *symbolTable;

public:
	SleepCommand(map<string, Var> *symTable) :symbolTable(symTable) {}
	
	int execute(list<string> params) {
		list<string> restof;
		try {
			Interpreter* interpreter = new Interpreter();
			interpreter->setVariables(*this->symbolTable);
			list<string>::iterator it = params.begin();
			it++;
			//take the rest of the strings till the end.
			while (*it != "END") {
				restof.push_back(*it);
				it++;
			}
			Expression* expression = interpreter->interpret(restof);
			double value = expression->calculate();
			//sleep 
			this_thread::sleep_for(chrono::milliseconds((long)value));
			//delete interpreter;
		}
		catch (const char* e) {
			throw("invalid argument to sleep function");
		}


		return (int)restof.size() + 2;
	}
};
#endif //SLEEPCOMMAND_H
