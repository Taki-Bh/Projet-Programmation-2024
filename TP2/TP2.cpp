//
// Created by MSI on 1/4/2025.
//

#include <iostream>
#include <cstring>

using namespace std;

// Class representing an article with basic attributes like code, designation, and quantity
class Article {
    int code;            // Article code
    char desig[30]{};    // Designation of the article
    int qte;             // Quantity of the article

public:
    explicit Article(int _code = 0, const char* _desig = "", int _qte = 0) {
        code = _code;
        strcpy(desig, _desig);
        qte = _qte;
    }

    ~Article() {
        cout << "Destructor called for Article with code: " << code << endl;
    }

    // Setters and getters for the class attributes
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

    // Method to display article information
    void view() const {
        cout << "Code: " << code
             << "\nDesignation: " << desig
             << "\nQuantite: " << qte << endl;
    }
};

// Class representing a finished product with attributes like brand, price, and operations
class ProduitFini {
    char marque[30]{};   // Brand name
    float prix{};        // Price of the product
    int nbOp{};          // Number of operations
    char T[10][30]{};    // List of operations (up to 10)

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

    // Setters and getters for the class attributes
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

    // Method to display finished product information
    void afficher() const {
        cout << "Marque: " << marque
             << "\nPrix: " << prix
             << "\nNombre d'opérations: " << nbOp << endl;
    }
};

// Node class for linked list, containing a finished product and a pointer to the next node
class Node {
public:
    ProduitFini produit;
    Node* next;

    Node(const ProduitFini& _produit, Node* _suivant = nullptr)
        : produit(_produit), next(_suivant) {}
};

// Linked list class for managing a list of finished products
class ListeProduitFini {
    Node* first; // Pointer to the first node of the list

public:
    ListeProduitFini() : first(nullptr) {}

    ~ListeProduitFini() {
        // Destructor to delete all nodes and free memory
        while (first) {
            Node* tmp = first;
            first = first->next;
            delete tmp;
        }
    }

    // Method to add a new product to the list
    void add(const ProduitFini& produit) {
        Node* newNode = new Node(produit, first);
        first = newNode;
    }

    // Method to delete a product by its brand
    bool del(const char* marque) {
        Node* current = first;
        Node* prev = nullptr;

        while (current) {
            if (strcmp(current->produit.getMarque(), marque) == 0) {
                if (prev == nullptr) {  // Deleting the first node
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
        return false;  // Brand not found
    }

    // Method to search for a product by its brand
    ProduitFini* search(const char* marque) const {
        Node* current = first;
        while (current) {
            if (strcmp(current->produit.getMarque(), marque) == 0) {
                return &(current->produit);
            }
            current = current->next;
        }
        return nullptr;  // Brand not found
    }

    // Overloaded operator+ to combine two product lists
    ListeProduitFini operator+(const ListeProduitFini& other) const {
        ListeProduitFini result;

        // Copy nodes from the first list
        Node* current = first;
        while (current) {
            result.add(current->produit);
            current = current->next;
        }

        // Copy nodes from the second list
        current = other.first;
        while (current) {
            result.add(current->produit);
            current = current->next;
        }

        return result;
    }
    
    // Method to display all products in the list
    void view() const {
        Node* current = first;
        while (current) {
            current->produit.afficher();
            cout << "---------------------" << endl;
            current = current->next;
        }
    }
};

// Main function to demonstrate the use of the above classes
int main() {
    // Create a linked list for ProduitFini
    ListeProduitFini liste;

    // Create some sample finished products
    char operations1[10][30] = {"Operation1", "Operation2", "Operation3"};
    ProduitFini p1("MarqueA", 100.5, 3, operations1);

    char operations2[10][30] = {"Op1", "Op2", "Op3"};
    ProduitFini p2("MarqueB", 200.75, 2, operations2);

    char operations3[10][30] = {"Task1", "Task2", "Task3"};
    ProduitFini p3("MarqueC", 150.25, 4, operations3);

    // Add products to the list
    liste.add(p1);
    liste.add(p2);
    liste.add(p3);

    // View the list
    cout << "Liste des produits finis :\n";
    liste.view();

    // Search for a specific product by marque
    cout << "\nRecherche du produit 'MarqueB' :\n";
    ProduitFini* produitRecherche = liste.search("MarqueB");
    if (produitRecherche) {
        produitRecherche->afficher();
    } else {
        cout << "Produit non trouvé.\n";
    }

    // Delete a product
    cout << "\nSuppression de 'MarqueA'.\n";
    if (liste.del("MarqueA")) {
        cout << "Produit supprimé avec succès.\n";
    } else {
        cout << "Produit non trouvé pour suppression.\n";
    }

    // View the list after deletion
    cout << "\nListe des produits après suppression :\n";
    liste.view();

    return 0;
}
