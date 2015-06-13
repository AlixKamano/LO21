#include "projetManager.h"

//methodes de la classe projet manager 
void ProjetManager::ajouterProjet(const QString& id, const QString& t, const QDate &dispo, const QDate &deadline, int max){
    if(trouverProjet(id)){
        throw ProjetException("Error : L'identificateur existe deja");
    }
    Projet *new_projet = new Projet(id,t,dispo,deadline,max);
    addItem(new_projet);
}

Projet* ProjetManager::trouverProjet(const QString& id) const{
    for(unsigned int i=0; i<nb;i++){
        if(id==projets[i]->getId()){
            return projets[i];
        }
    }
    return 0;
}


void ProjetManager::addItem(Projet *p){
    if(nb==nbMax){
        Projet** new_tab=new Projet*[nbMax+10];
        for(int i=0;i<nb;i++){
            new_tab[i]=projets[i];
        }
        nbMax+=10;
        Projet **old_tab=projets;
        projets=new_tab;
        delete[] old_tab;
    }
    projets[nb]=p;
    nb++;
}

Projet& ProjetManager::getProjet(const QString& id){
    Projet *p=trouverProjet(id);
    if(p) throw ProjetException("error : La tache n'existe pas");
    return *p;
}

const Projet& ProjetManager::getProjet(const QString& id) const{
    return const_cast<ProjetManager*>(this)->getProjet(id);
}

//methode de handler de PM
ProjetManager::Handler ProjetManager::handler = ProjetManager::Handler();

ProjetManager& ProjetManager::getInstance(){
    if (handler.instance == 0)
        handler.instance = new ProjetManager;
    return *handler.instance;
}

void ProjetManager::freeInstance(){
    if (handler.instance!=0)
        delete handler.instance;
    handler.instance = 0;
}

//methode de IteratorSTL de PM
ProjetManager::IteratorSTL ProjetManager::begin(){
    return IteratorSTL(projets);
};

ProjetManager::IteratorSTL ProjetManager::end(){
    return IteratorSTL(projets+nb);
};
