#$ s/{ctrl-V}{ctrl-M}//
#!bin/bash
cd .. 
cd src
# testing echo output redirect
./main.out << EOF
echo Textfile A > a.txt
echo Textfile B > b.txt
echo Textfile C > c.txt
exit
EOF

# testing output file redirect with input redirection with pipe
./main.out << EOF
cat < quotes.txt | tr a-z A-Z > b.txt
exit
EOF

# testing output redirect on multiple piped file
./main.out << EOF
echo >> c.txt
cat < quotes.txt | tr a-z A-Z | tee c.txt | tr A-Z a-z > d.txt
exit
EOF