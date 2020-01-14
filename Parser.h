//
// Created by abla on 03/01/2020.
//

#ifndef DESKTOP_PARSER_H
#define DESKTOP_PARSER_H
#include "Command.h"
#include <iostream>
#include <map>
#include <list>
#include <string>
#include <chrono>
#include "ExpressionInterpreter.h"
#include "Expression.h"
#include <thread>

/*
* Parser Class.
by the commands evaluate each line that token from list of strings.
*/
using namespace std;
class Parser {
private:
	map<string, Command*> *commandMap;
	map<string, Var> *symbolTable;

public:
	//constructor for the Parser.
	Parser(map<string, Command*> *comMap, map<string, Var> *symTable
	) :commandMap(comMap), symbolTable(symTable) {}
	void parsing(list<string> &list);
};
#endif //DESKTOP_PARSER_H

