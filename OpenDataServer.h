//
// Created by abla on 03/01/2020.
//

#ifndef DESKTOP_OPENDATASERVER_H
#define DESKTOP_OPENDATASERVER_H
#include <sys/socket.h>
#include <cstring>
#include <string>
#include <iostream>
#include <unistd.h>
#include <thread>
#include <map>
#include "ExpressionInterpreter.h"
#include "Expression.h"
#include "Command.h"
#include "ConnectCommand.h"
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <list>
using namespace std;

/*
* OpenServerCommand class:
open server and get info from the simulator.
*/
class OpenDataServer : public Command {
private:
    bool pass=false;
	map<string, Var> *symbolTable;
public:
	OpenDataServer(map<string, Var> *varsmap) {
		this->symbolTable = varsmap;
	}
	int execute(list<string> parameters);
    map<int,string> varsOrder();
	void openServer(int port);
	~OpenDataServer() {}
};
#endif //DESKTOP_OPENDATASERVER_H

