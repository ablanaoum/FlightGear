//
// Created by abla on 03/01/2020.
//

#ifndef DESKTOP_COMMAND_H
#define DESKTOP_COMMAND_H

#include <list>
#include <string>

/*
command interface exists execute function
that takes list of stringsexecute them and
returned how much to move till the next command.
*/

using namespace std;
struct Var {
    //'->' or '<-' or "";
    string type = "";
    string sim = "";
    double value=0;

};

class Command {
public:
	virtual int execute(list<string> parameters) = 0;
	virtual ~Command(){}
};
#endif //DESKTOP_COMMAND_H
