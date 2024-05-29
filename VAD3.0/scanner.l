%{
#include "simple.h"
%}

CHIFFRE         [0-9]
LETTRE          [a-zA-Z]
ENTIER          [0-9]+
DECIMALE        [0-9]+\.[0-9]+
BOOLEEN         (vrai|faux)
CHAINE          (\"([^\\\"]|\\.)*\"|\'([^\\\"]|\\.)*\')
TYPE_VARIABLE   (lettre|chaine|entier|decimale|booleen)

%%

"si" { return 'si'; }
"sinon" { return 'sinon'; }
"boucle" { return 'boucle'; }
"renvoyer" { return 'renvoyer'; }
{CHAINE} { yylval.str = strdup(yytext); return CHAINE; }
{ENTIER} { yylval.intval = atoi(yytext); return ENTIER; }
{DECIMALE} { yylval.floatval = atof(yytext); return DECIMALE; }
{BOOLEEN} { yylval.boolval = strcmp(yytext, "vrai") == 0; return BOOLEEN; }
{TYPE_VARIABLE} { return TYPE_VARIABLE; }
"log" { return LOG; }
{LETTRE}({LETTRE}|{CHIFFRE})* { yylval.str = strdup(yytext); return VARIABLE; }
"+" { return '+'; }
"-" { return '-'; }
"*" { return '*'; }
"/" { return '/'; }
"=" { return AFFECTATION; }
"(" { return '('; }
")" { return ')'; }
"{" { return '{'; }
"}" { return '}'; }
";" { return ';'; }
"\n" { return FIN_DE_LIGNE; }
[ \t\n]+ ; // Ignore les espaces blancs
. { printf("UNKNOWN: %s\n", yytext); }

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
