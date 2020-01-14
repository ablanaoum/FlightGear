//
// Created by abla on 13/01/2020.
//

#ifndef DESKTOP_WHILECOMMAND_H
#define DESKTOP_WHILECOMMAND_H
#include <iostream>
#include <map>
#include "Command.h"
#include "Expression.h"
#include <string>
#include <list>
#include "ConditionParser.h"


class WhileCommand :public ConditionParser {
private:

 //   map<string, Command*> *commandMap;
  //  map<string, Var> *symbolTable;


public:
    WhileCommand(map<string, Var> *symTable, map<string, Command*> *comdMap)
            : ConditionParser(symTable,comdMap){}

    int execute(list<string> params) {
        int counter=1;
        list<string>::iterator it;
        it= params.begin();
        it++;
        list<string> whileExpression;
        list<string> commandsCondition;
        while ((*it) != "{") {
            whileExpression.push_back(*it);
            counter++;
            it++;
        }
        counter++;

        /// send all the rest of commands to the parser
        it++;
        //if the { is at the end of the line
        if(*it=="END"){
            it++;
            counter++;
        }
        /// send to shuntingyard and calculate the expression of the the while.
        Interpreter* inter = new Interpreter();
        inter->setVariables(*this->symbolTable);
        Expression* expression = inter->interpret(whileExpression);
        //double flag=expression->calculate();

        //it++;
        while ((*it) != "}") {
            commandsCondition.push_back(*it);
            counter++;
            it++;
        }
        //ConditionParser(commandMap, symbolTable);
        while(expression->calculate()!=0){
            ConditionParser::execute(commandsCondition);
            inter->setVariables(*this->symbolTable);
            ///for } and for "END:

        }
        return counter + 2;
    }

};
#endif //DESKTOP_WHILECOMMAND_H
