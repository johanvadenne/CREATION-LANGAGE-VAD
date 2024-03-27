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
                printf(":%s\n",sousChaine);
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
                printf(":%s\n",sousChaine);
                indiceDebut = i+1;
            }
            // Réinitialisation de la chaîne avec '\0'
            memset(sousChaine, '\0', sizeof(sousChaine));
            sousChaine[0]=codeSource[i];
            printf(":%s\n",sousChaine);
            separateur = true;
        }
        else {
            separateur = false;
        }

    }


    return 0;
}