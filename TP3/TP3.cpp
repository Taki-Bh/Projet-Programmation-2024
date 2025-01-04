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
    void view()
    {
        recView(racine);//appel d'une fonction recursif qui perfome l'afichage
    }
    void recView(node<T>* current){
        if(current){
            cout<<"Data : "<<current->data<<endl;// On affiche le donné enregistré dans ce noeud
            recAfficher(current->frere); //On passe l'affichage de la sous-noeud frere
            recAfficher(current->fils); //On passe l'affichage de la sous-noeud fils
        }
    }

    node<T>* search(T _data){
        return recSearch(racine,_data);
    }
    node <T> * recSearch(node<T> * noeud,T _data){
        if(noeud){//test sur l'existence de noeud
            if(noeud->data==_data){//test sur l'égalité des valeurs
                cout<<"FOUND DATA"<<_data<<endl;
                return noeud;
            }
            node<T> * rechRes=recSearch(noeud->fils,_data);//démarrage d'une recherche dans la sous-noeud fils
            if(!rechRes){//test sur la resultat éventuelle de sous recherche
                node<T> * rechRes=recSearch(noeud->frere,_data);//démarrage d'une recherche dans la sous-noeud fils
            }
            return rechRes;
        }
        return NULL;
    }//retourne l'adresse de la noeud contenant "_data" sinon en cas d'inexistance on retourne NULL
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
    tree.view();
    tree.search(7);
    return 0;
}