#include "tacheManager.h"

//methodes de tache manager
void TacheManager::ajouterTache(const QString& id, const QString& t, const Date& dispo, const Date& deadline){
    if(trouverTache(id)){
        throw TacheException("Error : L'identificateur existe deja");
    }
    Tache *new_tache = new Tache(id,t,dispo,deadline);
    addItem(new_tache);
}

Tache* TacheManager::trouverTache(const QString& id) const{
    for(unsigned int i=0; i<nb;i++){
        if(id==tab[i]->getId()){
            return tab[i];
        }
    }
    return 0;
}

void TacheManager::addItem(Tache *t){
    if(nb==nbMax){
        Tache** new_tab=new Tache*[nbMax+10];
        for(int i=0;i<nb;i++){
            new_tab[i]=tab[i];
        }
        nbMax+=10;
        Tache **old_tab=tab;
        tab=new_tab;
        delete[] old_tab;
    }
    tab[nb]=t;
    nb++;
}

Tache& TacheManager::getTache( const QString& id){
    Tache *t=trouverTache(id);
    if(t) throw TacheException("error : La tache n'existe pas");
    return *t;
}

const Tache& TacheManager::getTache(const QString& id) const{
    return const_cast<TacheManager*>(this)->getTache(id);
}

//methode de handler de TM
TacheManager::Handler TacheManager::handler = TacheManager::Handler();

TacheManager& TacheManager::getInstance(){
    if (handler.instance == 0)
        handler.instance = new TacheManager;
    return *handler.instance;
}

void TacheManager::freeInstance(){
    if (handler.instance!=0)
        delete handler.instance;
    handler.instance = 0;
}

//methode de IteratorSTL de TM
TacheManager::IteratorSTL TacheManager::begin(){
    return IteratorSTL(tab);
};

TacheManager::IteratorSTL TacheManager::end(){
    return IteratorSTL(tab+nb);
};
