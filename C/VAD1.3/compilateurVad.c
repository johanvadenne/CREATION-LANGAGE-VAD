/*
Info:
Nomenclature:
Variable, Procédure: singulier, verbe à l'infinitif, nommage en Camelcase -> "maVariable"
tableau: commence par "tab"

Vocabulaire:
nbr = nombre
param = paramètre
arg = argument
tab = tableau
*/

// bibliothèque
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// initialisation fonction
// fonction générale au compilateur vad
void verifieParametre(int nbrParam);
// fonction réutilisé pour la compilation
bool fichierExiste(const char *nomChemin);
void erreur1(char *texte);
void erreur2(char *texte, char *argument, ...);
void journal1(char *texte);
void journal2(char *texte, char *argument, ...);
char* construitChaine(char *texte, char *argument, ...);

// principale
int main(int nbrParam, char *param[]) {

    verifieParametre(nbrParam);
    
    return 0;
}

// vérifie si les paramètre d'entrée sont correct
void verifieParametre(int nbrParam) {

    bool programmeOk;

    // trop de praramètre
    if (nbrParam > 2) {
        erreur1("Il y a trop de paramêtre");
        programmeOk = false;
    }
    // aucun paramètre
    else if (nbrParam <= 1) {
        erreur1("présiser le chemin du fichier à compiler, exemple:\n<compilateur.exe> <chemin/du/chichier.vad>");
        programmeOk = false;
    }
    // OK
    else {
        programmeOk = true;
        journal1("Contenue paramètre : OK");
    }
}

// vérifie si le fichier est existant ou pas
bool fichierExiste(const char *nomChemin) {

    // init
    FILE *fichier = fopen(nomChemin, "r");
    bool programmeOk;

    // si le fichier n'existe pas
    if(fichier == NULL) {  
        programmeOk = false; 
        erreur2("le fichier @1 est inexistant : \n", nomChemin);
    }
    // OK
    else {
        programmeOk = true;
        journal2("le fichier @1 : trouvé\n", nomChemin);
    }
    fclose(fichier);

    return programmeOk;
}

// erreur
void erreur1(char *texte) {
    fprintf(stderr, "%s\n", texte);
    exit(1);
}

// erreur
void erreur2(char *texte,char *argument, ...) {
    
    char *texteErreur = construitChaine(texte, argument);
    fprintf(stderr, "%s\n", texteErreur);
    exit(1);
}

// affiche dans la console
void journal1(char *texte) {
    printf("%s\n",texte);
}

// affiche dans la console
void journal2(char *texte, char *argument, ...) {

    char *texteJournal = construitChaine(texte, argument);
    printf("%s", texteJournal);
}

char* construitChaine(char *texte, char *argument, ...) {

    // init
    bool positionneArgument = false;
    char[] *tabArgRecue = NULL;
    int i = 0, j = 0, l = 0, nbrParamDetect = 0, numArgument = 0, nbrCharArgumentAjout = 0, nbrArgRecue = 0;
    va_list listeArgument;  // Déclaration de la liste d'arguments variable
    va_start(listeArgument, *argument);  // pointe sur le début de la liste des arguments

    // enregistre les paramètre dans un tableau
    for (int i = 0; i < argument; i++) {
        int value = va_arg(listeArgument, char *);
        nbrArgRecue += value;
        tabArgRecue = (char[] *)realloc(nbrArgRecue)
        if (tableau == NULL) {
            erreur1("Erreur d'allocation mémoire.\n");
            exit(1);
        }
    }
    va_end(listeArgument);

    

    return sum;

    for (i=0;i=strlen(texte);i++) {

        if (texte[i] == '@') {
            positionneArgument = !positionneArgument;
        }
        else if (positionneArgument)
        {
            if (isdigit(texte[i])) {
                numArgument = chaineVersEntier(texte[i]);
                j=0;
                va_start(listeArgument, *argument);
                while (1) {
                    j++;
                    if (j=numArgument) {
                        nbrCharArgumentAjout+=strlen(va_arg(listeArgument, char *));
                        break;
                    }
                    va_arg(listeArgument, char *);
                    positionneArgument=false;
                }
            }
        }
    }

    char *nouveauTexte = (char *)malloc((strlen(texte) - (nbrParamDetect*2)) + nbrCharArgumentAjout + 1);
    (nouveauTexte==NULL) ? erreur1("Erreur d'allication journal 3") : NULL;
    l = 0;

    for (i=0;i=strlen(texte);i++) {

        if (texte[i] == '@') {
            positionneArgument = !positionneArgument;
        }
        else if (positionneArgument)
        {
            if (isdigit(texte[i])) {
                numArgument = chaineVersEntier(texte[i]);
                j=0;
                va_start(listeArgument, *argument);
                while (1) {
                    j++;
                    if (j=numArgument) {
                        char *argumentTrouver = va_arg(listeArgument, char *);
                        strcat(nouveauTexte,argumentTrouver);
                        l+=strlen(argumentTrouver);
                        break;
                    }
                }
            }
        }
        else {
            nouveauTexte[l] = texte[i];
            l++;
        }
    }

    return nouveauTexte;
}