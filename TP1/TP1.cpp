#include <iostream>
#include <stdio.h>
#include <string.h>
using namespace std;
void allocateMemFor(char ** targetAdr /*On prends une reference pour le target car il est un pointeur lui meme ,pour le changer on besoin de l'adresse de pointeur*/ ,char * source=""){
    *targetAdr=new char[strlen(source)+1];
    strcpy(*targetAdr,source);
}
class fichier{
    
    public:
    char * name;
    char * mode;
    FILE * fp;
    int size_len;
        fichier(){
            allocateMemFor(&name);
            allocateMemFor(&mode);
            fp=NULL;
            size_len=0;
        }
        fichier (char * _name, char * _mode, int _size_len){
            allocateMemFor(&name,_name);
            allocateMemFor(&mode,_mode);
            size_len=_size_len;
        }
        ~fichier(){
            if(name){
                delete[] name;
            }
            if(mode){
                delete[] mode;
            }
            if(fp){
                fclose(fp);
            }
        }
};
int main(){
    fichier f("Taki","Here",6);
    cout<<"Hello World!"<<endl;
    cout<<strlen(f.name)<<endl;
    return 0;
}