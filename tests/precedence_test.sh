#$ s/{ctrl-V}{ctrl-M}//
#!bin/bash
cd ..
cd src
make

# testing precedence with || connector
./main.out << EOF
(test -e ../src/command.h && echo path exists) || ([ -f ../src/command.h ] && echo path exists)
exit
EOF

# testing nested precedence with && connector
./main.out << EOF
(([ -e ../src/command.h ] && echo path exists) && (ls -a;cd ..|| echo Hello World && make))
exit
EOF

# testing uneven amount of parentheses (should error gracefully)
./main.out << EOF
(make || ls -a) && ( echo Hello world
exit
EOF

