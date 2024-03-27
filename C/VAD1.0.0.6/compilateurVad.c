
// bibliothèque
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdarg.h>
#include <ctype.h>

const char *typeVariableVAD[] = {"chaine", "entier", "decimale", "booleen", "tableau"};
const char *typeVariableC[] = {"char[]", "int", "float", "bool", "char[]"};
const int nbrTypeVariableVAD = sizeof(typeVariableVAD) / sizeof(typeVariableVAD[0]);

// initialisation fonction
void verifieParametre(int nbrParam);
bool fichierExiste(const char *nomChemin);
void erreur(char *texte);
void journal(const char *format, ...);
char *lectureFichier(const char *nomChemin);
int occurence(const char *chaine, const char *chaineOccurence);

// principale
int main(int nbrParam, char *param[])
{

    char *programmeVad;

    verifieParametre(nbrParam);
    fichierExiste(param[1]);
    programmeVad = lectureFichier(param[1]);
    return 0;
}

// vérifie si les paramètre d'entrée sont correct
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

void erreur(char *texte)
{
    fprintf(stderr, "%s\n", texte);
    exit(1);
}

void journal(const char *format, ...) {
    va_list args;
    va_start(args, format);
    vprintf(format, args);
    va_end(args);
    printf("\n");
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
    FILE *fichier = fopen(nomChemin, "r");
    if (fichier == NULL)
    {
        return NULL;
    }

    // Obtenir la taille du fichier
    fseek(fichier, 0, SEEK_END);
    long taille = ftell(fichier);
    fseek(fichier, 0, SEEK_SET);

    char *contenueFichier = (char *)malloc(taille + 1); // +1 pour le caractère nul
    if (contenueFichier == NULL)
    {
        fclose(fichier);
        return NULL;
    }

    contenueFichier[0] = '\0'; // Initialise la chaîne vide

    char *ligneProgrammeVad = (char *)malloc(taille + 1);
    if (ligneProgrammeVad == NULL)
    {
        free(contenueFichier);
        fclose(fichier);
        return NULL;
    }

    while (fgets(ligneProgrammeVad, taille, fichier))
    {
        // Concaténez la ligne lue à la chaîne principale
        strcat(contenueFichier, ligneProgrammeVad);
    }

    free(ligneProgrammeVad);
    fclose(fichier);
    return contenueFichier;
}

int occurence(const char *chaine, const char *chaineOccurence) {
    int lignes = 0;
    const char *ptr = chaine;

    while (*ptr != '\0') {
        if (*ptr == *chaineOccurence) {
            lignes++;
        }
        ptr++;
    }

    // Si la chaîne ne se termine pas par un caractère de nouvelle ligne, ajoutez 1 pour la dernière ligne
    if (ptr > chaine && *(ptr - 1) != *chaineOccurence) {
        lignes++;
    }

    return lignes;
}
