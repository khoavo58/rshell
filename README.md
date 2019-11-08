Rshell

Main Contributors: Khoa Vo, Annie Du

This is a basic command shell that takes commands from the bin/bash directory.

Currently, the Rshell can:

    Take in single line commands with ';' '||' '&&' connectors in different combinations.
    Execute all commands according to the connectors and available commands in the specified directory.
    Execute commands with precedence using parenthesis '()'
    Execute test commands using flags -e, -f, and -d. Also works with precedence
    Redirection using <,<<,>,>> and pipe |

Known Bugs:

    Segmentation fault when the line of commands end with a connector and not a command.
