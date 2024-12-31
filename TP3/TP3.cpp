#include <iostream>
using namespace std;
template <class T>
class node
{
public:
    T data;
    node<T> *fils;
    node<T> *frere; // Structure de noeud de l'arbre
    node()
    {
        fils = NULL;
        frere = NULL;
    }
    node(T _data)
    {
        fils = NULL;
        frere = NULL;
        data = _data;
    }
};
template <class T>
class abr
{
    node<T> *racine;

public:
    abr()
    {
        racine = NULL; // construction d'une arbre vide
    }
    void insert(T _data)
    {
        // Ceci une méthode d'insertion dans l'arbre (car aucun est spécifié);
        insertFrere(_data);
        insertFils(_data);
    }
    void insertFrere(T _data)
    {
        if (!racine)
        {
            racine = new node<T>(_data);
        }
        else
        {
            node<T> *cur = racine;
            while (cur->frere)
            {
                cur = cur->frere;
            }
            cur->frere = new node<T>(_data);
        }
    }
    void insertFils(T _data)
    {
        if (!racine)
        {
            racine = new node<T>(_data);
        }
        else
        {
            node<T> *cur = racine;
            while (cur->fils)
            {
                cur = cur->fils;
            }
            cur->fils = new node<T>(_data);
        }
    }
    void afficher()
    {
        recAfficher(racine);
    }
    void recAfficher(node<T>* current){
        if(current){
            cout<<current->data<<endl;// On affiche le donné enregistré dans ce noeud
            recAfficher(current->frere); //On passe l'affichage de la sous-noeud frere
            recAfficher(current->fils); //On passe l'affichage de la sous-noeud fils
        }
    }

    //*****************************PARTIE REGISSANT LA DESTRUCTION********************************/
    void deleteNodes(node<T> *node)
    {
        if (node)
        {
            /// Avant La suppression de la noeud, On doit supprimer les sous-noeuds qui branchent au ce niveau...
            if (node->frere)
            {                             // On vérifie si la noeud frere existe
                deleteNodes(node->frere); // Si oui elle prends la priorité à supprimer
            }
            if (node->fils)
            {                            // On vérifie si la noeud fils existe
                deleteNodes(node->fils); // Si oui elle prends la priorité à supprimer
            }

            /// Enfin on supprime la noeud courante

            delete node;
        }
    }
    ~abr()
    {
        deleteNodes(racine); // On démarre la suprresion par la racine
    }
};

int main()
{
    abr<int> tree;
    tree.insert(5);
    cout << "Hello world!";
    tree.insert(6);
    cout << "Succes"<<endl;
    tree.afficher();
    return 0;
}