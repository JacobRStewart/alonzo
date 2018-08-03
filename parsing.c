#include <stdio.h>
#include <stdlib.h>
#include "mpc.h"
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
    
    /* Create Some Parsers */
    mpc_parser_t* Number   = mpc_new("number");
    mpc_parser_t* Operator = mpc_new("operator");
    mpc_parser_t* Expr     = mpc_new("expr");
    mpc_parser_t* Alonzo    = mpc_new("alonzo");

    /* Define them with the following Language */
    mpca_lang(MPCA_LANG_DEFAULT,
      "                                                     \
        number   : /-?[0-9]+/ ;                             \
        operator : '+' | '-' | '*' | '/' ;                  \
        expr     : <number> | '(' <operator> <expr>+ ')' ;  \
        alonzo    : /^/ <operator> <expr>+ /$/ ;             \
      ",
      Number, Operator, Expr, Alonzo);

    puts("Alonzo Version 0.1");
    puts("Press Ctrl+C to exit.");

    while (1) {

        //Output prompt and receive input
        char* input = readline("alonzo> ");

        //Add input to history
        add_history(input);

        /* Attempt to Parse the user Input */
        mpc_result_t r;
        if (mpc_parse("<stdin>", input, Alonzo, &r)) {

            /* On Success Print the AST */
            mpc_ast_print(r.output);
            mpc_ast_delete(r.output);

        } else {

            /* Otherwise Print the Error */
            mpc_err_print(r.error);
            mpc_err_delete(r.error);

        }

        //Free input memory
        free(input);

    }

    /* Undefine and Delete our Parsers */
    mpc_cleanup(4, Number, Operator, Expr, Alonzo);

    return 0;

}
