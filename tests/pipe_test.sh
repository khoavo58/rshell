#$ s/{ctrl-V}{ctrl-M}//
#!bin/bash
cd ..
cd src
make
# testing single pipe
./main.out << EOF
cat < a.txt | tr a-z A-Z
exit
EOF
# testing two pipes
./main.out << EOF
cat < a.txt | tee b.txt | tr a-z A-Z
exit
EOF
# testing multiple pipes
./main.out << EOF
cat < a.txt | tr a-z A-Z | tee b.txt | tr A-Z a-z | tee c.txt
exit
EOF
