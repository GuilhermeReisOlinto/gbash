#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MAX_COMMAND_LENGTH 1024
#define MAX_ARGS 64

// Func para executar comandos
void execute_command(char *input)
{
    char *args[MAX_ARGS];
    int i = 0;

    // Tokenizando a string de entrada
    args[i] = strtok(input, " ");
    while (args[i] != NULL)
    {
        i++;
        args[i] = strtok(NULL, " ");
    }

    // Mudar de diretório com cd
    if (strcmp(args[0], "cd") == 0)
    {
        if (args[1] == NULL)
        {
            fprintf(stderr, "Uso: cd <diretório>\n");
        }
        else
        {
            if (chdir(args[1]) != 0)
            {
                perror("cd falhou");
            }
        }
        return;
    }

    // Cria processo filho para executar comando
    pid_t pid = fork();

    if (pid < 0)
    {
        perror("Erro ao criar processo");
    }
    else if (pid == 0)
    {
        // Processo filho
        if (execvp(args[0], args) == -1)
        {
            perror("Erro ao executar comando");
        }
        exit(EXIT_FAILURE);
    }
    else
    {
        // Processo pai espera o filho terminar
        wait(NULL);
    }
}
int main()
{
    char input[MAX_COMMAND_LENGTH];

    while (1)
    {
        printf("gbash> ");
        fflush(stdout);

        // Le entrada do usuario
        if (fgets(input, MAX_COMMAND_LENGTH, stdin) == NULL)
        {
            break;
        }

        // Remove o '\n' no final
        input[strcspn(input, "\n")] = '\0';

        // Se for exite sai do shell
        if (strcspn(input, "exit") == 0)
        {
            break;
        }

        execute_command(input);
    }

    printf("Saindo do shell...\n");
    return 0;
}