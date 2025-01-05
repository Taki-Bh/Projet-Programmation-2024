#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>

using namespace std;

class Fichier {
    char* name;  // Nom du fichier
    char* mode;  // Mode d'ouverture du fichier (lecture, ecriture, etc.)
    FILE* file;  // Pointeur vers le fichier
    int size_len;  // Longueur maximale des chaines a ecrire

public:
    // Constructeur par defaut
    Fichier() : name(nullptr), mode(nullptr), file(nullptr), size_len(0) {}

    // Constructeur avec parametres
    Fichier(const char* _name, const char* _mode, int _size_len) {
        name = new char[strlen(_name) + 1];
        mode = new char[strlen(_mode) + 1];
        strcpy(name, _name);
        strcpy(mode, _mode);
        size_len = _size_len;

        file = fopen(name, mode);
        if (!file) {
            perror("Erreur lors de l'ouverture du fichier");
        }
    }

    // Destructeur pour liberer les ressources
    ~Fichier() {
        delete[] name;
        delete[] mode;
        if (file) {
            fclose(file);
        }
    }

    // Ecriture dans le fichier
    void writeFile(const char* str) {
        if (strcmp(mode, "w") != 0 && strcmp(mode, "w+") != 0) {
            cout << "Mode invalide pour l'ecriture" << endl;
            return;
        }
        if (file && fprintf(file, "%-*.*s\n", size_len, size_len, str) < 0) {
            perror("Erreur lors de l'ecriture dans le fichier");
        }
    }

    // Lecture depuis le fichier
    void readFile(char* buffer) {
        if (strcmp(mode, "r") != 0 && strcmp(mode, "r+") != 0 && strcmp(mode, "w+") != 0) {
            cout << "Mode invalide pour la lecture" << endl;
            return;
        }
        if (file && fscanf(file, "%s", buffer) == EOF && ferror(file)) {
            cout << "Erreur lors de la lecture du fichier" << endl;
        }
    }

    // Creation du fichier avec des lignes saisies par l'utilisateur
    void createInFile() {
        char* str = new char[size_len + 1];
        cout << "Entrez des lignes (ligne vide pour arreter) :" << endl;
        while (cin.getline(str, size_len + 1) && strlen(str) > 0) {
            writeFile(str);
        }
        delete[] str;
    }

    // Affichage du contenu du fichier
    void viewFile() {
        if (file) {
            fclose(file);
        }
        file = fopen(name, "r");
        if (!file) {
            cout << "Erreur lors de l'ouverture du fichier pour l'affichage" << endl;
            return;
        }
        char buffer[1024];
        while (fgets(buffer, sizeof(buffer), file)) {
            cout << buffer;
        }
        fclose(file);
    }

    // Surcharge de l'operateur + pour combiner deux fichiers
    Fichier operator+ (const Fichier& f1) {
        int max_len = max(this->size_len, f1.size_len);
        Fichier f0("C:\\Users\\MSI\\CLionProjects\\C++\\TP1\\tmp.txt", "w", max_len);

        if (!file || !f1.file) {
            cout << "Erreur : un des fichiers n'est pas ouvert" << endl;
            return f0;
        }

        rewind(this->file);
        rewind(f1.file);

        char buffer[1024];
        while (fgets(buffer, sizeof(buffer), this->file) != nullptr) {
            f0.writeFile(buffer);
        }
        while (fgets(buffer, sizeof(buffer), f1.file) != nullptr) {
            f0.writeFile(buffer);
        }
        return f0;
    }
};

int main() {
    // Creation d'un fichier pour ecrire et lire
    Fichier f1("C:\\Users\\MSI\\CLionProjects\\C++\\TP1\\file1.txt", "w+", 20);
    cout << "Creation de file1.txt. Entrez des lignes de texte (ligne vide pour arreter) :" << endl;
    f1.createInFile();

    // Affichage du contenu du fichier
    cout << "\nContenu de file1.txt :" << endl;
    f1.viewFile();

    // Creation d'un autre fichier
    Fichier f2("C:\\Users\\MSI\\CLionProjects\\C++\\TP1\\file2.txt", "w+", 20);
    cout << "\nCreation de file2.txt. Entrez des lignes de texte (ligne vide pour arreter) :" << endl;
    f2.createInFile();

    // Affichage du contenu du second fichier
    cout << "\nContenu de file2.txt :" << endl;
    f2.viewFile();

    // Combinaison des deux fichiers avec l'operateur +
    Fichier combinedFile = f1 + f2;

    // Affichage du contenu du fichier combine
    cout << "\nContenu du fichier combine (tmp.txt) :" << endl;
    combinedFile.viewFile();

    return 0;
}
