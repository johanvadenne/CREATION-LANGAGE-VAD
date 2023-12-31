
// bibliothèque
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdarg.h>
#include <ctype.h>

const char *typeVariableVAD[] = {"chaine"};
const char *typeVariableC[] = {"declareChaine(@1)"};
const int nbrTypeVariableVAD = sizeof(typeVariableVAD) / sizeof(typeVariableVAD[0]);

// initialisation fonction
void verifieParametre(int nbrParam);
bool declarationVariable(const char *chaine, char **programmeC);
void journalInt(int value);
void journalDouble(double value);
void journalChar(char value);
bool fichierExiste(const char *nomChemin);
void erreur(char *texte);
void journal(const char *format, ...);
char *lectureFichier(const char *nomChemin);
void compilation(char *programmeVad);
int occurence(const char *chaine, const char *chaineOccurence);
void ajouterTexte(char **texte, size_t *taille, const char *nouveauTexte);

// principale
int main(int nbrParam, char *param[])
{

    char *programmeVad;

    verifieParametre(nbrParam);
    fichierExiste(param[1]);
    programmeVad = lectureFichier(param[1]);
    compilation(programmeVad);
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

void journalInt(int value) {
    journal("%d", value);
}

void journalDouble(double value) {
    journal("%f", value);
}

void journalChar(char value) {
    journal("%c", value);
}

// vérifie si le fichier est existant ou pas
bool fichierExiste(const char *nomChemin)
{

    // init
    FILE *fichier = fopen(nomChemin, "r");
    char *texte;
    bool programmeOk;

    // si le fichier n'existe pas
    if (fichier == NULL)
    {
        programmeOk = false;
        erreur("le fichier est inexistant");
    }
    // OK
    else
    {
        programmeOk = true;
        journal("fichier trouve");
    }
    fclose(fichier);

    return programmeOk;
}

char *lectureFichier(const char *nomChemin)
{
    FILE *fichier;
    char *contenueFichier = NULL;

    fichier = fopen(nomChemin, "r");

    if (fichier == NULL)
    {
        journal("Le fichier n'existe pas.");
    }
    else
    {
        // Obtenir la taille du fichier
        fseek(fichier, 0, SEEK_END);
        long taille = ftell(fichier);
        fseek(fichier, 0, SEEK_SET);

        contenueFichier = (char *)malloc(taille + 1); // +1 pour le caractère nul

        if (contenueFichier == NULL)
        {
            journal("Erreur d'allocation mémoire.");
        }
        else
        {
            char *ligneProgrammeVad = (char *)malloc(taille + 1);
            if (ligneProgrammeVad == NULL)
            {
                journal("Erreur d'allocation mémoire.");
            }
            else
            {
                contenueFichier[0] = '\0'; // Initialise la chaîne vide

                while (fgets(ligneProgrammeVad, taille, fichier))
                {
                    // Concaténez la ligne lue à la chaîne principale
                    strcat(contenueFichier, ligneProgrammeVad);
                }
                free(ligneProgrammeVad);
                journal("Lecture reussie.");
            }
        }
    }
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

bool declarationVariable(const char *chaine, char **programmeC) {

    bool variableTrouve = false;

    for (int i = 0; i < nbrTypeVariableVAD; i++) {
        char variableRecherchee[strlen(typeVariableVAD[i]) + 2]; // +2 pour l'espace et le caractère nul
        snprintf(variableRecherchee, sizeof(variableRecherchee), "%s ", typeVariableVAD[i]);

        if (strncmp(chaine, variableRecherchee, strlen(variableRecherchee)) == 0) {
            variableTrouve = true;
            switch (expression)
            {
            case /* constant-expression */:
                /* code */
                break;
            
            default:
                break;
            }
            break;
        }
    }

    return variableTrouve;
}

void ajouterTexte(char **texte, size_t *taille, const char *nouveauTexte) {
    size_t nouvelleTaille = *taille + strlen(nouveauTexte) + 1;  // +1 pour le caractère nul
    *texte = (char *)realloc(*texte, nouvelleTaille);  // Réallouer de la mémoire pour le texte
    if (*texte != NULL) {
        strcat(*texte, nouveauTexte);  // Ajouter le nouveau texte
        *taille = nouvelleTaille - 1;  // Mettre à jour la taille
    }
}

void compilation(char *programmeVad)
{

    // détection du prmier utiliser
    // variable, classe, création fonction ou appelle fonction
    char *programmeC = NULL;
    int nbrLigne = occurence(programmeVad, "\n");
    char **tabLigne = (char **)malloc(occurence(programmeVad, "\n") * sizeof(char *));
    const char *pattern = "[^=]+=\"([^\"]+)\"";

    int index = 0;
    char *token = strtok(programmeVad, "\n");
    
    while (token != NULL) {
        tabLigne[index] = (char *)malloc(strlen(token) + 1);
        if (tabLigne[index] != NULL) {
            strcpy(tabLigne[index], token);
            index++;
        }
        token = strtok(NULL, "\n");
    }

    for (size_t i = 0; i < nbrLigne; i++)
    {
        journal(tabLigne[i]);
        
        if (declarationVariable(tabLigne[i], &programmeC)) {
            journal("OK");
        }
    }
}