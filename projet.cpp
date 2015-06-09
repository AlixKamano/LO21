#include "projet.h"

void Projet::addItem(Tache* t){
    if(nb==nbMax){
        Tache** new_tab=new Tache*[nbMax+10];
        for(int i=0;i<nb;i++){
            new_tab[i]=taches[i];
        }
        nbMax+=10;
        Tache **old_tab=taches;
        taches=new_tab;
        delete[] old_tab;
    }
    taches[nb]=t;
    nb++;
}

Tache* Projet::getTache(const QString &id) const{
    for(int i=0; i<nb;i++){
            if(id==taches[i]->getId()){
                return taches[i];
            }
        }
        return 0;
}


void Projet::ajouterTache(const QString& id, const QString& t, const Date& dispo, const Date& deadline){
    if(getTache(id)){
        throw ProjetException("Error : L'identificateur existe deja");
    }
    //Appel à TacheFactory
    Tache *new_tache = new Tache(id,t,dispo,deadline);
    addItem(new_tache);
}


Projet::IteratorSTL Projet::begin(){
    return IteratorSTL(taches);
}

Projet::IteratorSTL Projet::end(){
    return IteratorSTL(taches+nb);
}
