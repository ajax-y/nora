#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(){

    char *prompt = "(Nora) $ ";
    char *command = NULL;
    size_t bufsize = 0;
    while(1){
        // Start with space for 16 token
        int capacity = 16;
        char **args = malloc(capacity * sizeof(char *));
        if (args == NULL){
            printf("Memory Allocation Failed: malloc()");
            exit(0);
        }
        // Printing the prompt
        printf("%s",prompt);
        // Force to print the prompt before getting any input
        fflush(stdout);
        // Getting the input entered by the user and if the user press Ctrl + D to tell end of the file the program need to exit
        if(getline(&command, &bufsize, stdin) == -1){
            break;
        }
        // Removing the new line from the string
        command[strcspn(command, "\n")] = '\0';
        // Tokenizing the input string from the user
        char *token = strtok(command, " ");

        int i = 0;
        while (token != NULL){
            if (i >= capacity - 1){
                capacity *=2;
                args = realloc(args, capacity * sizeof(char *));
                if (args == NULL){
                    printf("Memory Allocation Failed: realloc()");
                    exit(0);
                }
            }
            args[i] = token;
            token = strtok(NULL, " ");
            i++;
        }
        args[i] = NULL;

        if(args[0] != NULL){
            if (strcmp(args[0], "exit") == 0){ // Condition to exit
                free(args);
                break;
            }else if(strcmp(args[0], "echo") == 0){ // Condition to check if the command is echo
                for (int j = 1; args[j] != NULL; j++){
                    printf("%s", args[j]);

                    if (args[j+1] != NULL){
                        printf(" ");
                    }
                }
                printf("\n");
            }else if(strcmp(args[0], "type") == 0){ // Condition for type command
                if(strcmp(args[1], "exit") == 0){
                    printf("Built-in command: %s\n",args[1]);
                }else if(strcmp(args[1], "echo") == 0){
                    printf("Built-in command: %s\n",args[1]);
                }else if(args[1] == NULL){
                    printf("Command not provided\n");
                }else{
                    printf("Unknow command: %s\n", args[1]);
                }
            }
            else{ // Condition for the invalid commands
                printf("Command not found: %s\n", args[0]);
            }
        }
    }

    free(command);
    return 0;
}