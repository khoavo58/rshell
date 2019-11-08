#$ s/{ctrl-V}{ctrl-M}//
#!/bin/bash
cd ..
cd src
make

# testing ls
./main.out << EOF
ls
exit
EOF

# testing ls -a
./main.out << EOF
ls -a
exit
EOF

# testing make
./main.out << EOF
make
exit
EOF

# testing echo
./main.out << EOF
echo Hello World
exit
EOF

# testing cd (should not work)
./main.out << EOF
cd
exit
EOF

# testing cd .. (should not work)
./main.out << EOF
cd ..
exit
EOF