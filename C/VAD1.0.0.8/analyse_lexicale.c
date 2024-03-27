#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h> 

enum valeur {VALEUR_LETTRE, VALEUR_CHAINE, VALEUR_ENTIER, VALEUR_DECIMALE, VALEUR_BOOLEEN};
enum variable {VARIABLE_LETTRE, VARIABLE_CHAINE, VARIABLE_ENTIER, VARIABLE_DECIMALE, VARIABLE_BOOLEEN, VARIABLE_STRUCTURE, VARIABLE_CONSTANTE, VARIABLE_FONCTION, VARIABLE_CLASSE};
enum operateurs { ADDITION, MULTIPLICATION, SOUSTRACTION, DIVISION, RESTE, MODULO, ET, OU, PAS, INFERIEUR, INFERIEUR_EGALE, SUPERIEUR, SUPERIEUR_EGALE, DIFFIRENT, EGALE_EGALE, EGALE_STRICT};
enum attribution {EGALE, PLUS_EGALE, MOINS_EGALE, DIVISE_EGALE, MULTIPLI_EGALE, RESTE_EGALE, MODULO_EGALE};
enum separateur {ESPACE, SAUT_DE_LIGNE};
enum charactere {SIMPLE_GUILLEMET_ANGLAIS, DOUBLE_GUILLEMET_ANGLAIS, CROCHET, ACOLADE, PARENTHESE};

struct Token {
    char* nomType;
    int type;
    char* valeur;
};

char SeparateurGarder[] = {'(',')','[',']','{','}','"','\'','+','-','*','=','%','<','>', '\n'};
bool guillemetOuvert = false;

int estSeparateur(char caractere) {
    return caractere == ' ' || caractere == '\0';
}

int estSeparateurGarder(char caractere) {
    for (size_t i = 0; i < sizeof(SeparateurGarder)/sizeof(SeparateurGarder[0]); i++)
    {
        if (SeparateurGarder[i] == caractere) {
            return 1;
        }
    }

    return 0;
}

struct Token* nouveauToken(const char* nomType, int type, const char* valeur) {
    struct Token* token = (struct Token*)malloc(sizeof(struct Token));
    token->nomType = strdup(nomType);
    token->type = type;
    token->valeur = strdup(valeur);
    printf("%s[%i,%s]\n", nomType, type, valeur);
    return token;
}

bool estEntier(const char *chaine) {
    char *fin;
    strtol(chaine, &fin, 10);  // Utilise la base 10
    return *fin == '\0';
}

bool estDecimale(const char *chaine) {
    char *fin;
    strtod(chaine, &fin);
    return *fin == '\0';
}

void analyseurLexem(char *chaine, int longueur) {
    
    // variable+fonction+classe
    if (strcasecmp(chaine, "lettre") == 0) {
        nouveauToken("variable", VARIABLE_LETTRE, chaine);
    }

    if (strcasecmp(chaine, "chaine") == 0) {
        nouveauToken("variable", VARIABLE_CHAINE, chaine);
    }

    if (strcasecmp(chaine, "entier") == 0) {
        nouveauToken("variable", VARIABLE_ENTIER, chaine);
    }

    if (strcasecmp(chaine, "decimale") == 0) {
        nouveauToken("variable", VARIABLE_DECIMALE, chaine);
    }

    if (strcasecmp(chaine, "booleen") == 0) {
        nouveauToken("variable", VARIABLE_BOOLEEN, chaine);
    }

    if (strcasecmp(chaine, "structure") == 0) {
        nouveauToken("variable", VARIABLE_STRUCTURE, chaine);
    }

    if (strcasecmp(chaine, "constante") == 0) {
        nouveauToken("variable", VARIABLE_CONSTANTE, chaine);
    }

    if (strcasecmp(chaine, "fonction") == 0) {
        nouveauToken("variable", VARIABLE_FONCTION, chaine);
    }

    if (strcasecmp(chaine, "classe") == 0) {
        nouveauToken("variable", VARIABLE_CLASSE, chaine);
    }

    // signe
    


    // signe
    if (strcmp(chaine, "+") == 0) {
        nouveauToken("signe", ADDITION, chaine);
    }

    if (strcmp(chaine, "*") == 0) {
        nouveauToken("signe", MULTIPLICATION, chaine);
    }

    if (strcmp(chaine, "-") == 0) {
        nouveauToken("signe", SOUSTRACTION, chaine);
    }

    if (strcmp(chaine, "/") == 0) {
        nouveauToken("signe", DIVISION, chaine);
    }

    if (strcmp(chaine, "%%") == 0) {
        nouveauToken("signe", MODULO, chaine);
    }

    if (strcasecmp(chaine, "et") == 0) {
        nouveauToken("signe", ET, chaine);
    }

    if (strcasecmp(chaine, "ou") == 0) {
        nouveauToken("signe", OU, chaine);
    }

    if (strcasecmp(chaine, "pas") == 0) {
        nouveauToken("signe", PAS, chaine);
    }

    if (strcmp(chaine, "<") == 0) {
        nouveauToken("signe", INFERIEUR, chaine);
    }

    if (strcmp(chaine, ">") == 0) {
        nouveauToken("signe", SUPERIEUR, chaine);
    }

    if (strcmp(chaine, "=") == 0) {
        nouveauToken("signe", EGALE, chaine);
    }

    // valeur
    if ((longueur == 1) && guillemetOuvert) {
        nouveauToken("valeur", VALEUR_LETTRE, chaine);
    }

    if (guillemetOuvert) {
        nouveauToken("valeur", VALEUR_CHAINE, chaine);
    }

    if (estEntier(chaine)) {
        nouveauToken("valeur", VALEUR_ENTIER, chaine);
    }

    if (estDecimale(chaine)) {
        nouveauToken("valeur", VALEUR_DECIMALE, chaine);
    }

    if (strcasecmp(chaine, "vrai") || strcasecmp(chaine, "faux") == 0) {
        nouveauToken("valeur", VALEUR_BOOLEEN, chaine);
    }
}

int main() {
    char codeSource[] = "entier x = 5\nentier y=3\nentier z=x+y\n";
    char sousChaine[100];
    int longueur = strlen(codeSource);
    int indiceDebut = 0;
    bool separateur = false;

    for (int i=0;i<longueur;i++) {
        if (estSeparateur(codeSource[i])) {
            int longueurSousChaine = i - indiceDebut;
            if (!separateur) {
                strncpy(sousChaine, codeSource + indiceDebut, longueurSousChaine);
                sousChaine[longueurSousChaine]='\0';
                analyseurLexem(sousChaine, longueurSousChaine);
                indiceDebut = i+1;
                separateur = true;
            }
            else {
                indiceDebut = i+1;
            }
        }
        else if (estSeparateurGarder(codeSource[i])) {
            int longueurSousChaine = i - indiceDebut;
            if (!separateur) {
                strncpy(sousChaine, codeSource + indiceDebut, longueurSousChaine);
                sousChaine[longueurSousChaine]='\0';
                analyseurLexem(sousChaine, longueurSousChaine);
                indiceDebut = i+1;
            }
            // Réinitialisation de la chaîne avec '\0'
            memset(sousChaine, '\0', sizeof(sousChaine));
            sousChaine[0]=codeSource[i];
            analyseurLexem(sousChaine, 1);
            separateur = true;
        }
        else {
            separateur = false;
        }

    }


    return 0;
}