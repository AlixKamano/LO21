#include "actmanager.h"

void ActiviteManager::ajouterAct(const QString& t, const Duree d){
    if(nb==nbMax){
        nbMax+=10;
        Activite** tmp = new Activite*[nbMax];
        for(int i=0;i<nb;<++)
            tmp[i]=activites[i];
        Activite** old = activites;
        activites = tmp;
        delete[] old;
    }
    actvites[nb++]=Activite(t,d);
}
ActiviteManager::Handler ActiviteManager::handler = ActiviteManager::Handler();

static ActiviteManager& ActiviteManager::getInstance(){
    if(handler.instance==0)
        handler.instance = new ActiviteManager;
    return *handler.instance;
}

static void ActiviteManager::freeInstance(){
    if(handler.instance!=0)
        delete handler.instance;
    handler.instance=0;
}

IteratorSTL ActiviteManager::begin()const{
    return IteratorSTL(activites);
}
IteratorSTL ActiviteManager::end()const{
    return IteratorSTL(activites+nb);
}
