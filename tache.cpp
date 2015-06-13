#include"tache.h"
#include "evenement.h"
//Uniquemet pour avoir accès à CalendarException
//
int Tache::getStatutPrecedence()const{
    int statut=1;
    for(int i =0;i<nbPrec;i++)
        statut*=precedence[i]->getStatut();
    return statut;
}

void Tache::addPrecedence(Tache* t){
    //Vérifier si la tache n'est pas dans le tableau
    for(int i=0;i<nbPrec;i++)
        if(precedence[i]->getId()==t->getId())
            throw CalendarException ("La tâche a déjà été ajoutée comme précédente");
    //Ajouter le pointeur
    if(nbPrec==nbPrecMax){
        nbPrecMax+=10;
        Tache** new_tab = new Tache*[nbPrecMax+10];
        for(int i=0;i<nbPrec;i++)
            new_tab[i]=precedence[i];
        Tache** old_tab=precedence;
        precedence=new_tab;
        delete[] old_tab;
    }
    precedence[nbPrec]=t;
    nbPrec++;
}

void Tache::rmPrecedence(Tache* t){
    int i=0;
    while(i<nbPrec && precedence[i]!=t)
        i++;
    for(int j=i;j<nbPrec;j++)
        precedence[j]=precedence[j+1];
}

void TComposite::addSousTache(Tache* t){
    for(int i=0;i<nb;i++)
        if(sousTaches[i]==t)
            throw CalendarException("Cette tâche est déjà une sous-tache");
    if(nb==nbMax){
        Tache** new_tab = new Tache*[nbMax+10];
        for(int i=0;i<nb;i++)
            new_tab[i]=sousTaches[i];
        nbMax+=10;
        Tache** old_tab=sousTaches;
        sousTaches=new_tab;
        delete[] old_tab;
    }
    sousTaches[nb]=t;
    nb++;

}

TComposite::IteratorSTL TComposite::begin() const{
    return IteratorSTL(sousTaches);
}

TComposite::IteratorSTL TComposite::end() const{
    return IteratorSTL(sousTaches+nb);
}

Tache* TComposite::getSousTache(const QString& id)const{
    Tache* t=0;
    for(int i=0; i<nb;i++){
            if(id==sousTaches[i]->getId()){
                return sousTaches[i];
            }
            if(sousTaches[i]->getType()=="composite")
                t=dynamic_cast<TComposite*>(sousTaches[i])->getSousTache(id);
        }
        return t;
}

void TComposite::ajouterSousTache(const QString& desc, const QString& id,Tache* prec, const QString& t, const Duree& du, const QDate& dispo, const QDate& deadline, bool preempt){
    //Appel à TacheFactory
    Tache* new_tache= TacheFactory::NewTache(desc,id,prec,t,dispo,deadline,du,preempt);
    TComposite::addSousTache(new_tache);
}
