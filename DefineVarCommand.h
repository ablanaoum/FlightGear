//
// Created by abla on 08/01/2020.
//

#ifndef NEWPR_DEFINEVARCOMMAND_H
#define NEWPR_DEFINEVARCOMMAND_H
#include <iostream>
#include <map>
#include <string>
#include "Command.h"
#include "ConnectCommand.h"
#include "Expression.h"
#include <string>
#include "ExpressionInterpreter.h"
#include "Expression.h"

/*
*DefineVarCommand class:
class that define the var for each command.
*/
class DefineVarCommand :public Command {
private:
	map<string, Var> *symbolTable;

public:
	DefineVarCommand(map<string, Var> *symTable)
		: symbolTable(symTable){}

	int execute(list<string> params);

};


#endif //NEWPR_DEFINEVARCOMMAND_H

