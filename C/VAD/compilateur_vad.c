#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

#define try bool __HadError=false;
#define catch(x) ExitJmp:if(__HadError)
#define throw(x) {__HadError=true;goto ExitJmp;}

bool continueProgramme;
char *contenueProgrammeVad;
const char *variablesVad[] = {"chaine", "entier", "decimale", "booleen", "tableau ", "tableau ", "structure", "constante", "classe", "fonction", NULL};
const char chartereSnob = ' ';
//struct variable
//{
//    char chaine;
//    char entier;
//    char décimale;
//    char booleen;
//    char tableau;
//    char tableauCle;
//    char structure;
//    char constante;
//    char classe;
//    char fonction
//};


// vérifie si les paramètre d'entrée sont correct
void verifieParametre(int nbrParam) {

    // trop de praramètre
    if (nbrParam > 2) {
        printf("Il y a trop de paramêtre\n");
        continueProgramme = false;
    }
    // aucun paramètre
    else if (nbrParam <= 1) {
        printf("présiser le chemin du fichier à compiler, exemple:\n<compilateur.exe> <chemin/du/chichier.vad>\n");
        continueProgramme = false;
    }
    // OK
    else {
        continueProgramme = true;
        printf("Contenue paramètre : OK\n");
    }
}


// vérifie si le fichier est existant ou pas
bool fichierExiste(const char *nomChemin) {

    // init
    FILE *fichier = fopen(nomChemin, "r");

    // si le fichier n'existe pas
    if(fichier == NULL) {  
        continueProgramme = false; 
        printf("le fichier %s est inexistant : \n", nomChemin);
    }
    // OK
    else {
        continueProgramme = true;
        printf("le fichier %s : trouvé\n", nomChemin);
    }
    fclose(fichier);

    return continueProgramme;
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
        printf("le fichier %s est inexistant : \n", nomChemin);
        continueProgramme = false; 
    }
    // OK
    else {

        // Obtenir la taille du fichier
        fseek(fichier, 0, SEEK_END);
        long taille = ftell(fichier);
        fseek(fichier, 0, SEEK_SET);

        // Allouer de la mémoire pour contenueProgrammeVad
        contenueFichier = (char *)malloc(taille + 1); // +1 pour le caractère de fin de chaîne

        // Vérifier si l'allocation a réussi
        if (contenueFichier == NULL) {
            printf("Erreur d'allocation mémoire.\n");
            free(contenueFichier);
            continueProgramme = false;
        }
        else {
            // Lire le contenu ligne par ligne
            char *ligneProgrammeVad = (char *)malloc(taille+1);
            while(fgets(ligneProgrammeVad, sizeof(ligneProgrammeVad), fichier)) {  
                strcat(contenueFichier, ligneProgrammeVad); // Concaténer la ligne lue dans le contenu total
            }
            free(ligneProgrammeVad);
        }
    }  
    fclose(fichier);

    return contenueFichier;
}

// remplace une partie de chaine par une autre
char* remplace(const char *texte, const char *ancienTexte, const char *nouveauTexte) {
    
    // init
    int i, cnt = 0;
    int tailleAncienTexte = strlen(ancienTexte);
    int tailleNouveauTexte = strlen(nouveauTexte);
    char *resultatTexte;

    // boucle qui permettra de calculer l'allocation de la nouvelle chaine
    for (i=0; texte[i] != '\0'; i++) {
        // repère la position de l'ancienne chaine
        if (strstr(&texte[i], ancienTexte) == &texte[i]) {

            cnt++;
            i+=tailleAncienTexte-1;
        }
    }

    // allocation
    resultatTexte = (char *)malloc(i + cnt * (tailleNouveauTexte - tailleAncienTexte) + 1);
    
    // Vérifier si l'allocation a réussi
    if (resultatTexte == NULL) {
        printf("Erreur d'allocation mémoire.\n");
        free(resultatTexte);
    }
    else {
        i=0;
        while (*texte) {
        
            if (strstr(texte, ancienTexte) == texte) {
                strcpy(&resultatTexte[i], nouveauTexte);
                i += tailleNouveauTexte;
                texte += tailleAncienTexte;
                printf("%s\n",resultatTexte);
            }
            else
                resultatTexte[i++] = *texte++;
                printf("%s\n",resultatTexte);
        }
    }
    
    resultatTexte[i] = '\0';
    printf("%s\n", resultatTexte);
    return resultatTexte;
}

int taille(char *tableau) {
    
    // Calcul de la taille du tableau en octets.
    size_t taille = sizeof(tableau);

    // Calcul du nombre d'éléments dans le tableau.
    size_t nombreElements = taille / sizeof(tableau[0]);

    return nombreElements;
}

void convertionVadEnC(char *contenueFichier[]) {
    
    char *ligne;
    
    ligne = strtok(*contenueFichier, "\n");
    
    while (ligne != NULL) {
        printf("Ligne : %s\n", ligne);

        // Passage à la ligne suivante
        ligne = strtok(NULL, "\n");
    }
}

char* chaine(char *ligne) {

    const char charactereAffectation = '=';
    const char nomVariable[] = "char ";
    char *ligneC;
    int declarationNomVariable = 0;
    int i, j, k, l = 0; 

    if (strstr(ligne, &charactereAffectation) != NULL) {
        for (i=0;i<sizeof(ligne);i++) {
            if (strstr(&ligne[i], variablesVad[0]) == &ligne[i]) {
                i+=strlen(variablesVad[0])-1;
                declarationNomVariable = 1;
            }
            else if (declarationNomVariable == 2)
            {
                declarationNomVariable = 3;
                ligneC = (char *)malloc(j);
                for (k=i-j;k<i;k++) {
                    ligneC[l] = ligne[k];
                    l++;
                }
            }
            else if (strstr(&ligne[i], &chartereSnob) == &ligne[i])
            {
                if (declarationNomVariable == 1) {
                    j++;
                }
                else {
                    declarationNomVariable = 2;
                }
                continue;
            }
            
            
        }
    }

    printf("%s", *ligneC);

    return ligneC;
}

int main(int nbrParam, char *param[]) {

    try {
        char *contenueFichier;

        verifieParametre(nbrParam);
        (continueProgramme) ? fichierExiste(param[1]) : exit(0);
        (continueProgramme) ? contenueFichier = lectureFichier(param[1]) : exit(0);
        (continueProgramme) ? convertionVadEnC(contenueFichier) : exit(0);
        //(continueProgramme) ? continueProgramme = convertionVadEnC(contenueProgrammeVad, texteModif, texteNouv) : exit(0);
        return 0;
    }
    catch(...) {
        printf("Error\n");
    }

    

}