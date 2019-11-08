#ifndef __COMMAND_H__
#define __COMMAND_H__

#include <vector>
#include <string>
#include <cstring>
#include <iostream>
#include "shellBase.h"
#include "package.h"


using namespace std;

class Command:public ShellBase {
	public:
		vector<string> cnct;
		vector<Package*> argArr;
		vector<string> cmd;	//vector containing arguments;
		string _input;		//input string from user
		//constructors
		Command(){};					//default constructor
		Command(string input){_input = input;}	//constructor with one arg
		~Command();
		void parse();			//parse string using tokenizer
		bool execute();

};

Command::~Command() {					// destructor
	for (int i = 0; i < argArr.size(); i++) {
		argArr.at(i)->arr[0] = NULL;
	}
	argArr.clear();
	cnct.clear();
	cmd.clear();
	_input = "";
}

//parsing input by tokenizing
void Command::parse() {
	string temp = _input;
	Package* array;
	
	if (temp == "") {
		return;
	}
	//first store connectors into cnct
	//cout << "storing connector" << endl;
	for (int i = 0; i < _input.size(); i++)
	{
		if (_input.at(i) == ';') {
			cnct.push_back(";");
		}
		else if (_input[i] == '|') {
			if (_input[i+1] == '|') {
				cnct.push_back("||");
				i++;
			}
			else {
				cnct.push_back("|");			// added pipe checking
			}
		}
		else if (_input[i] == '&') {			// two characters that are the same.
			cnct.push_back("&&");
			i++;
		}
		else if (_input[i] == '(') {			// added checking for parenthesis
			cnct.push_back("(");
		}
		else if (_input[i] == ')') {
			cnct.push_back(")");
		}
		else if (_input[i] == '#') {
			cnct.push_back("#");
		}
		else if (_input[i] == '<') {
			cnct.push_back("<");
		}
		else if(_input[i] == '>') {
			if (_input[i+1] == '>') {
				cnct.push_back(">>");
				i++;
			}
			else {
				cnct.push_back(">");
			}
		}
	}
	//checking connectors
	// for (int i = 0; i < cnct.size(); i++) {		// outputting the connectors stored
	// 	cout << cnct.at(i) << ", ";
	// }
	// cout << "done" << endl;

	char* parser = strtok((char*)temp.c_str(), "><();|&#");	// tokenizing commands based on tokenizers
	cmd.push_back(parser);
    while (parser) {
        parser = strtok(NULL, "><();|&#");
        if (parser)
        {
			if (strcmp(parser, " ") != 0){
				cmd.push_back(parser);
			}
        }
	}
	// for (int i = 0; i < cmd.size(); i++) {				// check if the commands are separated correctly.
	// 	cout << cmd.at(i) << " | ";
	// }
	// cout << "done" << endl;

	for (int i = 0; i < cmd.size(); i++) {
		parser = strtok((char*)cmd.at(i).c_str(), " ");
		array = new Package(parser);
		int counter = 1;
		while (parser) {
		 	parser = strtok(NULL, " ");
			array->arr[counter] = parser;
			counter++;
		}
		array->arr[counter] = NULL;		// null terminator
		argArr.push_back(array);
		counter = 0;
	}

}

bool Command::execute() {
	return 0;
}


#endif //__command_h__
