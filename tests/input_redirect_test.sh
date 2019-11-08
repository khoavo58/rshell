#$ s/{ctrl-V}{ctrl-M}//
#!bin/bash
cd ..
cd src
# testing echo
# should complete the action, but segfaults for unknown reason.
./main.out << EOF
cat < quotes.txt
EOF

# testing file redirection
# should complete the action with an unknown segfault at the end
./main.out << EOF
cat < a.txt > b.txt
EOF

# testing file redirection on piped input
./main.out << EOF
cat < a.txt | tr a-z A-Z > c.txt
exit
EOF

# testing file redirection on multiple piped input
./main.out << EOF
cat < a.txt | tr a-z A-Z | tee b.txt | tr a-z A-Z > c.txt
exit
EOF