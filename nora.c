#include "nora.h"

void nora_echo(char **args){ // Function for the echo command
    int i = 1;
    while (args[i] != NULL){
        printf("%s", args[i]);
        
        if (args[i+1] != NULL){
            printf(" ");
        }
        i++;
    }
    printf("\n");
    return;
}

void nora_type(char **args){ // Function for the type command
    if (args[1] != NULL && args[2] == NULL){
        if (strcmp(args[1], "echo") == 0){ // Condition for echo
            printf("Built-in Command: %s\n", args[1]);
        }else if(strcmp(args[1], "exit") == 0){ // Condition for exit
            printf("Built-in Command: %s\n", args[1]);
        }else if(strcmp(args[1], "type") == 0){ // Condition for type
            printf("Built-in Command: %s\n", args[1]);
        }else{ // Condition for the command not found
            printf("Command Not Found: %s\n", args[1]);
        }
    }else if (args[1] == NULL){ // Condtion for the command not provided
        printf("Command is not provided\n");
    }else{ // Condition for the extra arguments
        printf("The type command just need one argument\n");
    }
    return;
}