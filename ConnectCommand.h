
//
// Created by abla on 03/01/2020.
//

#ifndef DESKTOP_CONNECTCOMMAND_H
#define DESKTOP_CONNECTCOMMAND_H

#include <sys/socket.h>
#include <cstring>
#include <iostream>
#include <unistd.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <thread>
#include <chrono>
#include <map>
#include "Command.h"
#include "Expression.h"
#include "ExpressionInterpreter.h"
#include "ConnectCommand.h"
#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>

/*
* ConnectServerCommand class.
connect as client to the server.
*/
class ConnectCommand : public Command {
private:
	map<string, Var> *symbolTable;
	bool msgSend ;
	string msg;
public:
	ConnectCommand(map<string, Var> *symTable) :symbolTable(symTable) {this->msgSend=false;}
	int execute(list<string> parameters);
	void sendMsg(string mesage);
	void connectToSim(string ip, int port);
	~ConnectCommand(){}
};
#endif //DESKTOP_CONNECTCOMMAND_H

