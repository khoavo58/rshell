#ifndef SHELLBASE_H
#define SHELLBASE_H

class ShellBase {
    public:
        ShellBase(){}
        virtual ~ShellBase(){}
        virtual bool execute()=0;
};



#endif
