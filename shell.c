#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MAXLEN 513
#define MAXCMD 64
#define MAXARGS 256

static char *sep = ";";
static char *delim = " \t\n";

static int EXITSTATUS = 0;
static int argIndex = 0;

void ResetLine(char *line)
{
    memset(line, '\0', MAXLEN);
}

void ResetCommands(char *argv[MAXCMD][MAXCMD])
{
    int i;
    for (i = 0; argv[i][0]; i++)
        memset(argv[i][0], '\0', MAXCMD);
}

void Debug(char *argv[MAXCMD][MAXCMD])
{
    int i;
    for (i = 0; argv[i][0]; i++)
    {
        printf("%s\n", argv[i][0]);
    }
}
int IsValidInput(char *line)
{
    if (strlen(line) >= MAXLEN)
    {
        return 0;
    }
    int i;
    for (i = 0; line[i]; i++)
    {
        if (isalpha(line[i]))
            return 1;
    }
    return 0;
}

int ParseForSemiColon(char *str, char *parsedSemiColonCMDs[MAXCMD])
{
    int i = 0;
    char *token = strtok(str, sep);

    if (strcmp(token, "quit\n") == 0){
        EXITSTATUS = 1;
    }
        

    while (i < MAXCMD && token)
    {
        parsedSemiColonCMDs[i++] = token;
        token = strtok(NULL, sep);
    }
    parsedSemiColonCMDs[i] = NULL;
    return 1;
}
void ParseCommands(char *line, char *argv[MAXCMD][MAXCMD])
{
    char *token = strtok(line, delim);
    int index = 0;
    while (token)
    {
        if (strcmp(token, "quit") == 0 && index==0)
            EXITSTATUS = 1;
       
        argv[argIndex][index++] = token;
   
        token = strtok(NULL, delim);
    }
    argv[argIndex++][index] = NULL;
    
}
void Parse(char *line, char *argv[MAXCMD][MAXCMD])
{
    int i;
    char *token;
    char *parsedSemiColonCMDs[MAXCMD];

    int successfulParse = ParseForSemiColon(line, parsedSemiColonCMDs);
    if (successfulParse)
    {
        for(i=0;parsedSemiColonCMDs[i];++i)
        {
            ParseCommands(parsedSemiColonCMDs[i], argv);
        }
    }
}

void Execute(char *argv[MAXCMD][MAXCMD])
{
    int i = 0;
    
    for (; argv[i][0]; ++i)
    {
        pid_t pid;
        pid_t waitStatus;
        int status;
    
        if(strcmp(argv[i][0],"quit")==0){
            continue;
        };
        if ((pid = fork()) == 0)
        {
            printf("%u\n",i);
            if(pid==0){
                execvp(argv[i][0], &argv[i][0]);
                printf("Exec failed on command %s\n", argv[i][0]);
                exit(1);
            }
        }
        else
        {
            if (pid == (pid_t)(-1))
            {
                printf("Fork failed.\n");
                exit(1);
            }
            else
            {
                waitStatus = wait(&status);
                printf("PID %ld exited with status %d\n", (long)waitStatus, status);
            }
        }
    }
}

int main(int argc, char *argv[])
{
    char line[MAXLEN];
    char *cmds[MAXCMD][MAXCMD];
    FILE *fp;

    fp = fopen(argv[1], "r");

    if (fp != NULL)
    {
        printf("FILE IS: %s, argv[1] is %s\n", argv[1], argv[1]);
        while (fgets(line, MAXLEN, fp))
        {
            // Remove end line character
            line[strlen(line) - 1] = '\0';
            printf("Retrieved line of length %ld :\n+%s\n", strlen(line), line);
            

            // Only process valid input commands
            if (IsValidInput(line))
            {
                Parse(line, cmds);
                Execute(cmds);
            }
            if(EXITSTATUS) exit(0);
            ResetLine(line);
            ResetCommands(cmds);
        }
        if(EXITSTATUS) exit(0);
        fclose(fp);
    }
    else
    {

        printf("Prompt>>");
        while (fgets(line, MAXLEN, stdin))
        {
            // Remove end line character
            line[strlen(line) - 1] = '\0';
            // Only process valid input commands
            if (IsValidInput(line))
            {
                Parse(line, cmds);
                Execute(cmds);
            }
            if(EXITSTATUS) exit(0);
            ResetLine(line);
            ResetCommands(cmds);
            printf("Prompt>>");
        }
    }
    return 0;
}