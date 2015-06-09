#include"tache.h"
#include "evenement.h"
//Uniquemet pour avoir accès à CalendarException

int Tache::getStatutPrecedence()const{
    int statut;
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
        Tache** new_tab = new Tache*[nbPrecMax+10];
        for(int i=0;i<nbPrec;i++)
            new_tab[i]=precedence[i];
        nbPrecMax+=10;
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
