#include "command.h"

#include "semicolon.h"
#include "and.h"
#include "or.h"
#include "pipe.h"
#include <iostream>
#include <fstream>
#include <istream>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <cstring>
#include <unistd.h>     //chdir(),fork(),exec(),pid_t
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <fstream>
using namespace std;

int main() {
        //=============variable declaration begin==================
        Command* cmd;
        Connector* connect;
        Package* c;
        string input;
        bool execution = true;
        bool paren;
        int cnctcounter = 0;
        int j = 0;
        int flag = 0;
        int restore = 0;
        int savedin = 0;
        int savedout = 1;
        int fd[2];
        fd[0] = 0;
        fd[1] = 1;
        //==============variable declaration end===================
    while(1) {                      // continous loop until exit function

        cout << "$ ";       // shell command 
        getline(cin, input);       // get string of commands until enter
        cmd = new Command(input);
        cmd->parse();               // separates all commands and connectors
        c = cmd->argArr[0];
        dup2(0,0);
        dup2(1,1);
        // execute if not 'exit' or 'test'
        while(j < cmd->argArr.size()) {
            c = cmd->argArr[j];
            if ((j == 0 && cmd->cnct.size() == 0) || 
                (j == 0 && cmd->cnct.size() > 0 && cmd->cnct.at(0) != "(" && cmd->cnct.at(0) != "<" && cmd->cnct.at(0) != ">" && cmd->cnct.at(0) != ">>")) {  
                connect = new Semicolon(execution, c->arr);
                execution = connect->execute();
            }
            else if (cmd->cnct.at(cnctcounter) == "&&") {                  // and case
                //cout << "and" << endl;
                if (cnctcounter < cmd->cnct.size() - 1 && cmd->cnct.at(cnctcounter + 1) == "(") {
                    if (execution) {
                        cnctcounter++;
                        j--;
                    }
                }
                else {
                        connect = new And(execution, c->arr);
                        execution = connect->execute();                         // return if execution was successful 
                        cnctcounter++;
                }
            }
            else if (cmd->cnct.at(cnctcounter) == "||") {             // or case
                //cout << "or" << endl;
                if (cnctcounter < cmd->cnct.size() - 1 && cmd->cnct.at(cnctcounter + 1) == "(") {
                    if (!execution) {
                        cnctcounter++;
                        j--;
                        execution = true;
                    }
                }   
                else {
                    connect = new Or(execution, c->arr);
                    execution = connect->execute();                         // return if execution was successful 
                    cnctcounter++;
                }
            }
            else if (cmd->cnct.at(cnctcounter) == ";") {              // semicolon case
                //cout << "semi" << endl;
                if (cnctcounter < cmd->cnct.size() - 1 && cmd->cnct.at(cnctcounter + 1) == "(") {
                    j--;
                    cnctcounter++;
                }
                else {
                    connect = new Semicolon(execution, c->arr);
                    execution = connect->execute();                         // return if execution was successful 
                    cnctcounter++;
                }
            }
            else if (cmd->cnct.at(cnctcounter) == "(") {              // parenthesis case
                paren = true;                                         // starts as true
                if (cmd->cnct.at(cnctcounter + 1) == "(") {
                    flag = 1;
                    cnctcounter++;
                }
                cnctcounter++;
                //cout << "nested execute" << endl;
                connect = new Semicolon(execution,c->arr);            // execute first command in parenthesis
                execution = connect->execute();
                j++;
                while (cmd->cnct.at(cnctcounter) != ")") {
                    c = cmd->argArr[j];
                    if (cmd->cnct.at(cnctcounter) == "&&") {                  // nested and case
                        //cout << "*nested and" << endl;
                        if (execution == false) {                             // if execution is false, then the parenthesis did not execute all correctly)
                            paren = false;
                        }
                        connect = new And(execution, c->arr);
                        execution = connect->execute();                         // return if execution was successful 
                        cnctcounter++;
                    }
                    else if (cmd->cnct.at(cnctcounter) == "||") {             // nested or case
                        //cout << "*nested or" << endl;
                        if (execution == true) {
                            paren = false; 
                        }
                        connect = new Or(execution, c->arr);
                        execution = connect->execute();                         // return if execution was successful 
                        cnctcounter++;
                    }
                    else if (cmd->cnct.at(cnctcounter) == ";") {              // nested semicolon case
                        //cout << "*nested semi" << endl;
                        connect = new Semicolon(execution, c->arr);
                        execution = connect->execute();                         // return if execution was successful 
                        paren = true;
                        cnctcounter++;
                    }
                    j++;
                }
                if (flag == 1) {
                    cnctcounter++;
                }
                cnctcounter++;
                execution = paren;                                              // overall paren bool value
                //cout << "execution: " << execution << endl;
                j--;
            }
            else if (cmd->cnct.at(cnctcounter) == "|" || cmd->cnct.at(cnctcounter) == "<" || cmd->cnct.at(cnctcounter) == ">>" || cmd->cnct.at(cnctcounter) == ">") {
                if (strcmp(c->arr[0], "cat") == 0) {
                    j++;
                }
                c = cmd->argArr[j];
                if (cmd->cnct.at(cnctcounter) == "<") {// cat <
                    // cout << "connector <" << endl;
                    string file = c->arr[0];
                    fd[0] = open(file.c_str(), O_RDONLY);
                    savedin = dup(0);
                    savedout = dup(1);
                    dup2(fd[0], 0);
                    cnctcounter++;
                    if(cnctcounter >= cmd->cnct.size()) {       // only connector
                        vector<string> s;
                        string str;
                        while(getline(cin, str)) {
                            cout << str << endl;
                        }
                        dup2(0,0);             // restore
                        dup2(1,1);
                        break;
                    }
                    else if (cmd->cnct.at(cnctcounter) == ">" || cmd->cnct.at(cnctcounter) == ">>"){
                        // output to a file
                        j++;
                        c = cmd->argArr[j];
                        string file = c->arr[0];
                        if (cmd->cnct.at(cnctcounter) == ">") {
                            ofstream ofs;
                            ofs.open(file.c_str(), ios::out | ios::trunc);
                            ofs.close();
                        }
                        fd[1] = open(file.c_str(), O_WRONLY | O_APPEND);
                        savedin = dup(0);
                        savedout = dup(1);
                        dup2(fd[1], 1);
                        string str;
                        while(getline(cin, str)) {
                            cout << str << endl;
                        }
                        dup2(0, 0);
                        dup2(1, 1);
                        break;
                    }
                }
                else if (cmd->cnct.at(0) == ">" || cmd->cnct.at(0) == ">>") {// echo case
                    // cout << "echo case" << endl;
                    c = cmd->argArr[j+1];               // file to write
                    string file = c->arr[0];
                    //cout << file << endl;
                    if (cmd->cnct.at(cnctcounter) == ">") {
                        //cout << "remove" << endl;
                            ofstream ofs;
                            ofs.open(file.c_str(), ios::out | ios::trunc);
                            ofs.close();
                    }
                    fd[1] = open(file.c_str(), O_WRONLY | O_APPEND);
                    if (fd[1] < 0) {
                        perror("error opening file");
                    }
                    savedin = dup(0);
                    savedout = dup(1);
                    dup2(fd[1], 1);
                    c = cmd->argArr[j];                 // echo cmd
                    connect = new Semicolon(execution, c->arr);
                    execution = connect->execute();
                    // because > and >> are last connectors, restore
                    dup2(savedin, 0);
                    dup2(savedout, 1);
                    j++;
                }
                else if (cmd->cnct.at(cnctcounter) == "|") {  
                    //cout << "connector |" << endl;                          //================BIG ERRORS HERE=================
                    if (cnctcounter < cmd->cnct.size() - 1) {
                        if (cmd->cnct.at(cnctcounter + 1) == ">" || cmd->cnct.at(cnctcounter+1) == ">>") {
                            //cout << "| and then > or >>" << endl;
                            restore = 1;                        // add a cnctcounter if 1
                            c = cmd->argArr[j+1];
                            string file = c->arr[0];
                            savedin = dup(0);
                            savedout = dup(1);
                            fd[1] = open(file.c_str(), O_WRONLY | O_APPEND);
                            if (cmd->cnct.at(cnctcounter + 1) == ">") {
                                ofstream ofs;
                                ofs.open(file.c_str(), ios::out | ios::trunc);
                                ofs.close();
                            }
                            dup2(fd[1], STDOUT_FILENO);
                            // execute here because last cmd
                            c = cmd->argArr[j];
                            connect = new Semicolon(execution, c->arr);
                            execution = connect->execute();
                            if (fd[1] != 1) {
                            close(fd[1]);
                            }
                            if (fd[0] != 0) {
                                close(fd[0]);
                            }
                            j++;
                        }
                        else if (cmd->cnct.at(cnctcounter + 1) == "|") {
                            //cout << "connector | after |" << endl;
                            fd[0] = pipen(c->arr, fd);
                        }
                    }
                    else if (cnctcounter == cmd->cnct.size() - 1) {
                        //cout << "single |" << endl;
                        dup2(fd[1], STDOUT_FILENO);
                        connect = new Semicolon(execution, c->arr);
                        execution = connect->execute();
                        if (fd[1] != 1) {
                            close(fd[1]);
                        }
                        if (fd[0] != 0) {
                            close(fd[0]);
                        }
                    }
                    cnctcounter++;
                    if (restore == 1) {
                        cnctcounter++;             // next one was > or >>
                        dup2(savedin, 0);                                   // restore original
                        dup2(savedout, 1);
                    }
                }
            }
            else if (cmd->cnct.at(cnctcounter) == "#") {
                break;
            }
            else {
                perror("Error: Invalid Connector");
            }      
            j++;
        }
        // once all commands in the line are executed, deconstruct to refresh variables
        j = 0;
        delete cmd;
        input = "";
        cnctcounter = 0;
        flag = 0;
        fd[0] = 0;
        fd[1] = 1;
        dup2(savedin, 0);
        dup2(savedout, 1);
    }

    return 0;
}