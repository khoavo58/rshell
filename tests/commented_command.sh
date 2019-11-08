#$ s/{ctrl-V}{ctrl-M}//
#!bin/bash
cd ..
cd src
make
# testing one command with comment
./main.out << EOF
ls -a #make
exit
EOF
# testing multiple command with comment
./main.out << EOF
ls -a; make && echo Hello #This is a comment
exit
EOF
# testing comment with exit (program should not exit)
./main.out << EOF
ls -a; make && echo dont exit yet #echo exit
exit
EOF