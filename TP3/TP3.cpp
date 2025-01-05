#include <iostream>
#include <exception>
#include <string.h>
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
        if(racine){
            recView(racine);//appel d'une fonction recursif qui perfome l'afichage
        }
        
    }
    void recView(node<T>* current){
        if(current){
            cout<<(current==racine)<<endl;
            cout<<"Data : "<<current->data<<endl;// On affiche le donné enregistré dans ce noeud
            recView(current->frere); //On passe l'affichage de la sous-noeud frere
            recView(current->fils); //On passe l'affichage de la sous-noeud fils
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
    void deleteElement(T _data){
        recDeleteElement(racine,_data);
    }
    node<T>* recDeleteElement(node<T>* _node, T _data) {
        if (_node == NULL) {
            return NULL;  // Si le noeud est NULL, retourner NULL
        }

        // Si le noeud actuel correspond aux données à supprimer
        if (_node->data == _data) {
            // Si c'est le noeud racine, le traiter séparément
            if (_node == racine) {
                deleteNodes(_node->fils);  // Supprimer tous les enfants de la racine
                node<T>* racineFrr=racine->frere;
                delete _node;
                racine=racineFrr;              
                return NULL;
            }

            // Si ce n'est pas la racine, on doit le retirer de la liste des frères du parent
            if (_node->frere) {
                // Retourner le frère suivant dans la liste
                node<T>* tmp = _node->frere;
                deleteNodes(_node->fils);  // Supprimer tous ses enfants
                delete _node;              // Supprimer le noeud actuel
                return tmp;                // Retourner le frère suivant
            } else {
                // Si le noeud n'a pas de frère (noeud feuille), on le supprime directement
                deleteNodes(_node->fils);
                delete _node;
                return NULL;  // Aucun noeud à remplacer, retourner NULL
            }
        }

        // Recherche récursive dans les frères et les enfants
        _node->frere = recDeleteElement(_node->frere, _data);  // Vérifier les frères
        _node->fils = recDeleteElement(_node->fils, _data);    // Vérifier les enfants

        return _node;  // Retourner le noeud mis à jour (avec éventuellement des changements dans ses enfants/frères)
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
            node=NULL;
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
    tree.search(6);
    cout<<"After deletion"<<endl;

   
    tree.view();
    return 0;
}