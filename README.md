Rshell UCR CS100 Assignment 4

Main Contributors: Annie Du, Khoa Vo

In this assignment, we created a basic command shell that takes commands from the bin/bash directory.

Currently, the project can:

    Take in single line commands with ';' '||' '&&' connectors in different combinations.
    Execute all commands according to the connectors and available commands in the specified directory.
    Execute commands with precedence using parenthesis '()'
    Execute test commands using flags -e, -f, and -d. Also works with precedence
    Redirection using <,<<,>,>> and pipe |

Known Bugs:

    Segmentation fault when the line of commands end with a connector and not a command.


Annie Du complete:
    Task 1: Github Setup (10%)
    Task 2: Input redirection (For commands contain "<", 20%);
    Task 3: output redirection (For commands contain ">" and ">>", 20%);
total: 50%;

Khoa Vo complete:
    Task 4: Piping (25%)
    Task 5: construct test scripts (enough test cases, 15%);
    Task 6: construct json and README files, and git commit (that means, all the works meaned from the part "Submission" to "Coding             Conventions" in assignment 4 description)(10%) 
total: 50%
