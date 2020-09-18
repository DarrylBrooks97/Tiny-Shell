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

Darryl Brooks
FSUID: DB17D

# Design Overview

The code submitted acts a command line interpreter where each command is validiated before execution and executed if valid. The code operates in two modes batch and interactive and they vary by if the user passes a batch file path.

In the case that a file path is passed into the scripts argument the main function checks to see if that is a valid path to execute. If the path is valid then the script is executed, however if it is not then the code exits safely.

However, if a file path is not passed then the code runs in interactive mode. Where is waits for the user to type commands. Batch mode and Interactive mode implements the same code but differs by the file passed into the fgets() function.

The most important design structure of this code is the 2 dimensional cmds[][] character array. This structure is important because it allows multiple commands to be be stored after multiple semicolon breaks.

# Parsing

The code first checks to see if the command input is valid before even parsing it. It then parses the line for any semicolons and places them within a parsedSemiColon[] for later uses. It then checks to see if the parse was successful and if it was it then parses each individual token from the previous parse for spaces, tabs, and newline characters then places them in the cmds[][] for later use.

# Execution

The code on execution loops through the cmds[][] and forks then if a child process is successfully created it then executes that command. After all of the commands are executed a clean service like function resets the input line buffer and the cmds[][] for the next use;

# Complete Specification

- [x] Empty commands & Non Alphanumeric
  - Empty commands are handled by the IsValidInput function. This function checks to see if the entered command has either an alphabet or number before processing.
- [x] Incorrect file path
  - Incorrect file paths are handled before execution starts. If a file path does not exist then the program will exit safely using the perror() function.
- [x] Max input line length
  - Before the input is validated a check occurs to see if the input length is greater than the MAXLEN. If so, the function returns a 0 stating that it is not a valid input.
- [x] File without quit
  - As the file is being parsed and it does not see the word "quit" then it continues to parse under it reaches the end of the file.
- [x] Empty commands in between semicolons
  - As the code parses the input for semicolons it reuses the IsValidInput function to check whether the input length is 0 or greater than the MAXLEN. This keeps the program from adding in white space as a valid command.
