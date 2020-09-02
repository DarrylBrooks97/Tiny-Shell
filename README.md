# Tiny Shell Operating Systems

## Overview

To implement a command line interpreter (or a shell).The shell should operate in this basic way: when you type in a command (in response to its prompt), the shell creates a child process that executes the command you entered and then prompts for more user input when the child has finished. The shells you implement will be similar to, but much simpler than, the one you run every day in Unix. For this project, you do not need to implement much functionality; but you will need to be able to handle running multiple commands simultaneously.

Interactive Mode:
- [ ] Command prompts
- [ ] Stops when it sees quit or ‘Ctrl-D’
- [ ] May contain multiple ‘;’ in which commands must be split up
    - [ ] wait() or waitPID() can be useful 

Batch Mode:
- [ ] Contains a list of commands and must be echoed after each process is completed
- [ ] Stops when it sees quit or ‘Ctrl-D’ or end of file
- [ ] May contain multiple ‘;’ in which commands must be split up
    - [ ] wait() or waitpid() can be useful 

Requirements:
- [ ] If quit command is on the same line as another command, you will have to execute that command first before quitting
- [ ] Shell will have optional parameter on execution, if no file path is given then the shell should run in interactive mode
- [ ] Error should print to the user and exit gracefully
    - [ ] Incorrect amount of command line arguments 
    - [ ] The batch file trying to be opened cannot be accessed
    - [ ] Command does not existed or cannot be executed
    - [ ] A very long command line (512> length or `\`)
- [ ] Commands the program should not throw an error for
    - [ ] An empty line 
    - [ ] Extra white space between commands
    - [ ] The end of the batch file not having quit

Hints
- [ ] fget() to parse line 
- [ ] fopen() to open a file 
- [ ] strtok() for parsing also 

