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

int exitStatus = 0;

void debug(char *argv[MAXCMD][MAXCMD])
{
    int i;
    for (i = 0; argv[i][0]; i++)
    {
        printf("%s\n", argv[i][0]);
    }
}

void ResetLine(char *line)
{
    memset(line, 0, MAXLEN);
}
void ResetCommands(char *argv[MAXCMD][MAXCMD])
{
    int i;
    for (i = 0; argv[i][0]; i++)
        memset(argv[i][0], 0, MAXCMD);
}

// function for finding semi
int parseSemiColon(char *str, char *strWithSemi[])
{
    int i = 0;
    char *token = strtok(str, sep);

    if (strcmp(token, "quit\n") == 0)
        exitStatus = 1;
    while (token)
    {
        if (isspace(*token) == 0)
        {
            strWithSemi[i++] = token;
        }
        token = strtok(NULL, sep);
    }
    strWithSemi[i] = NULL;
    return strWithSemi[0] == NULL ? 0 : 1;
}
void ParseCommands(char *line, char *argv[MAXCMD][MAXCMD], int cmd)
{
    char *token = strtok(line, delim);
    int index = 0;
    while (token)
    {
        if (strcmp(token, "quit") == 0)
            exitStatus = 1;
        argv[cmd][index++] = token;
        token = strtok(NULL, delim);
    }
    argv[cmd][index] = NULL;
}
int parse(char *line, char *argv[MAXCMD][MAXCMD])
{
    char *token;
    char *strWithSemi[MAXCMD];
    int parsedSemiColonFlag = parseSemiColon(line, strWithSemi);
    int i = 0;

    if (parsedSemiColonFlag)
    {
        for (i = 0; strWithSemi[i]; ++i)
        {
            ParseCommands(strWithSemi[i], argv, i);
        }
    }
    else
    {
        ParseCommands(line, argv, i);
    }
    return 1;
}

void execute(char *argv[MAXCMD][MAXCMD])
{
    int i = 0;
    for (; argv[i][0]; ++i)
    {
        // Forking a child
        pid_t pid;
        pid_t c;
        int status;
        if ((pid = fork()) == 0)
        {
            execvp(argv[i][0], &argv[i][0]);
        }
        else
        {
            if (pid == (pid_t)(-1))
            {
                // printf(stderr, "Fork failed.\n");
                exit(1);
            }
            else
            {
                c = wait(&status);
                printf("PID %ld exited with status %d\n", (long)c, status);
            }
        }
    }
}

int main(void)
{
    char line[MAXLEN];
    char *argv[MAXCMD][MAXCMD];
    int status = 0;

    printf("Prompt>>");
    while (fgets(line, sizeof(line), stdin))
    {
        line[strlen(line) - 1] = '\0';
        printf("he");
        int success = parse(line, argv);
        if (strcmp(argv[0][0], "quit") == 0)
        {
            exit(0);
        }

        // debug(argv);
        if (success)
            execute(argv);
        // ResetLine(line);
        // ResetCommands(argv);
        printf("Prompt>>");
    }
    return 0;
}