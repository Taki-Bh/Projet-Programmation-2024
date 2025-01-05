
/*Group: 
    -Taki Eddine Baccouch
    -Ismail Mechkene
    -Ahmed Baccouche
    -Ghazi Mouaddeb
*/

#include <iostream>
#include <exception>
#include <string.h>
using namespace std;

template <class T>
class node
{
public:
    T data;          // Donnée du noeud
    node<T> *fils;   // Pointeur vers le fils
    node<T> *frere;  // Pointeur vers le frère du noeud

    node()
    {
        fils = NULL;   // Initialisation des pointeurs à NULL
        frere = NULL;
    }

    node(T _data)
    {
        fils = NULL;   // Initialisation des pointeurs à NULL
        frere = NULL;
        data = _data;  // Initialisation de la donnée
    }
};

template <class T>
class abr
{
    node<T> *racine;  // Pointeur vers la racine de l'arbre

public:
    abr()
    {
        racine = NULL;  // Construction d'un arbre vide
    }

    void insert(T _data)
    {
        // Méthode d'insertion dans l'arbre (aucune méthode spécifique donnée)
        insertFrere(_data);
        insertFils(_data);
    }

    void insertFrere(T _data)
    {
        if (!racine)
        {
            racine = new node<T>(_data);  // Si l'arbre est vide, créer un noeud racine
        }
        else
        {
            node<T> *cur = racine;
            while (cur->frere)
            {
                cur = cur->frere;  // Parcours des frères pour ajouter à la fin
            }
            cur->frere = new node<T>(_data);  // Ajout du frère
        }
    }

    void insertFils(T _data)
    {
        if (!racine)
        {
            racine = new node<T>(_data);  // Si l'arbre est vide, créer un noeud racine
        }
        else
        {
            node<T> *cur = racine;
            while (cur->fils)
            {
                cur = cur->fils;  // Parcours des fils pour ajouter à la fin
            }
            cur->fils = new node<T>(_data);  // Ajout du fils
        }
    }

    void view()
    {
        if(racine){
            recView(racine);  // Appel de la fonction récursive pour afficher l'arbre
        }
    }

    void recView(node<T>* current){
        if(current){
            cout << (current == racine) << endl; // Vérification si le noeud est la racine
            cout << "Donnée : " << current->data << endl;  // Affichage de la donnée du noeud
            recView(current->frere);  // Affichage du frère du noeud
            recView(current->fils);    // Affichage du fils du noeud
        }
    }

    node<T>* search(T _data){
        return recSearch(racine, _data);  // Appel de la fonction récursive de recherche
    }

    node<T>* recSearch(node<T>* noeud, T _data){
        if(noeud){
            if(noeud->data == _data){
                cout << "Donnée trouvée : " << _data << endl;  // Affichage de la donnée trouvée
                return noeud;  // Retour du noeud contenant la donnée
            }
            node<T> *rechRes = recSearch(noeud->fils, _data);  // Recherche dans les fils
            if(!rechRes){
                node<T> *rechRes = recSearch(noeud->frere, _data);  // Recherche dans les frères
            }
            return rechRes;
        }
        return NULL;  // Retour de NULL si le noeud n'existe pas
    }

    void deleteElement(T _data){
        recDeleteElement(racine, _data);  // Appel de la fonction récursive pour supprimer un noeud
    }

    node<T>* recDeleteElement(node<T>* _node, T _data) {
        if (_node == NULL) {
            return NULL;  // Si le noeud est NULL, retour de NULL
        }

        // Si le noeud actuel correspond aux données à supprimer
        if (_node->data == _data) {
            if (_node == racine) {
                deleteNodes(_node->fils);  // Suppression des enfants de la racine
                node<T>* racineFrr = racine->frere;
                delete _node;
                racine = racineFrr;  // Mise à jour de la racine
                return NULL;
            }

            if (_node->frere) {
                node<T>* tmp = _node->frere;
                deleteNodes(_node->fils);  // Suppression des enfants
                delete _node;              // Suppression du noeud
                return tmp;                // Retour du frère suivant
            } else {
                deleteNodes(_node->fils);
                delete _node;  // Suppression du noeud feuille
                return NULL;
            }
        }

        // Recherche récursive dans les frères et les enfants
        _node->frere = recDeleteElement(_node->frere, _data);  // Recherche dans les frères
        _node->fils = recDeleteElement(_node->fils, _data);    // Recherche dans les enfants

        return _node;  // Retour du noeud mis à jour
    }

    void deleteNodes(node<T> *node)
    {
        if (node)
        {
            if (node->frere) {
                deleteNodes(node->frere);  // Suppression des frères
            }
            if (node->fils) {
                deleteNodes(node->fils);   // Suppression des fils
            }
            delete node;  // Suppression du noeud courant
            node = NULL;
        }
    }

    ~abr()
    {
        deleteNodes(racine);  // Détruction de l'arbre à la fin
    }
};

int main()
{
    abr<int> arbre;  // Création de l'arbre
    arbre.insert(5);  // Insertion d'un noeud avec la donnée 5
    cout << "Hello world!" << endl;
    arbre.insert(6);  // Insertion d'un noeud avec la donnée 6
    cout << "Succès" << endl;
    
    arbre.view();  // Affichage de l'arbre
    
    arbre.search(6);  // Recherche du noeud contenant la donnée 6
    
    cout << "Après la suppression" << endl;
    arbre.deleteElement(5);  // Suppression du noeud contenant la donnée 5
    
    arbre.view();  // Affichage de l'arbre après la suppression

    return 0;
}
