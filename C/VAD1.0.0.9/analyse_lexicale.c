#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h> 

enum valeur {VALEUR_LETTRE, VALEUR_CHAINE, VALEUR_ENTIER, VALEUR_DECIMALE, VALEUR_BOOLEEN};
enum typeVariable {VARIABLE_LETTRE, VARIABLE_CHAINE, VARIABLE_ENTIER, VARIABLE_DECIMALE, VARIABLE_BOOLEEN, VARIABLE_STRUCTURE, VARIABLE_CONSTANTE, VARIABLE_FONCTION, VARIABLE_CLASSE};
enum operateurs { ADDITION, MULTIPLICATION, SOUSTRACTION, DIVISION, RESTE, MODULO, ET, OU, PAS, INFERIEUR, INFERIEUR_EGALE, SUPERIEUR, SUPERIEUR_EGALE, DIFFIRENT, STRICT_EGALE};
enum attribution {EGALE, PLUS_EGALE, MOINS_EGALE, DIVISE_EGALE, MULTIPLI_EGALE, RESTE_EGALE, MODULO_EGALE};
enum separateur {ESPACE, SAUT_DE_LIGNE};
enum charactere {SIMPLE_GUILLEMET_ANGLAIS, DOUBLE_GUILLEMET_ANGLAIS, CROCHET, ACOLADE, PARENTHESE};
enum variable {VARIABLE};

struct Token {
    char* nomType;
    int type;
    char* valeur;
};

char *tabTypeVariable[] = {"lettre", "chaine", "lettre", "decimale", "booleen", "structure", "constante", "fonction", "classe"};
char *tabOperateurs[] = {"==", "*", "-", "/", "//", "%%", "et", "ou", "pas", "<", "<=", ">", ">=", "<>", "==="};
char *tabAttribution[] = {"=", "+=", "-=", "/=", "*=", "//=", "%%="};
char *tabCharactere[] = {"'", "\"", "[]", "{}", "()"};
char tabSeparateur[] = {' ', '\n'};
char tabSeparateurGarder[] = {'=', '+', '-','*', '-','<', '>','(', ')','{', '}','[', ']','\'', '"'};

bool estSeparateur(char lettre) {
    int taille = sizeof(tabSeparateur) / sizeof(tabSeparateur[0]);
    bool boolRetour = false;
    for (size_t i = 0; i < taille; i++)
    {
        if (tabSeparateur[i] == lettre) {
            boolRetour = true;
        }
    }
    return boolRetour;
}

bool estSeparateurGarder(char lettre) {
    int taille = sizeof(tabSeparateurGarder) / sizeof(tabSeparateurGarder[0]);
    bool boolRetour = false;
    for (size_t i = 0; i < taille; i++)
    {
        if (tabSeparateurGarder[i] == lettre) {
            boolRetour = true;
        }
    }
    return boolRetour;

}

void decoupage(char *codeSource, size_t  taille) {
    char **tabCodeSource = (char **)malloc(taille * sizeof(char *));;
    size_t indTabCodeSource = 0;
    int indDebut = 0;
    bool separateur = false;
    char *sousChaine = NULL;

    for (size_t i = 0; i < taille; i++)
    {
        char lettre = codeSource[i];
        if (estSeparateur(lettre) && !separateur) {
            int longueurSousChaine = i - indDebut;
            free(sousChaine);
            char *sousChaine = (char *)malloc(longueurSousChaine+1);
            sousChaine[longueurSousChaine] = '\0';
            strncpy(sousChaine, codeSource + indDebut, longueurSousChaine);
            printf("%s\n",sousChaine);
            tabCodeSource[indTabCodeSource] = sousChaine;
            indTabCodeSource++;
            indDebut=i+1;
            separateur = true;
        }
        else if (estSeparateurGarder(lettre)) {
            // if (separateur) 
            if (!separateur && codeSource[i-1] != ' ') {
                int longueurSousChaine = i - indDebut;
                free(sousChaine);
                char *sousChaine = (char *)malloc(longueurSousChaine+1);
                sousChaine[longueurSousChaine] = '\0';
                strncpy(sousChaine, codeSource + indDebut, longueurSousChaine);
                printf("%s\n",sousChaine);
                tabCodeSource[indTabCodeSource] = sousChaine;
                indTabCodeSource++;
                indDebut=i+1;
                separateur = true;
            }
            printf("%c\n",lettre);
        }
        else {
            if (separateur) {
                indDebut = i;
            }
            separateur = estSeparateur(lettre) || estSeparateurGarder(lettre);
        }
    }

    free(sousChaine);
}

int main() {
    char codeSource[] = "entier entierX = 5\n"
                        "entier entierY=3\n"
                        "entier entierZ=entierX+entierY\n"
                        "chaine chaineX = \"Bonjour \"\n"
                        "chaine chaineY=\"tout le monde\"\n"
                        "chaine chaineZ=chaineX+chaineY\n";
    
    size_t taille = sizeof(codeSource);
    
    decoupage(codeSource, taille);

    return 0;
}