#include"tache.h"

int Tache::getStatutPrecedence()const{
    int statut;
    for(int i =0;i<nbPrec;i++)
        statut*=precedence[i]->getStatut();
    return statut;
}

