//
// Created by abla on 09/01/2020.
//
#include <iostream>
#include <list>
#include "ExpressionInterpreter.h"
#include "Expression.h"
#include <string.h>
#include <algorithm>
#include <fstream>
#include <map>
#include "PrintCommand.h"
#include "Parser.h"
#include "Command.h"
#include "Lexer.h"
#include "OpenDataServer.h"
#include "ConnectCommand.h"
#include "DefineVarCommand.h"
#include "SleepCommand.h"
#include "IfCommand.h"
#include "WhileCommand.h"

#define PRINT_COMMAND "Print"
#define OPEN_DATA_SERVER_COMMAND "openDataServer"
#define CONNECT_COMMAND "connectControlClient"
#define DEFINE_VAR_COMMAND "var"
#define SLEEP_COMMAND "Sleep"
#define IF_COMMAND "if"
#define WHILE_COMMAND "while"

/*
 * main function.  the interpreter.
 * get file from the command line and execute it line by line
 * by lexer function and then parser .
 */
using namespace std;
int main(int argc, char *argv[]) {
    if (argc != 2){
        cout<<"invalid arguments!";
        return -1;
    }
    map<string, Command *> commandsMap;
    map<string, Var> symbolTbl;
    //map<string, string> bindingTbl;
    //initialize the command .
    commandsMap[PRINT_COMMAND] = new PrintCommand(&symbolTbl);
    commandsMap[OPEN_DATA_SERVER_COMMAND] = new OpenDataServer(&symbolTbl);
    commandsMap[CONNECT_COMMAND] = new ConnectCommand(&symbolTbl);
    commandsMap[DEFINE_VAR_COMMAND] = new DefineVarCommand(&symbolTbl);
    commandsMap[SLEEP_COMMAND] = new SleepCommand(&symbolTbl);
    commandsMap[WHILE_COMMAND] = new WhileCommand(&symbolTbl,&commandsMap);
    commandsMap[IF_COMMAND] = new IfCommand( &symbolTbl, &commandsMap);
    Parser *parser;

    //take the tokens as a result of lexer function , and start to execute by parser.
    list<string> tokens;
    try {
        tokens = lexer(argv[1]);
        parser = new Parser(&commandsMap, &symbolTbl);
        parser->parsing(tokens);
    } catch (const char *e) {
        cout << e << endl;
        return 1;
    }
    map<string, Command *>::iterator it;
    //iterating over each command and delete it
    for (it = commandsMap.begin(); it != commandsMap.end(); ++it) {
        delete it->second;
    }

    this_thread::sleep_for(chrono::milliseconds(2000));
    return 0;
}