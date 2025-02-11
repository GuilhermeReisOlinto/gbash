#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define MAX_CMD_LEN 1024

int main()
{
    char command[MAX_CMD_LEN];

    while (1)
    {
        printf("mini-bash> ");
        fgets(command, MAX_CMD_LEN, stdin);
        command[strcspn(command, "\n")] = 0;

        if (strcspn(command, "exit") == 0)
        {
            break;
        }

        system(command);
    }

    return 0;
}