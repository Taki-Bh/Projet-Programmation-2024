/*Group: 
    -Taki Eddine Baccouch
    -Ismail Mechkene
    -Ahmed Baccouche
    -Ghazi Mouaddeb
*/

#include <iostream>
#include <cstdio>
#include <map>
#include <string>

using namespace std;



// Fonction pour charger le contenu d'un fichier dans une map
void load_file_to_map(map<int, string>& Map, const string& file_name) {
    // Ouverture du fichier en lecture
    FILE* file = fopen(file_name.c_str(), "r");

    if (!file) {
        perror("Erreur lors de l'ouverture du fichier");  // Gestion des erreurs d'ouverture
        return;
    }

    int itr = 1;  // Compteur pour les clés de la map
    char ch[100];  // Tableau pour stocker chaque ligne lue
    while (fgets(ch, sizeof(ch), file) != nullptr) {
        string str(ch);  // Conversion de la ligne en string
        Map.insert(pair<int, string>(itr, str));  // Insertion dans la map avec une clé incrémentée
        itr++;  // Incrémentation du compteur de clé
    }

    fclose(file);  // Fermeture du fichier après la lecture
}

// Fonction pour écrire les données de la map dans un fichier
void write_map_to_file(map<int, string>& Map, const string& file_name) {
    // Ouverture du fichier en écriture
    FILE* file = fopen(file_name.c_str(), "w");

    if (!file) {
        perror("Erreur lors de l'ouverture du fichier");  // Gestion des erreurs d'ouverture
        return;
    }

    // Écriture de chaque ligne de la map dans le fichier
    for (const auto& [key, value] : Map) {
        fprintf(file, "%s", value.c_str());  // Écriture de la valeur dans le fichier
    }

    fclose(file);  // Fermeture du fichier après l'écriture
}

// Fonction pour trier la map en fonction d'un critère de sous-chaîne
void mapSort(map<int, string>& Map, int depl, int longueur) {
    // Parcours de la map
    for (auto itr1 = Map.begin(); itr1 != Map.end(); ++itr1) {
        auto minItr = itr1;

        // Comparaison avec les éléments suivants dans la map
        for (auto itr2 = next(itr1); itr2 != Map.end(); ++itr2) {
            // Comparaison des sous-chaînes spécifiées par les critères
            if ((minItr->second).substr(depl, longueur) < (itr2->second).substr(depl, longueur)) {
                minItr = itr2;  // Mise à jour du minimum
            }
        }

        // Échange des valeurs entre itr1 et minItr
        swap(itr1->second, minItr->second);
    }
}

// Fonction pour afficher le contenu de la map
void viewMap(const map<int, string>& Map) {
    // Parcours et affichage des paires clé-valeur de la map
    for (const auto& [key, value] : Map) {
        cout << "Clé: " << key << ", Valeur: " << value << endl;
    }
}

// Fonction pour afficher le contenu d'un fichier
void viewFile(const string& file_name) {
    // Ouverture du fichier en lecture
    FILE* file = fopen(file_name.c_str(), "r");

    if (!file) {
        perror("Erreur lors de l'ouverture du fichier");  // Gestion des erreurs d'ouverture
        return;
    }

    char str[100];  // Tableau pour stocker chaque ligne lue
    while (fgets(str, sizeof(str), file) != nullptr) {
        cout << str << endl;  // Affichage de chaque ligne du fichier
    }
}

// Fonction principale
int main(int argc, char* argv[]) {
    // Vérification du nombre de paramètres passés en ligne de commande
    if (argc != 5) {
        cout << "Le nombre de parametres doit etre 5 (<program_name> <input_file> <output_file> <dep_critere> <longueur_critere>)" << endl;
        return 1;
    }

    string input_file = argv[1];  // Nom du fichier d'entrée
    string output_file = argv[2];  // Nom du fichier de sortie
    int dep_critere = stoi(argv[3]);  // Position de départ pour la sous-chaîne
    int longueur_critere = stoi(argv[4]);  // Longueur de la sous-chaîne à comparer

    map<int, string> Map;  // Déclaration de la map pour stocker les données

    // Affichage du contenu du fichier d'entrée
    viewFile(input_file);
    cout << "----------------------------------------" << endl;

    // Chargement des données du fichier dans la map
    load_file_to_map(Map, input_file);

    // Affichage du contenu de la map après le chargement
    viewMap(Map);
    cout << "----------------------------------------" << endl;

    // Tri de la map selon les critères spécifiés
    mapSort(Map, dep_critere, longueur_critere);

    // Écriture des données triées dans le fichier de sortie
    write_map_to_file(Map, output_file);

    // Affichage du contenu du fichier de sortie
    viewFile(output_file);
    cout << "----------------------------------------" << endl;

    return 0;
}