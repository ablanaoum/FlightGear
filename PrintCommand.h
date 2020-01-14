#ifndef NEWPR_PRINT_H
#define NEWPR_PRINT_H
#include <iostream>
#include <map>
#include "Command.h"
#include "ConnectCommand.h"
#include "Expression.h"
#include "ExpressionInterpreter.h"
#include <string>

/*
*PrintCommand class:
used to print texts and expressions.
*/
class PrintCommand :public Command {
private:

	map<string, Var> *symbolTable;

public:
	PrintCommand(map<string, Var> *symTable)
		: symbolTable(symTable) {}

	int execute(list<string> params);

};
#endif
