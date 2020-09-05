#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

#define MAXLEN 512

void parse(char *line, char **argv)
{
    for (int index = 0; index < MAXLEN; index++)
    {
        argv[index] = strsep(&line, " ");

        if (argv[index] == NULL)
            break;
        if (strlen(argv[index]) == 0)
            --index;
    }
}

/* 
cd ergedfg; pwd;
pwd;pwd;pwd
*/
void execute(char **argv)
{
    return;
}
int main(void)
{
    char line[1024];
    char *argv[64];
    int status = 0;

    printf("Prompt>>");
    while (fgets(line, sizeof(line), stdin))
    {

        parse(line, argv);
        if (strcmp(argv[0], "exit") == 0)
        {
            exit(0);
        }
        // execute(argv);
        printf("%s", argv[1]);
        printf("Prompt>>");
    }
    return 0;
}