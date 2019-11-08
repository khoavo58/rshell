#ifndef CONNECTOR_H
#define CONNECTOR_H
#include "shellBase.h"
#include <iostream>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <time.h>
#include <unistd.h>     //chdir(),fork(),exec(),pid_t
#include <stdlib.h>     //execvp()
#include <stdio.h>      //perror()
#include <string.h>     //strcmp(),strtok()
#include "package.h"

using namespace std;
#define P_SIZE 12

class Connector:public ShellBase {
    protected:
        bool temp_DIR;
        bool temp_REG;
        bool launch(char**);
        bool check_stat(char* argv[]);
        bool filedir(char* argv[]);
    public:
        Connector(){}
        virtual bool execute()=0;
};

bool Connector::launch(char** argv) {       //takes in an array of commands
    pid_t pid, wpid;
    bool status = true;

    //initualizing pipe
    int pipefd[2];          //pipe
    int pipe_value;         //if return value is 0 then pipe is good, -1 mean pipe failed
    char pipe_buf[P_SIZE];      //pipe char array to write in
    char temp_status = 't';     //temp holder for pipe message
    
    pipe_value = pipe(pipefd);  //get pipe's value
    
    if(pipe_value == -1){
        perror("pipe failed");
        exit(1);
    }
    if (strcmp(argv[0],"exit") == 0) {
        exit(0);                   // exit program
    }
    //Forking process
    if ((pid = fork()) == 0){
        //child process
        if (execvp(argv[0], argv) < 0){
            perror("command execvp() error");
            write(pipefd[1], "f", P_SIZE);          //write into pipe the char "f". note [1] is the writing end of pipe while [0] is the reading end.
            close(pipefd[0]);                       //close reading end of pipe
            exit(1);                              //according to the main page of systems, exit(127) indicates /bin/sh could not be executed
        }
    }
    else if (pid < 0) {
        //Error forking
        perror("forking error");
        exit(127);                //exit
    }
    else {
        //process works, while pid !=0. This is the parent process
        wait(0);
        close(pipefd[1]);                            //closing writing end of pipe
        read(pipefd[0], pipe_buf, P_SIZE);          //reading in from pipe: Note pipe is like a queue FIFO
        temp_status = pipe_buf[0];
        if(temp_status == 'f'){                      //if status is false
            status = false;
        }
    }

    return status;
}

bool Connector::check_stat(char* argv[])
{
    struct stat sb;     //sb is the buf holding the returned data when stat() is called
    temp_DIR = false;  //temp is_directory bool, can be made protected member
    temp_REG = false;  // temp is_regular file bool, can be made protected member
    
    // if (argc != 2){
    //     fprintf(stderr, "Usage: %s <pathname>\n", argv[0]);
    //     return false;
    //     //exit(EXIT_FAILURE);
    // }
    
    if (stat(argv[0], &sb) == -1)       //if stat() call failed
    {
        perror("stat");
        return false;
        //exit(EXIT_FAILURE);
    }
    
    //cases for file existence
    switch (sb.st_mode & S_IFMT){       //switch cases for file type
        case S_IFDIR:   
            temp_DIR = true;     
            break;     //return true if file is a directory
        case S_IFREG:   
            temp_REG = true;    
            break;     //return true if its a regular file
        default:        
            return true;         
            break;     //default -e case, file exist
    }
    
    return true;                    // executed completely
    //exit(EXIT_SUCCESS);         //can be modified for function purposes within rshell
}

bool Connector::filedir(char* argv[]) {
     return true;
}

#endif
