/*
exemple code:
chaine texte = "mon texte"
journal(texte)
*/

// recupère le code
// découpe en tableau le code par tout les charactère spéciaux ainsi que les espace et les saut à la ligne (garder les charactère spéciaux)

// cas déclaration (ou le premier mot est la déclaration d'une variable)
// récupère le nom de la variable qui suis
// si un "=" suis alors vérifier si la valeur est compatible avec la variable déclarer
// si tout est OK écrie la ligne en C

#include <stdio.h>
#include <string.h>

void journal(char *texte) {
    printf("%s\n", texte);
}

void traiterCode(char *code) {
    char *token = strtok(code, " \t\n");
    
    while (token != NULL) {
        // Traitement du code ici
        if (strcmp(token, "chaine") == 0) {
            // Traitement des déclarations de chaînes
            token = strtok(NULL, " \t\n");  // Récupération du nom de la variable
            printf("char *%s[]\n", token);
            // ...

        } else if (strcmp(token, "journal") == 0) {
            // Traitement des appels à la fonction journal
            token = strtok(NULL, " \t\n");  // Récupération du texte ou du paramètre
            printf("journal(%s)", token);
            // ...

        } else {
            // Gérer d'autres cas de code ici
        }

        token = strtok(NULL, " \t\n");  // Passage au token suivant
    }
}

int main() {
    char code[] = "chaine texte = \"mon texte\"\njournal(texte)";
    traiterCode(code);

    return 0;
}
