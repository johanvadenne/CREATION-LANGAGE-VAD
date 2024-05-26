%{
#include <stdio.h>
#include <stdlib.h>

// Déclarations de fonctions
void yyerror(const char *s);
int yywrap(void);
%}

CHIFFRE         [0-9]
LETTRE          [a-zA-Z]
ENTIER          [0-9]+
DECIMALE        [0-9]+\.[0-9]+
BOOLEEN         (vrai|faux)
CHAINE          (\"([^\\\"]|\\.)*\"|\'([^\\\"]|\\.)*\')
TYPE_VARIABLE   (lettre|chaine|entier|decimale|booleen)
PROCEDURE         (journal)

%%

"si"                { printf("KEYWORD: if\n"); }
"sinon"              { printf("KEYWORD: else\n"); }
"boucle"             { printf("KEYWORD: while\n"); }
"renvoyer"            { printf("KEYWORD: return\n"); }
{CHAINE}            { printf("CHAINE: %s\n", yytext); }
{ENTIER}            { printf("ENTIER: %s\n", yytext); }
{DECIMALE}          { printf("DECIMALE: %s\n", yytext); }
{BOOLEEN}           { printf("BOOLEEN: %s\n", yytext); }
{TYPE_VARIABLE}     { printf("TYPE_VARIABLE: %s\n", yytext); }
{PROCEDURE}           { printf("FONCTION: %s\n", yytext); }
{LETTRE}({LETTRE}|{CHIFFRE})* { printf("IDENTIFIER: %s\n", yytext); }
"+"                 { printf("SYMBOL: +\n"); }
"-"                 { printf("SYMBOL: -\n"); }
"*"                 { printf("SYMBOL: *\n"); }
"/"                 { printf("SYMBOL: /\n"); }
"="                 { printf("SYMBOL: =\n"); }
"("                 { printf("SYMBOL: (\n"); }
")"                 { printf("SYMBOL: )\n"); }
"{"                 { printf("SYMBOL: {\n"); }
"}"                 { printf("SYMBOL: }\n"); }
";"                 { printf("SYMBOL: ;\n"); }
[ \t\n]+            ; // Ignore les espaces blancs
.                   { printf("UNKNOWN: %s\n", yytext); }

%%

// Fonction principale
int main(int argc, char **argv) {
    if (argc > 1) {
        FILE *file = fopen(argv[1], "r");
        if (!file) {
            perror(argv[1]);
            return 1;
        }
        yyin = file;
    }
    yylex();
    return 0;
}

// Fonction d'erreur
void yyerror(const char *s) {
    fprintf(stderr, "Erreur: %s\n", s);
}

// Définition de yywrap
int yywrap(void) {
    return 1;
}
