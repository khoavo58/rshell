#$ s/{ctrl-V}{ctrl-M}//
#!bin/bash
cd ..
cd src
make
# testing echo append
# should complete the action, but segfaults for unknown reason.
./main.out << EOF
echo Textfile A > a.txt
echo >> a.txt
cat < quotes.txt >> a.txt
EOF

# testing file redirected append
./main.out << EOF
echo Textfile B > b.txt
echo >> b.txt
cat < a.txt >> b.txt
EOF

# testing append on piped file
./main.out << EOF
echo Textfile C > c.txt
echo >> c.txt
cat < a.txt | tr a-z A-Z >> c.txt
exit
EOF

# testing append on multiple piping

./main.out << EOF
echo Textfile E > e.txt
echo >> e.txt
cat < a.txt | tr a-z A-Z | tee d.txt | tr A-Z a-z >> e.txt
exit
EOF