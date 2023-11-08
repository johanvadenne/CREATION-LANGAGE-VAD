#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdarg.h>
#include <ctype.h>

void verifieParametre(int nbrParam);
char *declareChaine(const char *chaine);
void affecteChaine(char **variable, const char *chaineAffecte);
void concateChaine(char **variable, ...);
void journal(const char *chaine, ...);
void erreur(const char *chaine, ...);
char *construitChaine(const char *chaine, char **param);
bool fichierExiste(const char *nomChemin);
char *lectureFichier(const char *nomChemin);
void compilation(char *programmeVad);
int occurence(const char *chaine, const char *chaineOccurence);
bool declarationVariable(const char *chaine, char **programmeC);
int taille(char **tableau);


const char *typeVariableVAD[] = {"chaine"};
const char *typeVariableC[] = {"char *@1 declareChaine(@2);"};

int main(int nbrParam, char *param[]) {
    journal("@1", "", NULL);
    verifieParametre(nbrParam);
    if (!fichierExiste(param[1])) { erreur("le fichier @1 est introuvable", param[1]); } else { journal("chemin \"@1\" trouve", param[1]); }
    char *programmeVad = lectureFichier(param[1]);
    compilation(programmeVad);

    return 0;
}

int taille(char **tableau) {
    int i = 0;
    while (tableau[i] != '\0') {
        i++;
    }
    return i;
}

void affecteChaine(char **variable, const char *chaineAffecte) {
    *variable = (char *)realloc(*variable, strlen(chaineAffecte) + 1);  // Réalloue la mémoire
    strcpy(*variable, chaineAffecte);  // Copie la nouvelle chaîne
}

void concateChaine(char **variable, ...) {
    va_list vargs;
    va_start(vargs, variable);
    int nbrParam = 0;
    char **tabParametre = NULL;
    int tailleChaine = 0;

    while (1) {
        char *param = va_arg(vargs, char*);
        if (param == NULL) {
            break;
        }
        tabParametre = (char **)realloc(tabParametre, (nbrParam + 1) * sizeof(char *));
        if (tabParametre != NULL ) {
            tabParametre[nbrParam] = (char *)malloc(strlen(param) + 1);
            tailleChaine+=strlen(param);
            if (tabParametre[nbrParam] != NULL) {
                strcpy(tabParametre[nbrParam], param);
                nbrParam++;
            }
        }
    };


    *variable = (char *)realloc(*variable, tailleChaine+1);
    for (size_t i = 0; i < taille(tabParametre); i++)
    {
        journal("test", NULL);
        journal(tabParametre[i], NULL);
        journal("test", NULL);
    }
    
}

char *declareChaine(const char *chaine) {
    
    char *nouvelleChaine;
    if (chaine == NULL) {
        nouvelleChaine = (char *)malloc(strlen(chaine) + 1);
        strcpy(nouvelleChaine, chaine);
    }
    return nouvelleChaine;
}


void journal(const char *chaine, ...) {
    va_list vargs;
    va_start(vargs, chaine);
    int nbrParam = 0;
    char **tabParametre;

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

    printf("%i", nbrParam);
    printf("%i", taille(tabParametre));
    char *nouvelleChaine = construitChaine(chaine, tabParametre);
    printf("%s\n", nouvelleChaine);

    free(nouvelleChaine);
    for (int i = 0; i < nbrParam; i++) {
        free(tabParametre[i]);
    }
    free(tabParametre);
    va_end(vargs);
}

void erreur(const char *chaine, ...) {
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

char *construitChaine(const char *chaine, char **tabParam) {
    int allocMemoire = strlen(chaine);
    char *pos = strstr(chaine, "@");
    while (pos != NULL) {
        int numero;
        if (pos > chaine) {
            numero = atoi(pos + 1)-1;
        } else {
            numero = -1;
        }

        if (numero >= 0 && numero < taille(tabParam)) {
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
            if (numArgument >= 0 && numArgument < taille(tabParam)) {
                printf("%i", numArgument);
                printf("%i", taille(tabParam));
                printf("%s est", tabParam[0]);
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
        erreur("Il y a trop de parametre", NULL);
        programmeOk = false;
    }
    // aucun paramètre
    else if (nbrParam <= 1)
    {
        erreur("presiser le chemin du fichier a compiler", NULL);
        programmeOk = false;
    }
    // OK
    else
    {
        programmeOk = true;
        journal("Contenue parametre : OK", NULL);
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

void compilation(char *programmeVad)
{

    // détection du prmier utiliser
    // variable, classe, création fonction ou appelle fonction
    char *programmeC = NULL;
    int nbrLigne = occurence(programmeVad, "\n");
    char **tabLigne = (char **)malloc(occurence(programmeVad, "\n") * sizeof(char *));

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
        journal(tabLigne[i],NULL);
        if (declarationVariable(tabLigne[i], &programmeC)) {
            journal("OK", NULL);
        }
    }
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
    int tabMot = 0;
    tabMot += occurence(chaine, " ");
    tabMot += occurence(chaine, "=");

    for (int i = 0; i < sizeof(typeVariableVAD); i++) {
        char variableRecherchee[strlen(typeVariableVAD[i]) + 2]; // +2 pour l'espace et le caractère nul
        snprintf(variableRecherchee, sizeof(variableRecherchee), "%s ", typeVariableVAD[i]);

        if (strncmp(chaine, variableRecherchee, strlen(variableRecherchee)) == 0) {
            variableTrouve = true;
            if (typeVariableVAD[i] == "chaine") {
                concateChaine(programmeC, typeVariableC[i], NULL);
                journal(*programmeC, NULL);
            }
            break;
        }
    }

    return variableTrouve;
}
