#include <stdio.h>
#include <stdlib.h>
#include <string.h>


char *declareChaine(const char *chaine)
void affecteChaine(char **variable, const char *chaineAffecte)
void verifieParametre(int nbrParam);


int main() {
    char *chaine = declareChaine("test");
    printf("%s\n", chaine);
    affecteChaine(&chaine, "test test");
    printf("%s\n", chaine);
    free(chaine);

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