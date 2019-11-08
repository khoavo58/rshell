#$ s/{ctrl-V}{ctrl-M}//
#!bin/bash
cd ..
cd src
make

# testing test -e path
./main.out << EOF
test -e ../src/command.h
exit
EOF

# testing test [-e path]
./main.out << EOF
[ -e ../src/connector.h ]
exit
EOF

# testing test -f path
./main.out << EOF
test -f ../src/command.h
exit
EOF

# testing test [ -f path ]
./main.out << EOF
[ -f ../src ]
exit
EOF

# testing test -d path
./main.out << EOF
test -d ../src
exit
EOF

# testing test [ -d path ]
./main.out << EOF
[ -d ../src/command.h ]
exit
EOF

# testing test command test -e path with connectors
./main.out << EOF
test -e ../src/command.h && echo path exists
exit
EOF

# testing test command [ -e path ] with connectors
./main.out << EOF
[ -e ../src/command.h ] && echo path exists
exit
EOF

# testing test command test -e path with connectors
./main.out << EOF
test -e ../src/command.h || [ -e ../src/connector.h ]
exit
EOF

# testing test command [ -e path ] with connectors
./main.out << EOF
[ -e ../src/command.h ] || test -d ../src
exit
EOF