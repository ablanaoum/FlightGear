//
// Created by abla on 11/01/2020.
//

#include "Parser.h"

void Parser::parsing(list<string>& commandsList)
{
    std::list<string> restOfList;
    std::list<string>::iterator it = commandsList.begin();
    std::list<string>::iterator it1;
    Command *command;
    unsigned int count = 0;
    unsigned int index=0;
    while (it!=commandsList.end() && index<commandsList.size()-1) {
        if (this->commandMap->find(*it) != this->commandMap->end()) {
            command = this->commandMap->find(*it)->second;
            it1 = it;
            while (it1 != commandsList.end()) {
                restOfList.push_back((*it1));
                it1++;
            }
            try {
                index += command->execute(restOfList);
            }catch (const char* e){
                throw e;
            }
            restOfList.clear();
            while (count < index && it!=commandsList.end()) {
                it++;
                count++;
            } //if there is a var that we have defined before
            //breaks = 0
        }else if (this->symbolTable->find(*it) != this->symbolTable->end()) {
            string var=*it;
            int countStep=0;
            Interpreter* inter = new Interpreter();
            inter->setVariables(*this->symbolTable);
            //pass the variable name;
            it++;
            //pas the = char
            it++;
            countStep+=2;
            while ((*it) != "END") {
                restOfList.push_back((*it));
                it++;
                countStep++;
            }
            index+=countStep;
            count+=countStep;
            //pas the END string
            if(index<commandsList.size()-1){
                it++;
                index++;
                count++;
            }
            double p;
            try {
                Expression* expression = inter->interpret(restOfList);
                p = expression->calculate();
            }
            catch (const char* e) {
                throw("invalid argument for expression");
            }
            restOfList.clear();
            if (this->symbolTable->find(var)->second.type == "->") {
                ConnectCommand *connect = dynamic_cast<ConnectCommand *>
                (this->commandMap->find("connectControlClient")->second);
                string msg="";
                msg += "set ";
                msg += (this->symbolTable->find(var)->second).sim;
                msg+=' ';
                msg += to_string(p);
                connect->sendMsg(msg);
                this_thread::sleep_for(chrono::milliseconds(100));
            }
            this->symbolTable->find(var)->second.value=p;
        }
        else {
            throw("ERROR");
        }


    }



}

