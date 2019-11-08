#$ s/{ctrl-V}{ctrl-M}//
#!bin/bash
cd ..
cd src
make
# testing exit function
./main.out << EOF
exit
EOF
# testing one command and exit
./main.out << EOF
ls -a;exit
EOF
# testing multiple commands and exit
./main.out << EOF
ls -a; make && cd ..|| echo Exiting Now...; exit
EOF
