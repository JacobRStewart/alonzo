#include <stdio.h>
#include <stdlib.h>

//Buffer for user input
static char buffer[2048];

//Function compilations for Windows runtimes
#ifdef _WIN2
#include <string.h>

//Pseudo-readline
char* readline(char* prompt) {
    fputs(prompt, stdout);;
    fgets(buffer, 2048, stdin);
    char* copy = malloc(strlen(buffer)+1);
    strcpy(copy, buffer);
    copy[strlen(copy)-1) = '/0';
    return copy;

}

//Pseudo-add_history
void add_history(char* unused) {}

#else

#include <editline/readline.h>
#include <editline/history.h>

#endif

int main(int argc, char** argv) {

    puts("Alonzo Version 0.1");
    puts("Press Ctrl+C to exit.");

    while (1) {
        
        //Output prompt and receive input
        char* input = readline("alonzo> ");
        
        //Add input to history
        add_history(input);

        printf("Indeed, %s\n", input);
        
        //Free input memory
        free(input);
    }

    return 0;

}
