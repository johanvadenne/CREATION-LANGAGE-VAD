#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h> 

enum valeurTypes {VALEUR_LETTRE, VALEUR_CHAINE, VALEUR_ENTIER, VALEUR_DECIMALE, VALEUR_BOOLEEN};
enum variableType {VARIABLE_LETTRE, VARIABLE_CHAINE, VARIABLE_ENTIER, VARIABLE_DECIMALE, VARIABLE_BOOLEEN, VARIABLE_STRUCTURE, VARIABLE_CONSTANTE, VARIABLE_FONCTION, VARIABLE_CLASSE};
enum operateurs { ADDITION, MULTIPLICATION, SOUSTRACTION, DIVISION, RESTE, MODULO, ET, OU, PAS, INFERIEUR, INFERIEUR_EGALE, SUPERIEUR, SUPERIEUR_EGALE, DIFFIRENT, EGALE_EGALE, EGALE_STRICT};
enum attribut {EGALE, PLUS_EGALE, MOINS_EGALE, DIVISE_EGALE, MULTIPLI_EGALE, RESTE_EGALE, MODULO_EGALE};
enum separateur {ESPACE, SAUT_DE_LIGNE};
enum charactere {SIMPLE_GUILLEMET_ANGLAIS, DOUBLE_GUILLEMET_ANGLAIS, CROCHET, ACOLADE, PARENTHESE};


// Structure pour stocker un token avec son type et sa valeur
struct Token {
    int type;
    char* valeur;
};

// Fonction pour créer un nouveau token
struct Token* nouveauToken(int type, const char* valeur) {
    struct Token* token = (struct Token*)malloc(sizeof(struct Token));
    token->type = type;
    token->valeur = strdup(valeur);
    return token;
}

// Fonction pour libérer la mémoire d'un token
void libererToken(struct Token* token) {
    free(token->valeur);
    free(token);
}

bool chaine(const char *variable, int longueur) {
    // Vérifie si la variable est une chaîne
    return (variable != NULL) && (strlen(variable) > 0) && (strcmp(variable[0], "\"") == 0) && (strcmp(variable[longueur], "\""));
}

bool entier(const char *chaine) {
    char *fin;
    strtol(chaine, &fin, 10);  // Utilise la base 10
    return *fin == '\0';
}

bool decimale(const char *chaine) {
    char *fin;
    strtod(chaine, &fin);
    return *fin == '\0';
}

// Fonction principale de l'analyseur lexical
struct Token* analyserLexeme(const char* lexeme) {
    // Logique de reconnaissance des lexèmes ici
    // Cette logique pourrait être implémentée à l'aide de fonctions comme strtok(), isdigit(), isalpha(), etc.
    int longueur = 0;
    while (lexeme[longueur] != '\0') {
        longueur++;
    }


    // variable
    if (strcasecmp(lexeme, "lettre") == 0) {
        return nouveauToken(VARIABLE_LETTRE, lexeme);
    }

    if (strcasecmp(lexeme, "chaine") == 0) {
        return nouveauToken(VARIABLE_CHAINE, lexeme);
    }

    if (strcasecmp(lexeme, "entier") == 0) {
        return nouveauToken(VARIABLE_ENTIER, lexeme);
    }

    if (strcasecmp(lexeme, "decimale") == 0) {
        return nouveauToken(VARIABLE_DECIMALE, lexeme);
    }

    if (strcasecmp(lexeme, "booleen") == 0) {
        return nouveauToken(VARIABLE_BOOLEEN, lexeme);
    }

    if (strcasecmp(lexeme, "[") == 0 || strcasecmp(lexeme, "]") == 0) {
        return nouveauToken(CROCHET, lexeme);
    }

    if (strcasecmp(lexeme, "structure") == 0) {
        return nouveauToken(VARIABLE_STRUCTURE, lexeme);
    }

    if (strcasecmp(lexeme, "constante") == 0) {
        return nouveauToken(VARIABLE_CONSTANTE, lexeme);
    }

    if (strcasecmp(lexeme, "fonction") == 0) {
        return nouveauToken(VARIABLE_FONCTION, lexeme);
    }

    if (strcasecmp(lexeme, "classe") == 0) {
        return nouveauToken(VARIABLE_CLASSE, lexeme);
    }


    // valeur
    if ((strlen(lexeme) > 1) && (isalpha((unsigned char) lexeme[0]))) {
        return nouveauToken(VALEUR_LETTRE, lexeme);
    }

    if (chaine(lexeme, longueur)) {
        return nouveauToken(VALEUR_CHAINE, lexeme);
    }

    if (entier(lexeme)) {
        return nouveauToken(VALEUR_ENTIER, lexeme);
    }

    if (decimale(lexeme)) {
        return nouveauToken(VALEUR_DECIMALE, lexeme);
    }

    if (strcasecmp(lexeme, "vrai") || strcasecmp(lexeme, "faux") == 0) {
        return nouveauToken(VALEUR_BOOLEEN, lexeme);
    }


    // cote
    if (strcasecmp(lexeme, "[") == 0 || strcasecmp(lexeme, "]") == 0) {
        return nouveauToken(CROCHET, lexeme);
    }

    if (strcasecmp(lexeme, "(") == 0 || strcasecmp(lexeme, ")") == 0) {
        return nouveauToken(PARENTHESE, lexeme);
    }

    if (strcasecmp(lexeme, "{") == 0 || strcasecmp(lexeme, "}") == 0) {
        return nouveauToken(ACOLADE, lexeme);
    }


    // signe
    if (strcmp(lexeme, "+") == 0) {
        return nouveauToken(ADDITION, lexeme);
    }

    if (strcmp(lexeme, "*") == 0) {
        return nouveauToken(MULTIPLICATION, lexeme);
    }

    if (strcmp(lexeme, "-") == 0) {
        return nouveauToken(SOUSTRACTION, lexeme);
    }

    if (strcmp(lexeme, "/") == 0) {
        return nouveauToken(DIVISION, lexeme);
    }

    if (strcmp(lexeme, "//") == 0) {
        return nouveauToken(RESTE, lexeme);
    }

    if (strcmp(lexeme, "%%") == 0) {
        return nouveauToken(MODULO, lexeme);
    }

    if (strcasecmp(lexeme, "et") == 0) {
        return nouveauToken(ET, lexeme);
    }

    if (strcasecmp(lexeme, "ou") == 0) {
        return nouveauToken(OU, lexeme);
    }

    if (strcasecmp(lexeme, "pas") == 0) {
        return nouveauToken(PAS, lexeme);
    }

    if (strcmp(lexeme, "<") == 0) {
        return nouveauToken(INFERIEUR, lexeme);
    }

    if (strcmp(lexeme, "<=") == 0) {
        return nouveauToken(INFERIEUR_EGALE, lexeme);
    }

    if (strcmp(lexeme, ">") == 0) {
        return nouveauToken(SUPERIEUR, lexeme);
    }

    if (strcmp(lexeme, ">=") == 0) {
        return nouveauToken(SUPERIEUR_EGALE, lexeme);
    }

    if (strcmp(lexeme, "<>") == 0) {
        return nouveauToken(DIFFIRENT, lexeme);
    }

    if (strcmp(lexeme, "==") == 0) {
        return nouveauToken(EGALE_EGALE, lexeme);
    }

    if (strcmp(lexeme, "===") == 0) {
        return nouveauToken(EGALE_STRICT, lexeme);
    }

    
    // affectation
    if (strcmp(lexeme, "=") == 0) {
        return nouveauToken(EGALE, lexeme);
    }

    if (strcmp(lexeme, "+=") == 0) {
        return nouveauToken(PLUS_EGALE, lexeme);
    }

    if (strcmp(lexeme, "-=") == 0) {
        return nouveauToken(MOINS_EGALE, lexeme);
    }

    if (strcmp(lexeme, "/=") == 0) {
        return nouveauToken(DIVISE_EGALE, lexeme);
    }

    if (strcmp(lexeme, "*=") == 0) {
        return nouveauToken(MULTIPLI_EGALE, lexeme);
    }

    if (strcmp(lexeme, "//=") == 0) {
        return nouveauToken(RESTE_EGALE, lexeme);
    }

    if (strcmp(lexeme, "%%=") == 0) {
        return nouveauToken(MODULO_EGALE, lexeme);
    }


    
    // séparation
    if (strcmp(lexeme, " ") == 0) {
        return nouveauToken(ESPACE, lexeme);
    }

    if (strcmp(lexeme, "\n") == 0) {
        return nouveauToken(SAUT_DE_LIGNE, lexeme);
    }

    return NULL;
}

int main() {
    char codeSource[] = "entier x = 5 + 3";

    // Découper le code source en lexèmes
    char* lexeme = strtok(codeSource, " ");
    while (lexeme != NULL) {
        // Analyser chaque lexème
        struct Token* token = analyserLexeme(lexeme);

        // Afficher le résultat
        if (token != NULL) {
            printf("Type: %d, Valeur: %s\n", token->type, token->valeur);
            libererToken(token);
        } else {
            printf("Lexème non reconnu : %s\n", lexeme);
        }

        // Passer au lexème suivant
        lexeme = strtok(NULL, " ");
    }


    return 0;
}