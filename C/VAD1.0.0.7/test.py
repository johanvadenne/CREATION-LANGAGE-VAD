import re

def analyse_syntaxique(code):
    # Divise le code en lignes
    lignes = code.split('\n')
    
    for ligne in lignes:
        # Ignore les lignes vides
        if not ligne.strip():
            continue

        # Détection du type d'instruction
        if re.match(r'^lettre', ligne):
            # Traitement des déclarations de lettres
            analyse_lettre(ligne)
        elif re.match(r'^chaine', ligne):
            # Traitement des déclarations de chaînes
            analyse_chaine(ligne)
        # ... Ajouter d'autres types d'instructions ici ...

def analyse_lettre(ligne):
    # Utilise des expressions régulières pour extraire des informations
    match = re.match(r'^lettre\s+(?P<variable>\w+)(\s*=\s*(?P<valeur>\S+))?', ligne)
    if match:
        variable = match.group('variable')
        valeur = match.group('valeur')
        print(f"Déclaration de lettre : Variable '{variable}', Valeur '{valeur}'")

def analyse_chaine(ligne):
    # Utilise des expressions régulières pour extraire des informations
    match = re.match(r'^chaine(\((?P<limite>\d+)\))?\s+(?P<variable>\w+)(\s*=\s*"(?P<valeur>[^"]+)")?', ligne)
    if match:
        limite = match.group('limite')
        variable = match.group('variable')
        valeur = match.group('valeur')
        print(f"Déclaration de chaîne : Limite '{limite}', Variable '{variable}', Valeur '{valeur}'")

# Exemple d'utilisation
code_source = """
lettre lettre
lettre texte = "g"
chaine(chaine) tableauDeChaine
chaine texte1, texte2 = "Hello", texte3
"""
analyse_syntaxique(code_source)
