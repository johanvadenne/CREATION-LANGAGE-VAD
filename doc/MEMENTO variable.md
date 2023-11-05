# chaine
>**chaine** texte
>**chaine** texte = "mon texte"
>**chaine**(100) texte
>**chaine** texte1, texte2
>>**chaine**(*<nombre limite de caractère>*) *\<nom variable>*<br>
>>*<nombre limite de caractère>* : optionnel
>>*\<nom variable>* : obligatoire

# entier
>**entier** nombre
>**entier** nombre = 5
>**entier**(-10,100) nombre
>**entier**(max,max) nombre
>**entier**(min,min) nombre
>**entier** nombre1, nombre2
>>**entier**(*<limite négatif>*,*\<limite positif>*) *\<nom variable>*<br>
>>*<limite négatif>* : optionnel
>>*\<limite positif>* : optionnel
>>*\<nom variable>* : obligatoire


# décimale
>**decimale** nombreDecimale
>**decimale** nombreDecimale = 5
>**decimale**(-22.24,45) nombreDecimale
>**decimale**(max,max) nombreDecimale
>**decimale**(min,min) nombreDecimale
>**decimale** nombreDecimale1, nombreDecimale2
>>**decimale**(*<limite négatif>*,*\<limite positif>*) *\<nom variable>*<br>
>>*<limite négatif>* : optionnel
>>*\<limite positif>* : optionnel
>>*\<nom variable>* : obligatoire


# booleen

>**booleen** variableBooleen
>**booleen** booleenVrai = vrai
>**booleen** booleenFaux = faux
>**booleen** booleenNull = null
>**booleen** variableBooleen1, variableBooleen2
>>**booleen** *\<nom variable>*<br>
>>*\<nom variable>* : obligatoire

# tableau

>**tableau** nomTableau
>**tableau** nomTableau = \[1,2,3]
>**tableau**(5) nomTableau
>**tableau**(chaine) tableauDeChaine
>**tableau**(entier) tableauDEntier
>**tableau**(decimale) tableauDeDecimale
>**tableau**(booleen) tableauDeBooleen
>**tableau**(tableau) tableauDeTableau
>**tableau**(tableau{}) tableauDeTableauClé
>**tableau**(structure) tableauDeStructure
>**tableau**(chaine,entier) tableauDeChaineEtDEntier
>**tableau** nomTableau1, nomTableau2
>**tableau**(5,chaine) tableDe5Chaine
>>**tableau**(*<type de donnée>*) *\<nom variable>*
>>**tableau**(*<nombre de valeur limitée>*) *\<nom variable>*
>>**tableau**(*<type de donnée>*, *<type de donnée>|<type de donnée>*, ...) *\<nom variable>*
>>**tableau**(*<nombre de valeur limitée>*, *<type de donnée>*, *<type de donnée>*, ...) *\<nom variable>*<br>
>>*<type(s) de donnée(s)>* : optionnel
>>*<nombre de valeur limitée>* : optionnel
>>*\<nom variable>* : obligatoire

# tableau clé
>**tableau**{} nomTableauCle
>**tableau**{structure} nomTableauCle
>**tableau**{} nomTableauCle = {nom: "Johan", age: 18}
>**tableau**{chaine,entier|decimale} nomTableauCle = {nom: "Johan", age: 18}
>**tableau**{} nomTableauCle1, nomTableauCle2
>>**tableau**{} nomTableauCle = {*\<nom variable>*: *\<valeur>*, ...}
>>**tableau**{*<type de donnée>*} *\<nom variable>* = {*\<nom variable>*: *\<valeur>*, ...}<br>
>>*<type(s) de donnée(s)>* : optionnel
>>*\<nom variable>* : obligatoire

# Structure
>**structure** maStructure {
>**chaine** nom
>**entier** age
>}
>
>**tableau**(maStructure) personnes
>**tableau**{structure} personne
>>**structure** *\<nom structure>* {
>>*<type de donnée>* *\<nom variable1>*
>>*<type de donnée>* *\<nom variable2>*
>>*<type de donnée>* *\<nom variable3>*
>>}<br>
>>*\<nom structure>*: obligatoire
>>*<type de donnée>* *\<nom variable1>*: optionnel

# constante
>**constante** chaine texte = "mon texte"
>**constante** entier nombre = 5
>**constante** decimale nombreDecimale = 5.5
>**constante** booleen variableBooleen = vrai
>**constante** tableau nomTableau = \[1,2,3]
>**constante** tableau{} nomTableauCle = {nom: "Johan", age: 18}
>>**constante** *<type de donnée>*

# classe
>**classe** maClasse2 {
>
>}


# fonction
>**fonction** maFonction() {
>}