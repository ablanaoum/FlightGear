//
// Created by abla on 01/01/2020.
//

#include "Lexer.h"
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

/*
 * function that takes a file and return a list of strings of commands , parameters we should.
*/
std::list<std::string> lexer(const char* fileName) {
	std::fstream file;
	unsigned int i;
	string line, temp, flagLine;
	std::list<string> lineStrings;
	//opening a file.
	file.open(fileName, std::ios::in);
	temp = "";
	line = "";
	//checking if the file is opened.
	if (!file) {
		throw ("File not Found !");
	}
	//loop for taking a line by line from the file.
	while (getline(file, line))
	{
		//delete the spaces from the line.
		line = deleteSpaces(line);
		flagLine = line;
		line = runOverOperators(line);
		if (isEmpty(line)) {
			break;
		}
		i = 0;
		
		while (i < line.size()) { //indecates to all the chars in the line.
			if (line[i] == '"') { // if there a string that starts with ".
				temp += line[i];
				i++;
				while (line[i] != '"') { 
					temp += line[i];
					i++;
				}
				temp += line[i];
				lineStrings.push_back(temp);
				temp = "";
				i++;
				continue;
			}
			//if we reach to those chars we can make a split and take the previous word.
			if ((line[i] != '(') && (line[i] != ')') && (line[i] != ' ') && (line[i] != '\t') && (line[i] != ',')) {
				temp += line[i];
				if (i == line.size() - 1) {
					lineStrings.push_back(temp);
					temp = "";
				}

			}
			else {
				if (temp.length() != 0) { 
					lineStrings.push_back(temp);
					temp="";
				}
				// we ignore the ( and ) at the sim sentance.
				if (((line[i] == '(') || (line[i] == ')')) && line.find("sim") == std::string::npos){
                    temp = line[i];
					lineStrings.push_back(temp);
					temp = "";
				}

			}
			i++;
		}
		line = "";
		lineStrings.push_back("END"); // add to the list "END" after each line.
	}

	return lineStrings;
}

/*
function that checking if the line is empty
*/
bool isEmpty(std::string line) {
	unsigned int j = 0;
	if (line.length() >= 1) {
		while (j < line.length()) {
			if (line[j] != ' ' && line[j] != '\t' && line[j] != '\n' && line[j] != 13) {
				return false;
			}
			j++;
		}
	}
	return true;
}
/*
function that adds spaces if there are not spaces
before and after the operators
*x=8-6 to x = 8 - 6

*/
std::string runOverOperators(string line) {
	std::string newLine;
	char operators[11] = { '+', '-', '*', '/', '=', '<', '>','&' ,'|','(',')' }; //operators
	int  flag, j;
	unsigned int i=0;
	while (i < line.size()) {
		flag = 0;
		//iterating over each operator
		j = 0;
		while (j < 11) {
			if (line[i] == operators[j]) {
                if(line.find("sim")!= std::string::npos)
                    break;
				//  '/' and '-' are not operators if sim apeears in the the line
				if (((line[i] == '<' || line[i] == '>') && line[i + 1] == '=')
					|| (line[i] == '-' && (line[i + 1] == '>' || line[i + 1] == '<'))
					|| (line[i] == '=' && line[i + 1] == '=')
					|| (line[i] == '!' && line[i + 1] == '=')
					|| (line[i] == '&' && line[i + 1] == '&')
					|| (line[i] == '|' && line[i + 1] == '|')) {

					if (line[i - 1] != ' ')//if there are no space before it.
						newLine += " "; // add space.
					newLine += line[i]; // take the first section for the operator.
					newLine += line[i + 1]; // take the second section for operator.
					if (line[i + 2] != ' ') // if there are no space after it.
						newLine += " "; // add space.
					flag = 1;
					i++;
					break;
				}

				if (line[i - 1] != ' ')
					newLine += " ";
				newLine += line[i];
				if (line[i + 1] != ' ')
					newLine += " ";
				flag = 1; // indecates that we added space.
			}
			j++;
		}


		if (flag == 0) { //line[i] is not operator and we don't add something
			newLine += line[i];
		}
		i++;
	}

	i = 0;
	while (i < newLine.size() - 1) {
		if (newLine[i] == ' ' && newLine[i + 1] == ' ') {
			newLine.erase(newLine.begin() + i);
			i--;
		}
		i++;
	}

	return newLine;
}

/*
function thatdelete spaces from the beginning and the end of the line
*/
std::string deleteSpaces(string line) {
	int end = line.size(), beginning = 0;
	std::string newLine;
	//count all the spaces from the end.
	while (line[end] == ' ') {
		end--;
	}
	//count all the spaces from the beginning.
	while (line[beginning] == ' ') {
		beginning++;
	}

	//taking the line without the spaces in the beginning and the end.
	while (beginning < end) {
		newLine += line[beginning];
		beginning++;
	}
	
	return newLine;

}
