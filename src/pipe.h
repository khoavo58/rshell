#include "command.h"
#include "connector.h"
#include "semicolon.h"
#include "and.h"
#include "or.h"
#include <iostream>
#include <fstream>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <cstring>
#include <unistd.h>     //chdir(),fork(),exec(),pid_t
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <fstream>
#define WRITE_END 1
#define READ_END 0
using namespace std;

int pipen(char** argv, int fd[2]){
    pid_t pid;
    int pipefd[2];
    int pipeval;
    pipeval = pipe(pipefd);
    pid = fork();
    if(pipeval == -1){
        perror("pipe failed");
        exit(1);
    }

    if (pid == 0) {
        //child process
        dup2(pipefd[WRITE_END], STDOUT_FILENO);         // change fdout to pipe
        dup2(fd[0], STDIN_FILENO);
        if(execvp(argv[0], argv) < 0) {
            perror("execvp error");
            exit(1);
        }
    }
    else if (pid < 0) {
        //Error forking
        perror("forking error");
        exit(127);                //exit
    }
    else {
        //parent process
        wait(0);
        dup2(fd[1], STDOUT_FILENO);             // restore fdout
        fd[0] = pipefd[READ_END];
        dup2(pipefd[READ_END], STDIN_FILENO);
        close(pipefd[WRITE_END]);                       // cout will write to pipe            
    }
    return fd[0];
}