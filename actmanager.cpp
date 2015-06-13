#include "actmanager.h"

void ActiviteManager::ajouterAct(const QString &id, const QString& t, const Duree d){
    if(trouverActivite(id)){
        throw ProjetException("Error : L'identificateur existe deja");
    }
    Activite *new_act = new Activite(id,t,d);
    addItem(new_act);
}


void ActiviteManager::addItem(Activite *p){
    if(nb==nbMax){
        nbMax+=10;
        Activite** tmp = new Activite*[nbMax];
        for(int i=0;i<nb;i++)
            tmp[i]=activites[i];
        Activite** old = activites;
        activites = tmp;
        delete[] old;
    }
    activites[nb++]= p;
}
ActiviteManager::Handler ActiviteManager::handler = ActiviteManager::Handler();

ActiviteManager& ActiviteManager::getInstance(){
    if(handler.instance==0)
        handler.instance = new ActiviteManager;
    return *handler.instance;
}

void ActiviteManager::freeInstance(){
    if(handler.instance!=0)
        delete handler.instance;
    handler.instance=0;
}

ActiviteManager::IteratorSTL ActiviteManager::begin()const{
    return IteratorSTL(activites);
}
ActiviteManager::IteratorSTL ActiviteManager::end()const{
    return IteratorSTL(activites+nb);
}

Activite* ActiviteManager::trouverActivite(const QString& id) const{
    for(unsigned int i=0; i<nb;i++){
        if(id==activites[i]->getId()){
            return activites[i];
        }
    }
    return 0;
}
