#ifndef __statCalls__
#define __statCalls__

#include <sys/types.h>
#include <sys/stat.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

//function to check status of files using stat()
bool check_stat(int argc, char* argv[])
{
    struct stat sb;     //sb is the buf holding the returned data when stat() is called
    bool temp_DIR = false;  //temp is_directory bool, can be made protected member
    bool temp_REG = false;  // temp is_regular file bool, can be made protected member
    
    if (argc != 2){
        fprintf(stderr, "Usage: %s <pathname>\n", argv[0]);
        exit(EXIT_FAILURE);
    }
    
    if (stat(argv[0], &sb) == -1)       //if stat() call failed
    {
        perror("stat");
        exit(EXIT_FAILURE);
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
    
    exit(EXIT_SUCCESS);         //can be modified for function purposes within rshell
}
#endif