#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdarg.h>
#include <ctype.h>



// déclaration
void journal1(char *texte);
void journal2(char *texte, char *argument, ...);
bool verifieParametre(int nbrParam);
bool fichierExiste(const char *nomChemin);
char* lectureFichier(const char *nomChemin);
int chaineVersEntier(char nombreChaine);
void erreur1(char *texte);
void erreur2(char *texte, char *argument, ...);
int tailleChaine(char *chaine);
int tailleTableau(char *tableau[]);



int chaineVersEntier(char nombreChaine) {
    int nombreEntier;

    if (isdigit(nombreChaine)) {
        nombreEntier = atoi(&nombreChaine);
    }
    else {
        erreur1("le paramètre n'est pas un entier!");
    }

    return nombreEntier;
}



// erreur
void erreur1(char *texte) {
    journal1(texte);
    exit(0);
}



// affiche dans la console
void journal1(char *texte) {
    printf("%s\n",texte);
}



// affiche dans la console
void journal2(char *texte, char *argument, ...) {

    // init
    bool positionneArgument = false;
    int i = 0, j = 0, l = 0, nbrParamDetect = 0, numArgument = 0, nbrCharArgumentAjout = 0;
    va_list listeArgument;  // Déclaration de la liste d'arguments variable
    va_start(listeArgument, *argument);  // Initialisation de la liste d'arguments variable

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

    printf("%s", nouveauTexte);

}



// vérifie si le fichier est existant ou pas
bool fichierExiste(const char *nomChemin) {

    // init
    FILE *fichier = fopen(nomChemin, "r");
    bool programmeOk;

    // si le fichier n'existe pas
    if(fichier == NULL) {  
        programmeOk = false; 
        journal2("le fichier @1 est inexistant : \n", (char *)nomChemin);
    }
    // OK
    else {
        programmeOk = true;
        journal2("le fichier @1 : trouvé\n", (char *)nomChemin);
    }
    fclose(fichier);

    return programmeOk;
}



// vérifie si les paramètre d'entrée sont correct
bool verifieParametre(int nbrParam) {

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
    return programmeOk;
}



// principale
int main(int nbrParam, char *param[]) {

    bool continueCompilation;
    char *programmeVad;

    continueCompilation = verifieParametre(nbrParam);
    (continueCompilation) ? continueCompilation = fichierExiste(param[1]) : exit(0);
}