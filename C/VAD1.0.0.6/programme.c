#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdarg.h>
#include <ctype.h>

void verifieParametre(int nbrParam);
char *declareChaine(const char *chaine);
void affecteChaine(char **variable, const char *chaineAffecte);
void verifieParametre(int nbrParam);
void journal(char *chaine, ...);
void erreur(char *chaine, ...);


int main(int nbrParam, char *param[]) {
    verifieParametre(nbrParam);

    return 0;
}

void affecteChaine(char **variable, const char *chaineAffecte) {
    *variable = (char *)realloc(*variable, strlen(chaineAffecte) + 1);  // Réalloue la mémoire
    strcpy(*variable, chaineAffecte);  // Copie la nouvelle chaîne
}

char *declareChaine(const char *chaine) {
    char *nouvelleChaine = (char *)malloc(strlen(chaine) + 1);
    strcpy(nouvelleChaine, chaine);
    return nouvelleChaine;
}

void verifieParametre(int nbrParam)
{

    bool programmeOk;

    // trop de praramètre
    if (nbrParam > 2)
    {
        erreur("Il y a trop de parametre");
        programmeOk = false;
    }
    // aucun paramètre
    else if (nbrParam <= 1)
    {
        erreur("presiser le chemin du fichier à compiler, exemple:\n<compilateur.exe> <chemin/du/chichier.vad>");
        programmeOk = false;
    }
    // OK
    else
    {
        programmeOk = true;
        journal("Contenue parametre : OK");
    }
}

void journal(char *chaine, ...) {
    va_list vargs;
    va_start(vargs, chaine);
    int nbrParam = 0;
    char **tabParametre = NULL;
    int allocMemoire = strlen(chaine);

    while (1) {
        char *test2 = va_arg(vargs, char*);
        if (test2 == NULL) {
            break;
        }
        tabParametre = (char **)realloc(tabParametre, (nbrParam + 1) * sizeof(char *));
        if (tabParametre != NULL) {
            tabParametre[nbrParam] = (char *)malloc(strlen(test2) + 1);
            if (tabParametre[nbrParam] != NULL) {
                strcpy(tabParametre[nbrParam], test2);
                nbrParam++;
            }
        }
    };

    char *pos = strstr(chaine, "@");
    while (pos != NULL) {
        int numero;
        if (pos > chaine) {
            numero = atoi(pos + 1)-1;
        } else {
            numero = -1;
        }

        if (numero >= 0 && numero < nbrParam) {
            const char *argument = tabParametre[numero];
            if (argument != NULL) {
                allocMemoire += strlen(argument)-2;
                printf("Argument trouvé : %s\n", argument);
            }
        }
        pos = strstr(pos + 1, "@");
    }

    char *nouvelleChaine = (char *)malloc(allocMemoire + 1); // +1 pour le caractère nul
    nouvelleChaine[0] = '\0';

    for (int i = 0; chaine[i] != '\0'; i++) {
        if (chaine[i] == '@') {
            i++;
            int numArgument = atoi(&chaine[i]) - 1;
            if (numArgument >= 0 && numArgument < nbrParam) {
                const char *argument = tabParametre[numArgument];
                if (argument != NULL) {
                    strncat(nouvelleChaine, argument, strlen(argument));
                } else {
                    strncat(nouvelleChaine, "@", 1); // Argument non trouvé, ajoute un "@"
                }
            } else {
                strncat(nouvelleChaine, "@", 1); // Numéro d'argument hors limites, ajoute un "@"
            }
        } else {
            strncat(nouvelleChaine, &chaine[i], 1);
        }
    }

    printf("%s\n", nouvelleChaine);

    free(nouvelleChaine);
    for (int i = 0; i < nbrParam; i++) {
        free(tabParametre[i]);
    }
    free(tabParametre);
    va_end(vargs);
}