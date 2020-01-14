//
// Created by abla on 11/01/2020.
//
#ifndef NEWPR_IFCOMMAND_H
#define NEWPR_IFCOMMAND_H

#include <iostream>
#include <map>
#include "Command.h"
#include "Expression.h"
#include "ConditionParser.h"
#include <string>
#include <list>

/*
 * Command use the father funtion ConditionCommand , that make the parser work aroud
 * the strings it gets.
 */
class IfCommand :public ConditionParser {
public:
    IfCommand(map<string, Var> *symTable, map<string, Command*> *comMap)
            : ConditionParser(symTable,comMap) {}

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

        //it++;
        while ((*it) != "}") {
            commandsCondition.push_back(*it);
            counter++;
            it++;
        }
        //ConditionParser(commandMap, symbolTable);
        if(expression->calculate()!=0){
            ConditionParser::execute(commandsCondition);
            this_thread::sleep_for(chrono::milliseconds((long)5000));
            inter->setVariables(*this->symbolTable);
            ///for } and for "END:

        }
        //cout << counter+2;
        return counter + 2;

    }



};

#endif