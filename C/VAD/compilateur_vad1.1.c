#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdarg.h>
#include <ctype.h>

// déclaration
void journal(char *texte, char *argument, ...);
bool verifieParametre(int nbrParam);
bool fichierExiste(const char *nomChemin);
char* lectureFichier(const char *nomChemin);
int taille(char *tableau[]);
int chaineVersEntier(char *nombre);
void erreur(char *texte);



void erreur(char *texte) {
    journal(texte, NULL);
    exit(0);
}



int chaineVersEntier(char *nombreChaine) {

    int *nombreEntier = (int *)malloc(sizeof(int));

    if (isdigit(*nombreChaine)) {
        *nombreEntier = atoi(nombreChaine);
    }
    else {
        erreur("le paramètre n'est pas un entier!");
    }

    return *nombreEntier;
}



int taille(char *tableau[]) {

    // Calcul de la taille du tableau en octets.
    size_t taille = sizeof(*tableau);

    // Calcul du nombre d'éléments dans le tableau.
    int nombreElements = taille / sizeof(*tableau[0]);

    return nombreElements;
}



// affiche dans la console
void journal(char *texte, char *argument, ...) {

    // si il  y a des paramètre
    if (argument != NULL) {
        
        // init
        bool positionneArgument = false;
        int i = 0, j = 0, tailleTexteJournal = 0, nbrParamDetect = 0, numArgument = 0, nbrArgumentAjout = 0;
        va_list listeArgument;  // Déclaration de la liste d'arguments variable
        va_start(listeArgument, *argument);  // Initialisation de la liste d'arguments variable
        int nbrArgument = taille(&listeArgument);

        // parcours du texte pour calculer allocation du texte
        for (i=0;i=strlen(texte);i++) {

            // si détecte %
            if (*texte == '@') {
                if (positionneArgument) {
                    positionneArgument = false;
                }
                else {
                    positionneArgument = true;
                }
                texte++;
                continue;
            }
            
            if (positionneArgument) {
                
                if (isdigit(*texte)) {
                    numArgument = chaineVersEntier(texte);
                    if (numArgument <= nbrArgument) {
                        va_start(listeArgument, *argument);
                        do{
                            j++;
                            if (j == numArgument) {
                                printf("%s",va_arg(listeArgument, char *));
                                nbrArgumentAjout += strlen(va_arg(listeArgument, char *));
                                nbrParamDetect++;
                                j=0;
                                break;
                            }
                            else {
                                va_arg(listeArgument, const char *);
                            }
                        } while (j < nbrArgument);
                        (j!=0) ? erreur("Erreur interne journal 1") : texte++;
                        positionneArgument=false;
                        continue;
                    }
                    
                }
            }
            
            texte++;
        }

        char *nouveauTexte = (char *)malloc((strlen(texte) - (nbrParamDetect*2)) + nbrArgumentAjout + 1);
        (nouveauTexte==NULL) ? erreur("Erreur d'allication journal 3") : NULL;
        i = 0;

        while(*texte2) {

            // si détecte %
            if (*texte2 == '@') {
                if (positionneArgument) {
                    positionneArgument = false;
                }
                else {
                    positionneArgument = true;
                }
                *texte2++;
                continue;
            }

            if (positionneArgument) {
                if (isdigit(*texte2)) {
                    numArgument = chaineVersEntier(texte2);
                    if (numArgument <= nbrArgument) {
                        va_start(listeArgument, *argument);
                        do{
                            j++;
                            if (j == numArgument) {
                                printf("%s\n", va_arg(listeArgument, char *));
                                printf("%s\n", va_arg(listeArgument, char *));
                                char *test = va_arg(listeArgument, char *);
                                strcat(&nouveauTexte[i], test);
                                i+=nbrArgumentAjout+1;
                                j=0;
                                printf("test");
                                break;
                            }
                            else {
                                va_arg(listeArgument, const char *);
                            }
                        } while (j < nbrArgument);
                        (j!=0) ? erreur("Erreur interne journal 1") : *texte2++;
                        positionneArgument = false;
                        continue;
                    }
                    
                }
            }
            
            nouveauTexte[i] = *texte2;
            *texte2++;
            i++;
            
        }

        va_end(listeArgument);  // Nettoyage de la liste d'arguments variable
        printf("%s", *nouveauTexte);
        nouveauTexte[i] = '\0';
        free(nouveauTexte);
    
    }
    else {
        printf("%s\n", texte);
    }

}



// vérifie si les paramètre d'entrée sont correct
bool verifieParametre(int nbrParam) {

    bool programmeOk;

    // trop de praramètre
    if (nbrParam > 2) {
        journal("Il y a trop de paramêtre", NULL);
        programmeOk = false;
    }
    // aucun paramètre
    else if (nbrParam <= 1) {
        journal("présiser le chemin du fichier à compiler, exemple:\n<compilateur.exe> <chemin/du/chichier.vad>", NULL);
        programmeOk = false;
    }
    // OK
    else {
        programmeOk = true;
        journal("Contenue paramètre : OK", NULL);
    }
    return programmeOk;
}



// vérifie si le fichier est existant ou pas
bool fichierExiste(const char *nomChemin) {

    // init
    FILE *fichier = fopen(nomChemin, "r");
    bool programmeOk;

    // si le fichier n'existe pas
    if(fichier == NULL) {  
        programmeOk = false; 
        journal("le fichier @1 est inexistant : \n", (char *)nomChemin);
    }
    // OK
    else {
        programmeOk = true;
        journal("le fichier @1 : trouvé\n", (char *)nomChemin);
    }
    fclose(fichier);

    return programmeOk;
}



// lecture du fichier
char* lectureFichier(const char *nomChemin) {
    
    // init
    FILE *fichier;
    char *contenueFichier;

    // lecture
    fichier = fopen(nomChemin, "r");
    
    // si lecture erreur
    if(fichier == NULL) {  
        journal("le fichier %s est inexistant", (char *)nomChemin);
        contenueFichier = NULL;
    }
    // OK
    else {
        // Obtenir la taille du fichier
        fseek(fichier, 0, SEEK_END); // position curseur fin
        long taille = ftell(fichier);
        fseek(fichier, 0, SEEK_SET); // repositionement cusreur debut

        // Allouer de la mémoire pour contenueProgrammeVad
        contenueFichier = (char *)malloc(taille + 1); // +1 pour le caractère de fin de chaîne

        // Vérifier si l'allocation a réussi
        if (contenueFichier == NULL) {
            journal("Erreur d'allocation mémoire.", NULL);
            free(contenueFichier);
            contenueFichier = NULL;
        }
        else {
            // Lire le contenu ligne par ligne
            char *ligneProgrammeVad = (char *)malloc(taille+1);
            while(fgets(ligneProgrammeVad, sizeof(ligneProgrammeVad), fichier)) {  
                strcat(contenueFichier, ligneProgrammeVad); // Concaténer la ligne lue dans le contenu total
            }
            free(ligneProgrammeVad);
            journal("Lecture réussie.");
        }
    }  
    fclose(fichier);

    return contenueFichier;
}


// principale
int main(int nbrParam, char *param[]) {

    bool continueCompilation;
    char *programmeVad;

    continueCompilation = verifieParametre(nbrParam);
    (continueCompilation) ? continueCompilation = fichierExiste(param[1]) : exit(0);
    (continueCompilation) ? programmeVad = lectureFichier(param[1]) : exit(0);

}