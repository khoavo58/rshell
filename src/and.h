#ifndef AND_H
#define AND_H
#include "connector.h"
#include "package.h"

class And: public Connector {
    protected:                  // every connector will have a lhs and rhs;
        bool execution;
        char** rhs;
    private:
        bool e;
        char* pass[100];
    public:
        And(){}
        And(bool b, char** r){execution = b; rhs = r;}
        bool execute();
};

//execute if previous process succeeds
bool And::execute() {
    if (execution) {
        if (strcmp(rhs[0],"test") == 0 || strcmp(rhs[0],"[") == 0) {
        //cout << "hi" << endl;
        if (rhs[2] == NULL)        // if missing a value no -e case
        {
            pass[0] = rhs[1];
        }
        else {
            pass[0] = rhs[2];
        }
        pass[1] = NULL;
        if (strcmp(rhs[1],"-f") == 0) {
            e = check_stat(pass);
            if (e) {
                if(temp_REG) {
                    cout << "(TRUE)" << endl;
                }
                else{
                    cout << "(FALSE)" << endl;
                }
            }
        }
        else if (strcmp(rhs[1],"-d") == 0) {
            e = check_stat(pass);
            if (e) {
                if (temp_DIR) {
                    cout << "(TRUE)" << endl;
                }
                else {
                    cout << "(FALSE)" << endl;
                }
            }
        }
        else {
            //cout << "-e" << endl;
            e = check_stat(pass);
            if (e) {
                if (temp_DIR || temp_REG) {
                    cout << "(TRUE)" << endl;
                }
                else {
                    cout << "(FALSE)" << endl;
                }
            }
        }
        return e;
        }
        else {
            return launch(rhs);
        }
    }
    else{
        return false;             // return without checking next execution.
    }
}
#endif
