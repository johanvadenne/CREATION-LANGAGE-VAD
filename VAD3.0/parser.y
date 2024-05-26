%{
#include <stdio.h>
#include <stdlib.h>

extern FILE *yyin;
void yyerror(const char *s);
int yylex(void);

%}

%token CHIFFRE LETTRE ENTIER DECIMALE BOOLEEN CHAINE TYPE_VARIABLE PROCEDURE IDENTIFIER

%%

program:
    program statement
    | statement
    ;

statement:
    "si" expression "{" statements "}"
    | "sinon" "{" statements "}"
    | "boucle" expression "{" statements "}"
    | "renvoyer" expression ";"
    | TYPE_VARIABLE IDENTIFIER "=" expression ";"
    | IDENTIFIER "=" expression ";"
    ;

expression:
    ENTIER
    | DECIMALE
    | BOOLEEN
    | CHAINE
    | IDENTIFIER
    | expression "+" expression
    | expression "-" expression
    | expression "*" expression
    | expression "/" expression
    ;

statements:
    statements statement
    | statement
    ;

%%

void yyerror(const char *s) {
    fprintf(stderr, "Erreur: %s\n", s);
}

int main(int argc, char **argv) {
    if (argc > 1) {
        FILE *file = fopen(argv[1], "r");
        if (!file) {
            perror(argv[1]);
            return 1;
        }
        yyin = file;
    }
    yyparse();
    return 0;
}
