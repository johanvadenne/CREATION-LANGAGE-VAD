use std::{env, process, fs};

fn erreur(texte: &str) {
    journal(texte);
    process::exit(0);
}


fn journal(texte: &str) {
    println!("{texte}");
}

fn entier_vers_chaine(entier: usize) -> String {
    let chaine = entier.to_string();
    return chaine;
}

fn chaine_vers_entier(texte: &str) -> i32 {

    let mut nombre_chaine = String::new();
    let mut entier = 0;

    for lettre in texte.chars() {
        if lettre.is_digit(10) {
            nombre_chaine.push(lettre);
        }
        else {
            break;
        }
    }
    entier = nombre_chaine.parse::<i32>().unwrap_or(0);

    return entier;

}

fn construit_chaine(texte: &str, parametre: &[&str]) -> String {
    let mut num_param = 0;
    let parties_chaine: Vec<&str> = texte.split('@').collect();
    let mut nouveau_texte = String::new();
    let mut texte_temp = String::new();

    for partie_chaine in parties_chaine {
        num_param = chaine_vers_entier(partie_chaine);
        if num_param > 0 && num_param <= parametre.len() as i32 {
            texte_temp = partie_chaine.replace(
                &format!("@{}", num_param),
                parametre[num_param as usize - 1]
            );
            nouveau_texte.push_str(&texte_temp);
        }
        else {
            nouveau_texte.push_str(partie_chaine);
        }
    }

    return nouveau_texte;
}

fn verifie_argument(nbr_argument: usize) {
    
    let mut message = String::new();

    if nbr_argument > 2 {
        message = construit_chaine("Il y a trop d'argument\nnombre de paramètre: @1", &[&entier_vers_chaine(nbr_argument)]);
        erreur(&message);
    }
    else if nbr_argument < 2 {
        message = "Il n'y a pas d'argument".to_string();
        erreur(&message);
    }
    else {
        message = "nombre d'argument: OK".to_string();
        journal(&message);
    }
}

fn lire_fifchier(chemin: String) -> String {
    let contenu = fs::read_to_string(chemin)
        .expect("Quelque chose s'est mal passé lors de la lecture du fichier");

    return contenu;
}

fn fichier_existe(chemin: String) -> bool {
    let mut fichier_existe_renvoie = false;

    

    return fichier_existe_renvoie;
}

fn main() {
    // Récupérer les arguments de la ligne de commande
    let arguments: Vec<String> = env::args().collect();
    let nbr_argument = arguments.len();

    verifie_argument(nbr_argument);
    let chemin_programme: String = arguments[1].to_string();
    fichier_existe(chemin_programme);
    lire_fifchier(chemin_programme);
}
