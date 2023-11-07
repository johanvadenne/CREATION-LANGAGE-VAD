#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdarg.h>
#include <ctype.h>

void verifieParametre(int nbrParam);
char *declareChaine(const char *chaine);
void affecteChaine(char **variable, const char *chaineAffecte);
void journal(char *chaine, ...);
void erreur(char *chaine, ...);
char *construitChaine(char *chaine, char **param);
bool fichierExiste(const char *nomChemin);
char *lectureFichier(const char *nomChemin);


int main(int nbrParam, char *param[]) {
    journal("@1", "", NULL);
    verifieParametre(nbrParam);
    if (!fichierExiste(param[1])) { erreur("le fichier @1 est introuvable", param[1]); } else { journal("chemin \"@1\" trouve", param[1]); }
    char *programmeVad = lectureFichier(param[1]);
    journal(programmeVad);

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


void journal(char *chaine, ...) {
    va_list vargs;
    va_start(vargs, chaine);
    int nbrParam = 0;
    char **tabParametre = NULL;

    while (1) {
        char *param = va_arg(vargs, char*);
        if (param == NULL) {
            break;
        }
        tabParametre = (char **)realloc(tabParametre, (nbrParam + 1) * sizeof(char *));
        if (tabParametre != NULL ) {
            tabParametre[nbrParam] = (char *)malloc(strlen(param) + 1);
            if (tabParametre[nbrParam] != NULL) {
                strcpy(tabParametre[nbrParam], param);
                nbrParam++;
            }
        }
    };

    char *nouvelleChaine = construitChaine(chaine, tabParametre);
    printf("%s\n", nouvelleChaine);

    free(nouvelleChaine);
    for (int i = 0; i < nbrParam; i++) {
        free(tabParametre[i]);
    }
    free(tabParametre);
    va_end(vargs);
}

void erreur(char *chaine, ...) {
    va_list vargs;
    va_start(vargs, chaine);
    int nbrParam = 0;
    char **tabParametre = NULL;

    while (1) {
        char *param = va_arg(vargs, char*);
        if (param == NULL) {
            break;
        }
        tabParametre = (char **)realloc(tabParametre, (nbrParam + 1) * sizeof(char *));
        if (tabParametre != NULL ) {
            tabParametre[nbrParam] = (char *)malloc(strlen(param) + 1);
            if (tabParametre[nbrParam] != NULL) {
                strcpy(tabParametre[nbrParam], param);
                nbrParam++;
            }
        }
    };

    char *nouvelleChaine = construitChaine(chaine, tabParametre);
    printf("%s\n", nouvelleChaine);

    free(nouvelleChaine);
    for (int i = 0; i < nbrParam; i++) {
        free(tabParametre[i]);
    }
    free(tabParametre);
    va_end(vargs);
    exit(1);
}

char *construitChaine(char *chaine, char **tabParam) {

    int allocMemoire = strlen(chaine);
    char *pos = strstr(chaine, "@");
    while (pos != NULL) {
        int numero;
        if (pos > chaine) {
            numero = atoi(pos + 1)-1;
        } else {
            numero = -1;
        }

        if (numero >= 0 && numero < sizeof(tabParam)) {
            const char *argument = tabParam[numero];
            if (argument != NULL) {
                allocMemoire += strlen(argument)-2;
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
            if (numArgument >= 0 && numArgument < sizeof(tabParam)) {
                const char *argument = tabParam[numArgument];
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
        erreur("presiser le chemin du fichier a compiler");
        programmeOk = false;
    }
    // OK
    else
    {
        programmeOk = true;
        journal("Contenue parametre : OK");
    }
}

bool fichierExiste(const char *nomChemin)
{
    FILE *fichier = fopen(nomChemin, "r");
    if (fichier != NULL)
    {
        fclose(fichier);
        return true;
    }
    return false;
}


char *lectureFichier(const char *nomChemin)
{
    FILE *fichier;
    char *contenueFichier = NULL;

    fichier = fopen(nomChemin, "r");

    if (fichier != NULL)
    {
        // Obtenir la taille du fichier
        fseek(fichier, 0, SEEK_END);
        long taille = ftell(fichier);
        fseek(fichier, 0, SEEK_SET);

        contenueFichier = (char *)malloc(taille + 1); // +1 pour le caractère nul

        if (contenueFichier != NULL)
        {
            char *ligneProgrammeVad = (char *)malloc(taille + 1);
            if (ligneProgrammeVad != NULL)
            {
                contenueFichier[0] = '\0'; // Initialise la chaîne vide

                while (fgets(ligneProgrammeVad, taille, fichier))
                {
                    // Concaténez la ligne lue à la chaîne principale
                    strcat(contenueFichier, ligneProgrammeVad);
                }
                free(ligneProgrammeVad);
            }
        }
    }
    fclose(fichier);

    return contenueFichier;
}