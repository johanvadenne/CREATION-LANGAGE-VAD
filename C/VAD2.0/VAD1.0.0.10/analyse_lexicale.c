#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h> 

bool estSeparateur(char lettre);
bool estSeparateurGarder(char lettre);
void decoupage(char *codeSource, size_t  taille);
bool estDeclaration(char *chaine);
bool nomVariableValide(char *nomVariable);
void tradVAD (char *chaine);
bool estEntier(char *chaine);
bool estOperateur(char *chaine);

enum typeVariable {VARIABLE_LETTRE, VARIABLE_CHAINE, VARIABLE_ENTIER, VARIABLE_DECIMALE, VARIABLE_BOOLEEN, VARIABLE_STRUCTURE, VARIABLE_CONSTANTE, VARIABLE_FONCTION, VARIABLE_CLASSE};
enum valeur {VALEUR_LETTRE, VALEUR_CHAINE, VALEUR_ENTIER, VALEUR_DECIMALE, VALEUR_BOOLEEN};
enum operateurs { ADDITION, MULTIPLICATION, SOUSTRACTION, DIVISION, RESTE, MODULO, ET, OU, PAS, INFERIEUR, INFERIEUR_EGALE, SUPERIEUR, SUPERIEUR_EGALE, DIFFIRENT, STRICT_EGALE};
enum attribution {EGALE, PLUS_EGALE, MOINS_EGALE, DIVISE_EGALE, MULTIPLI_EGALE, RESTE_EGALE, MODULO_EGALE};
enum separateur {ESPACE, SAUT_DE_LIGNE};
enum charactere {SIMPLE_GUILLEMET_ANGLAIS, DOUBLE_GUILLEMET_ANGLAIS, CROCHET, ACOLADE, PARENTHESE};
enum variable {VARIABLE};

char *tabTypeVariable[] = {"lettre", "chaine", "entier", "decimale", "booleen", "structure", "constante", "fonction", "classe"};
char *tabOperateurs[] = {"==", "*", "-", "/", "//", "%%", "et", "ou", "pas", "<", "<=", ">", ">=", "<>", "==="};
char *tabAttribution[] = {"=", "+=", "-=", "/=", "*=", "//=", "%%="};
char *tabCharactere[] = {"'", "\"", "[]", "{}", "()"};
char tabSeparateur[] = {' ', ','};
char tabSeparateurGarder[] = {'=', '+','/','-','*', '-','<', '>','(', ')','{', '}','[', ']','\'', '"', '\n', ','};

bool debutLigne = true;
bool chaineOuvert = false;
bool declarationVariable = false;
bool attributionVariable = false;
bool attentValeur = false;
bool concatChaine = false;
bool operateur = false;

char *codVADTrad;

bool estSeparateur(char lettre) {
    int taille = sizeof(tabSeparateur) / sizeof(tabSeparateur[0]);
    bool boolRetour = false;
    for (size_t i = 0; i < taille; i++)
    {
        if (tabSeparateur[i] == lettre) {
            boolRetour = true;
        }
    }
    return boolRetour;
}

bool estSeparateurGarder(char lettre) {
    int taille = sizeof(tabSeparateurGarder) / sizeof(tabSeparateurGarder[0]);
    bool boolRetour = false;
    for (size_t i = 0; i < taille; i++)
    {
        if (tabSeparateurGarder[i] == lettre) {
            boolRetour = true;
        }
    }
    return boolRetour;

}

void decoupage(char *codeSource, size_t  taille) {
    char **tabCodeSource = (char **)malloc(taille * sizeof(char *));;
    size_t indTabCodeSource = 0;
    int indDebut = 0;
    bool separateur = false;
    char *sousChaine = NULL;


    for (size_t i = 0; i < taille; i++)
    {
        char lettre = codeSource[i];
        if (estSeparateur(lettre) && !separateur) {
            int longueurSousChaine = i - indDebut;
            free(sousChaine);
            char *sousChaine = (char *)malloc(longueurSousChaine+1);
            sousChaine[longueurSousChaine] = '\0';
            strncpy(sousChaine, codeSource + indDebut, longueurSousChaine);
            tabCodeSource[indTabCodeSource] = (char *)malloc(longueurSousChaine);
            tabCodeSource[indTabCodeSource] = sousChaine;
            indTabCodeSource++;
            indDebut=i+1;
            separateur = true;
        }
        else if (estSeparateurGarder(lettre)) {
            if (!separateur && codeSource[i-1] != ' ') {
                int longueurSousChaine = i - indDebut;
                free(sousChaine);
                char *sousChaine = (char *)malloc(longueurSousChaine+1);
                sousChaine[longueurSousChaine] = '\0';
                strncpy(sousChaine, codeSource + indDebut, longueurSousChaine);
                tabCodeSource[indTabCodeSource] = (char *)malloc(longueurSousChaine);
                tabCodeSource[indTabCodeSource] = sousChaine;
                indTabCodeSource++;
                indDebut=i+1;
                separateur = true;
            }
            int j = 0;
            while (1==1)
            {
                j++;
                if (!estSeparateurGarder(codeSource[i+j])) {
                    break;
                }
            }
            tabCodeSource[indTabCodeSource] = (char *)malloc(j+1);
            for (size_t k = 0; k < j; k++)
            {
                tabCodeSource[indTabCodeSource][k] = codeSource[i];
                i++;
            }
            i--;
            tabCodeSource[indTabCodeSource][j] = '\0';
            indTabCodeSource++;
            
            
        }
        else {
            if (separateur) {
                indDebut = i;
            }
            separateur = estSeparateur(lettre) || estSeparateurGarder(lettre);
        }
    }

    free(sousChaine);

    codVADTrad = (char *)malloc(indTabCodeSource);

    for (size_t i = 0; i < indTabCodeSource; i++)
    {
        // printf(tabCodeSource[i]);
        // printf("\n");
        tradVAD(tabCodeSource[i]);
    }
    
}

bool estDeclaration(char *chaine) {
    bool retour = false;

    for (size_t i = 0; i < sizeof(tabTypeVariable) / sizeof(tabTypeVariable[0]); i++)
    {
        if (strcmp(chaine, tabTypeVariable[i]) == 0) {
            retour = true;
            break;
        }
    }

    return retour;
}

bool nomVariableValide(char *nomVariable) {

    bool variableValide = true;

    for (int i = 0; nomVariable[i] != '\0'; i++) {
        if (!isalpha(nomVariable[i]) && !isdigit(nomVariable[i]) || (i==0 && isdigit(nomVariable[i]))) {
            variableValide = false;
        }
    }
    return variableValide;

}

bool estEntier(char *chaine) {
    bool retour = true;

    for (int i = 0; chaine[i] != '\0'; i++) {
        if (!isdigit(chaine[i])) {
            retour = false;
        }
    }
    return retour;
}

bool estOperateur(char *chaine) {
    bool retour = false;

    for (size_t i = 0; i < sizeof(tabOperateurs)/sizeof(tabOperateurs[0]); i++)
    {
        if (strcmp(chaine, tabOperateurs[i]) == 0) {
            retour = true;
            break;
        }
    }

    return retour;
}

void tradVAD (char *chaine) {

    if (chaine[0] == '\n') {
            debutLigne = true;
            declarationVariable = false;
            attributionVariable = false;
            chaineOuvert = false;
            attentValeur = false;
            concatChaine = false;
            operateur = false;
            printf("\n debut-ligne");
    }
    else if (debutLigne) {
        if (estDeclaration(chaine)) {
            debutLigne = false;
            chaineOuvert = false;
            attributionVariable = false;
            attentValeur = false;
            concatChaine = false;
            operateur = false;
            declarationVariable = true;
            printf(" declaration-variable");
        }
    }
    else if (declarationVariable) {
        if (nomVariableValide(chaine)) {
            declarationVariable = false;
            attributionVariable = true;
            chaineOuvert = false;
            attentValeur = false;
            concatChaine = false;
            operateur = false;
            printf(" nom-variable");
        }
    }
    else if (attributionVariable)
    {
        if (chaine[0] == '=') {
            attentValeur = true;
            declarationVariable = false;
            attributionVariable = false;
            chaineOuvert = false;
            concatChaine = false;
            operateur = false;
            printf(" attribution");
        }
    }
    else if (attentValeur) {
        if (chaine[0] == '\"') {
            chaineOuvert = true;
            debutLigne = false;
            declarationVariable = false;
            attributionVariable = false;
            attentValeur = false;
            concatChaine = false;
            operateur = false;
            printf(" chaine-ouvert");
        }
        else if(estEntier(chaine)) {
            chaineOuvert = false;
            debutLigne = false;
            declarationVariable = false;
            attributionVariable = false;
            attentValeur = false;
            concatChaine = false;
            operateur = true;
            printf(" entier");
        }
        
        
    }
    else if (chaineOuvert) {
        if (chaine[0] == '\"') {
            chaineOuvert = false;
            debutLigne = false;
            declarationVariable = false;
            attributionVariable = false;
            attentValeur = false;
            concatChaine = true;
            operateur = false;
            printf(" chaine-fermer");
        }
    }
    else if (concatChaine) {
        if (chaine[0] == '+') {
            chaineOuvert = false;
            debutLigne = false;
            declarationVariable = false;
            attributionVariable = false;
            attentValeur = true;
            concatChaine = false;
            operateur = false;
            printf(" plus");
        }
    }
    else if (operateur)
    {
        if (estOperateur(chaine))
        {
            chaineOuvert = false;
            debutLigne = false;
            declarationVariable = false;
            attributionVariable = false;
            attentValeur = true;
            concatChaine = false;
            operateur = true;
            printf(" operateur");
        }
        
    }

    printf("[%s] ", chaine);
    
    
}

int main() {
    char codeSource[] = "entier entierX = 5\n"
                        "entier entierY=3\n"
                        "entier entierZ=entierX+entierY\n"
                        "entier entierZ/=2\n"
                        "chaine chaineX = \"Bonjour \"\n"
                        "chaine chaineY=\"tout le monde\"\n"
                        "chaine chaineZ=chaineX+chaineY\n";
    
    size_t taille = sizeof(codeSource);
    
    decoupage(codeSource, taille);

    return 0;
}