#$ s/{ctrl-V}{ctrl-M}//
#!bin/bash
cd ..
cd src
make
# testing ; connector
./main.out << EOF
ls -a;echo Hello World
exit
EOF

# testing ; connector with failed previous command
./main.out << EOF
cd ..;echo Hello World
exit
EOF

# testing && connector
./main.out << EOF
ls -a&& make
exit
EOF

# testing && connector with failed previous command
./main.out << EOF
cd .. && make
exit
EOF

# testing || connector
./main.out << EOF
cd .. || ls -a
exit
EOF

# testing || connector with passed previous command
./main.out << EOF
make || ls -a
exit
EOF

# testing more than two commands (all should execute)
./main.out << EOF
ls -a;cd ..|| echo Hello World && make
exit
EOF

# testing more than two commands (not all should execute)
./main.out << EOF
ls -a;echo Hello World && make || echo Shouldn't Output
exit
EOF