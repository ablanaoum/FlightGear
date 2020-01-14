//
// Created by abla on 03/01/2020.
//

#ifndef DESKTOP_CONDITIONPARSER_H
#define DESKTOP_CONDITIONPARSER_H

#include "Command.h"

/*
* ConditionParser class.
execute list of commands if there is a condition of the parser.
*/
class ConditionParser : public Command {
protected:
    map<string, Var> *symbolTable;
    map<string, Command*> *commandMap;
public:
    ConditionParser(map<string, Var> *symTable,map<string, Command*> *comMap):
    symbolTable(symTable),commandMap(comMap){}
	int execute(list<string> params) {
        list<string>::iterator it;
        it = params.begin();
        list<string> temp;
        Parser *p = new Parser(&(*this->commandMap), &(*this->symbolTable));
        p->parsing(params);
        return params.size();

  }
};
#endif //DESKTOP_CONDITIONPARSER_H

