
// bibliothèque
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdarg.h>
#include <ctype.h>

const char *typeVariable[] = {"chaine", "entier", "decimale", "booleen", "tableau"};


// initialisation fonction
// fonction générale au compilateur vad
void verifieParametre(int nbrParam);
// fonction réutilisé pour la compilation
bool fichierExiste(const char *nomChemin);
void erreur(char *texte);
void journal(char *texte);
char* lectureFichier(const char *nomChemin);
void compilation(char *programmeVad);

// principale
int main(int nbrParam, char *param[]) {

    char *programmeVad;
    
    verifieParametre(nbrParam);
    fichierExiste(param[1]);
    programmeVad = lectureFichier(param[1]);
    journal(programmeVad);
    compilation(programmeVad);
    
}

// vérifie si les paramètre d'entrée sont correct
void verifieParametre(int nbrParam) {

    bool programmeOk;

    // trop de praramètre
    if (nbrParam > 2) {
        erreur("Il y a trop de parametre");
        programmeOk = false;
    }
    // aucun paramètre
    else if (nbrParam <= 1) {
        erreur("presiser le chemin du fichier à compiler, exemple:\n<compilateur.exe> <chemin/du/chichier.vad>");
        programmeOk = false;
    }
    // OK
    else {
        programmeOk = true;
        journal("Contenue parametre : OK");
    }
}

// erreur
void erreur(char *texte) {
    fprintf(stderr, "%s\n", texte);
    exit(1);
}

// affiche dans la console
void journal(char *texte) {
    printf("%s\n",texte);
}

// vérifie si le fichier est existant ou pas
bool fichierExiste(const char *nomChemin) {

    // init
    FILE *fichier = fopen(nomChemin, "r");
    char *texte;
    bool programmeOk;

    // si le fichier n'existe pas
    if(fichier == NULL) {  
        programmeOk = false; 
        erreur("le fichier est inexistant");
    }
    // OK
    else {
        programmeOk = true;
        journal("fichier trouve");
    }
    fclose(fichier);

    return programmeOk;
}

char* lectureFichier(const char *nomChemin) {
    FILE *fichier;
    char *contenueFichier = NULL;

    fichier = fopen(nomChemin, "r");

    if (fichier == NULL) {
        journal("Le fichier n'existe pas.");
    } else {
        // Obtenir la taille du fichier
        fseek(fichier, 0, SEEK_END);
        long taille = ftell(fichier);
        fseek(fichier, 0, SEEK_SET);

        contenueFichier = (char *)malloc(taille + 1); // +1 pour le caractère nul

        if (contenueFichier == NULL) {
            journal("Erreur d'allocation mémoire.");
        } else {
            char *ligneProgrammeVad = (char *)malloc(taille + 1);
            if (ligneProgrammeVad == NULL) {
                journal("Erreur d'allocation mémoire.");
            } else {
                contenueFichier[0] = '\0'; // Initialise la chaîne vide

                while (fgets(ligneProgrammeVad, taille, fichier)) {
                    // Concaténez la ligne lue à la chaîne principale
                    strcat(contenueFichier, ligneProgrammeVad);
                }
                free(ligneProgrammeVad);
                journal("Lecture réussie.");
            }
        }
    }
    fclose(fichier);

    return contenueFichier;
}

void compilation(char *programmeVad) {
    journal(programmeVad);

    // Tableau pour stocker les parties
    char *tabLigne[1]; // Vous pouvez ajuster la taille en fonction de vos besoins

    int index = 0;
    char *token = strtok(programmeVad, "\n");
    
    // Découpez la chaîne en utilisant '\n' comme délimiteur
    while (token != NULL) {
        // Allouez de la mémoire pour chaque ligne et copiez la partie découpée
        tabLigne[index] = (char *)malloc(strlen(token) + 1); // +1 pour le caractère nul
        if (tabLigne[index] != NULL) {
            strcpy(tabLigne[index], token);
            index++;
        }
        token = strtok(NULL, "\n");
    }

    // Affichez les parties découpées
    for (int i = 0; i < index; i++) {
        char *ligne = tabLigne[i];
        for (int j = 0; j < sizeof(typeVariable); j++)
        {
            char *variable = strcat(typeVariable[j], " ");
            if (strcmp(variable, ligne) == 0) {
                journal(strcat("La première ligne correspond à la variable recherchée : ", variable));
            } else {
                journal(strcat("La première ligne ne correspond pas à la variable recherchée : ", variable));
            }
            }
        
    }

    // Libérez la mémoire allouée
    for (int i = 0; i < index; i++) {
        free(tabLigne[i]);
    }
}