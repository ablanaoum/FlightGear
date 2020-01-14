#ifndef LEXER_H
#define LEXER_H
#include <string>
#include <iostream>
#include <list>
#include <fstream>
#include <map>
/*
 * the lexer fucntion we use to split the commands and insert to list of string
 * and another helper funtion to the lexer.
 */
using namespace std;
list<string> lexer(const char* fileName);
string deleteSpaces(string line);
bool isEmpty(string line);
string runOverOperators(string line);

#endif