#ifndef PACKAGE_H
#define PACKAGE_H
#define MAX_SIZE 1000

class Package {
    public:
        char* arr[MAX_SIZE];
        Package(char* a){arr[0] = a;}
};

#endif
