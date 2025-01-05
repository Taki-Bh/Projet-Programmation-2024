//
// Created by MSI on 1/4/2025.
//
/*Groupe : 
    -Taki Eddine Baccouch
    -Ismail Mechkene
    -Ahmed Baccouche
    -Ghazi Mouaddeb
*/


#include <iostream>
#include <cstring>

using namespace std;

// Classe représentant un article avec des attributs de base comme le code, la désignation et la quantité
class Article {
    int code;            // Code de l'article
    char desig[30]{};    // Désignation de l'article
    int qte;             // Quantité de l'article

public:
    explicit Article(int _code = 0, const char* _desig = "", int _qte = 0) {
        code = _code;
        strcpy(desig, _desig);
        qte = _qte;
    }

    ~Article() {
        cout << "Destructeur appelé pour l'article avec le code : " << code << endl;
    }

    // Setters et getters pour les attributs de la classe
    void setCode(int _code) {
        code = _code;
    }
    int getCode() const {
        return code;
    }

    void setDesig(const char* _desig) {
        strcpy(desig, _desig);
    }
    const char* getDesig() const {
        return desig;
    }

    void setQte(int _qte) {
        qte = _qte;
    }
    int getQte() const {
        return qte;
    }

    // Méthode pour afficher les informations de l'article
    void view() const {
        cout << "Code : " << code
             << "\nDésignation : " << desig
             << "\nQuantité : " << qte << endl;
    }
};

// Classe représentant un produit fini avec des attributs comme la marque, le prix et les opérations
class ProduitFini {
    char marque[30]{};   // Nom de la marque
    float prix{};        // Prix du produit
    int nbOp{};          // Nombre d'opérations
    char T[10][30]{};    // Liste des opérations (jusqu'à 10)

public:
    ProduitFini() {
        strcpy(marque, "");
        prix = 0.0;
        nbOp = 0;
        for (auto & i : T) {
            strcpy(i, "");
        }
    }

    ProduitFini(const char* _marque, float _prix, int _nbOp, const char _T[10][30]) {
        strcpy(marque, _marque);
        prix = _prix;
        nbOp = _nbOp;
        for (int i = 0; i < 10; ++i) {
            strcpy(T[i], _T[i]);
        }
    }

    // Setters et getters pour les attributs de la classe
    void setMarque(const char* _marque) {
        strcpy(marque, _marque);
    }
    const char* getMarque() const {
        return marque;
    }

    void setPrix(float _prix) {
        prix = _prix;
    }
    float getPrix() const {
        return prix;
    }

    void setnbOp(int _nbOp) {
        nbOp = _nbOp;
    }
    int getnbOp() const {
        return nbOp;
    }

    void setT(int index, const char* str) {
        if (index >= 0 && index < 10) {
            strcpy(T[index], str);
        }
    }

    const char* getT(int index) const {
        if (index >= 0 && index < 10) {
            return T[index];
        }
        return nullptr;
    }

    // Méthode pour afficher les informations du produit fini
    void afficher() const {
        cout << "Marque : " << marque
             << "\nPrix : " << prix
             << "\nNombre d'opérations : " << nbOp << endl;
    }
};

// Classe Node pour la liste chaînée, contenant un produit fini et un pointeur vers le noeud suivant
class Node {
public:
    ProduitFini produit;
    Node* next;

    Node(const ProduitFini& _produit, Node* _suivant = nullptr)
        : produit(_produit), next(_suivant) {}
};

// Classe ListeProduitFini pour gérer une liste de produits finis
class ListeProduitFini {
    Node* first; // Pointeur vers le premier noeud de la liste

public:
    ListeProduitFini() : first(nullptr) {}

    ~ListeProduitFini() {
        // Destructeur pour supprimer tous les noeuds et libérer la mémoire
        while (first) {
            Node* tmp = first;
            first = first->next;
            delete tmp;
        }
    }

    // Méthode pour ajouter un nouveau produit à la liste
    void add(const ProduitFini& produit) {
        Node* newNode = new Node(produit, first);
        first = newNode;
    }

    // Méthode pour supprimer un produit par sa marque
    bool del(const char* marque) {
        Node* current = first;
        Node* prev = nullptr;

        while (current) {
            if (strcmp(current->produit.getMarque(), marque) == 0) {
                if (prev == nullptr) {  // Suppression du premier noeud
                    first = current->next;
                } else {
                    prev->next = current->next;
                }
                delete current;
                return true;
            }
            prev = current;
            current = current->next;
        }
        return false;  // Marque non trouvée
    }

    // Méthode pour rechercher un produit par sa marque
    ProduitFini* search(const char* marque) const {
        Node* current = first;
        while (current) {
            if (strcmp(current->produit.getMarque(), marque) == 0) {
                return &(current->produit);
            }
            current = current->next;
        }
        return nullptr;  // Marque non trouvée
    }

    // Surcharge de l'opérateur+ pour combiner deux listes de produits
    ListeProduitFini operator+(const ListeProduitFini& other) const {
        ListeProduitFini result;

        // Copier les noeuds de la première liste
        Node* current = first;
        while (current) {
            result.add(current->produit);
            current = current->next;
        }

        // Copier les noeuds de la deuxième liste
        current = other.first;
        while (current) {
            result.add(current->produit);
            current = current->next;
        }

        return result;
    }
    
    // Méthode pour afficher tous les produits de la liste
    void view() const {
        Node* current = first;
        while (current) {
            current->produit.afficher();
            cout << "---------------------" << endl;
            current = current->next;
        }
    }
};

// Fonction principale pour démontrer l'utilisation des classes ci-dessus
int main() {
    // Créer une liste chaînée pour les produits finis
    ListeProduitFini liste;

    // Créer quelques produits finis d'exemple
    char operations1[10][30] = {"Operation1", "Operation2", "Operation3"};
    ProduitFini p1("MarqueA", 100.5, 3, operations1);

    char operations2[10][30] = {"Op1", "Op2", "Op3"};
    ProduitFini p2("MarqueB", 200.75, 2, operations2);

    char operations3[10][30] = {"Task1", "Task2", "Task3"};
    ProduitFini p3("MarqueC", 150.25, 4, operations3);

    // Ajouter les produits à la liste
    liste.add(p1);
    liste.add(p2);
    liste.add(p3);

    // Afficher la liste
    cout << "Liste des produits finis :\n";
    liste.view();

    // Recherche d'un produit spécifique par marque
    cout << "\nRecherche du produit 'MarqueB' :\n";
    ProduitFini* produitRecherche = liste.search("MarqueB");
    if (produitRecherche) {
        produitRecherche->afficher();
    } else {
        cout << "Produit non trouvé.\n";
    }

    // Suppression d'un produit
    cout << "\nSuppression de 'MarqueA'.\n";
    if (liste.del("MarqueA")) {
        cout << "Produit supprimé avec succès.\n";
    } else {
        cout << "Produit non trouvé pour suppression.\n";
    }

    // Afficher la liste après suppression
    cout << "\nListe des produits après suppression :\n";
    liste.view();

    return 0;
}
