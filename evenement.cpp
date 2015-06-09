#include "evenement.h"

EvtTache* EvtTache::programmer(const Date& da, const Horaire& h, const Duree& d){
    //Vérification du respect des contraintes : précédence  + échéance + dispo
    if(da<tache->getDispo())
        throw CalendarException("La tâche n'est pas encore disponible");
    if(tache->getEcheance()<da)
    {
        throw CalendarException("La date d'échéance est dépassée");
        tache->setStatut(-1);}
    //On vérifie que toutes les taches précédentes ont été programmées
    if(tache->getStatutPrecedence()<=0)     //Pas sur que ça marche : Il faut vérifier que toutes les taches précédentes sont programmées/finies ?
        throw CalendarException("Les tâches précédentes n'ont pas encore été programmées");
    if(tache->getStatut()==0)
        tache->setStatut(1);
    Evt::setDuree(d);
    Evt::setDate(da);
    Evt::setHoraire(h);
    return this;
}

EvtActivite* EvtActivite::programmer(const Date& da, const Horaire& h, const Duree& d){
    Evt::setDate(da);
    Evt::setHoraire(h);
    Evt::setDuree(d);
    return this;
}

