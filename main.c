#include "nora.h"

int main(){
    // Initializing the prompt
    char *prompt = "Nora $ ";
    char *command = NULL;
    size_t bufsize = 0;
    // REPL loop
    while (1){
        // Default we gonna use size for 16 tokens
        int capacity = 16;
        char **args = malloc(capacity * sizeof(char *));
        // Check if the memory allocation success
        if (args == NULL){
            printf("Memory Allocation Failed: malloc()");
            exit(0);
        }
        // Printing the prompt
        printf("%s", prompt);
        // Force to print the prompt before getting any input
        fflush(stdout);
        // Getting the input string
        if (getline(&command, &bufsize, stdin) == -1){
            free(args);
            free(command);
            exit(0);
        }
        // Removing the newline from the input string
        command[strcspn(command, "\n")] = '\0';
        // Tokenizing the input string
        char *token = strtok(command, " ");
        int i = 0;
        while (token != NULL){
            if (i >= capacity - 1){
                capacity *=2;
                args = realloc(args, capacity * sizeof(char *));
                if (args == NULL){
                    printf("Memory Allocation Failed: realloc()");
                    free(args);
                    free(command);
                    exit(0);
                }
            }
            args[i] = token;
            token = strtok(NULL, " ");
            i++;
        }
        args[i] = NULL;

        // For commands
        if (args[0] != NULL){
            if (strcmp(args[0], "exit") == 0){ // Condition to exit from the shell
                free(args);
                free(command);
                exit(0);
            }else if(strcmp(args[0], "echo") == 0){
                nora_echo(args);
            }else if(strcmp(args[0], "type") == 0){
                nora_type(args);
            }else{
                printf("Command Not Found: %s", args[0]);
            }
        }
        free(args);
    }
    free(command);
    return 0;
}