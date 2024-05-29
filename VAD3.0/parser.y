%{

#include "simple.h"
#include <string.h>

%}

/* L'union dans Bison est utilisee pour typer nos tokens ainsi que nos non terminaux. Ici nous avons declare une union avec deux types : nombre de type int et texte de type pointeur de char (char*) */
%union {
        long nombre_;
        char* texte_;
}

/* Nous avons ici les operateurs, ils sont definis par leur ordre de priorite. Si je definis par exemple la multiplication en premier et l'addition apres, le + l'emportera alors sur le * dans le langage. Les parenthese sont prioritaires avec %right */
//%left                   TOK_PLUS        TOK_MOINS       /* +- */
//%left                   TOK_MUL         TOK_DIV         /* /* */
//%left                   TOK_ET         /* et */
//%left                   TOK_OU          TOK_NON         /* ou non */
//%right                  TOK_PARG        TOK_PARD        /* () */


/* Nous avons la liste de nos expressions (les non terminaux). Nous les typons tous en texte (pointeur vers une zone de char). On a legitimement cree un non terminal variable afin d'isoler le token TOK_VAR et avoir une expression qui contiendra uniquement le nom de la variable */
%type<texte_>            declaration
%type<texte_>            expression
%type<texte_>            numerique
%type<texte_>            appelleFonctionLog


/* Nous avons la liste de nos tokens (les terminaux de notre grammaire) */
%token CHIFFRE LETTRE ENTIER DECIMALE BOOLEEN CHAINE TYPE_VARIABLE LOG VARIABLE AFFECTATION FIN_DE_LIGNE

%%

declaration:
    TYPE_VARIABLE VARIABLE
    | TYPE_VARIABLE VARIABLE AFFECTATION expression

expression:
    ENTIER
    | DECIMALE
    | BOOLEEN
    | CHAINE
    | expression '+' expression
    | numerique '-' numerique
    | numerique '*' numerique
    | numerique '/' numerique

numerique:
    ENTIER
    | DECIMALE

appelleFonctionLog:
    LOG '(' expression ')'

%%

void yyerror(const char *s) {
    fprintf(stderr, "Erreur: %s\n", s);
}

int main(int argc, char **argv) {
    if (yyparse() == 0) {
        printf("Analyse réussie\n");
    }
    return 0;
}
