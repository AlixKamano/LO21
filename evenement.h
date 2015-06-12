#ifndef EVENEMENT_H
#define EVENEMENT_H

#include<iostream>
#include<typeinfo>
#include "timing.h"
#include "tache.h"
#include "exception.h"
#include "activite.h"

using namespace std;
using namespace TIME;

class Evt {    //Virtuelle pure
    //! \class Evenement
    //! \brief Classe abstraite permettant de stocker la programmation de tâches et activités
private:
    QDate date;     //!< \param Date de l'évènement
    Horaire horaire;    //!< \param Horaire de l'évènement
    Duree duree;        //!< \param Durée de l'évènement
public:
    //! Constructeur à partir de QDate, Horaire et Durée
    //! \param d const QDate par défaut à 0
    //! \param h Horaire par défaut à 0
    //! \param du Durée par défaut à 0
    Evt(const QDate& d=QDate(0,0,0), const Horaire& h=Horaire(0,0), const Duree& du=Duree(0,0)) : date(d), horaire(h),duree(du){};
    virtual ~Evt(){};
    //! Accesseur à la date de l'évènement
    QDate getDate()const{return date;};
    //! Accesseur à l'horaire de l'évènement
    Horaire getHoraire()const{return horaire;};
    //! Accesseur à la durée de l'évènement
    Duree getDuree()const{return duree;};
    //! Initialisateur de la date
    void setDate(QDate d){date = d;};
    //! Initialisateur de l'horaire
    void setHoraire(Horaire h){horaire = h;};
    //! Initialisateur de la durée
    void setDuree(Duree d){duree = d;};
    //! Programmation d'un évènement. Méthode virtuelle pure
    virtual Evt* programmer(const QDate& d, const Horaire&h, const Duree& du)=0;         // Comment récupérer le pointeur vers Tache/Evt ?
};

class EvtTache : public Evt{
    //! \class EvenementTache
    //! \brief Classe fille de Evenement. Permet de programmer des tâches
private:
    TUnitaire* tache;       //!< \param Pointeur vers la tâche programmée
public:
    //!Constructeur à partir de QDate, Horaire, Durée, TacheUnitaire*
    //! Fait appel au constructeur de la classe mère
    //! \param t pointeur vers une tâche unitaire par défaut NULL
    EvtTache(const QDate& da = QDate(0,0,0), const Horaire& h=Horaire(0,0),const Duree& d=Duree(0), TUnitaire* t=0) : Evt(da,h,d), tache(t){
        Duree du;
        if(t->getPreemptive()!=0)
            t->setDuree(Duree(t->getDuree().getDureeEnMinutes()-d.getDureeEnMinutes()));
    };
    //! Accesseur à la tâche programmée
    TUnitaire* getTache()const{return tache;};
    //!Programmation de la tâche
    EvtTache* programmer(const QDate& da, const Horaire& h, const Duree& d);
};

class EvtActivite :public Evt{
private:
    Activite* activite;
public:
    EvtActivite(const QDate& da=QDate(0,0,0), const Horaire& h=Horaire(0,0),const Duree& d=Duree(0), Activite* a=0) : Evt(da,h,d), activite(a){}
    EvtActivite(Activite* a):Evt(),activite(a){};
    Activite* getActivite()const{return activite;};
    EvtActivite* programmer(const QDate& da, const Horaire& h, const Duree& d);
};

class EvtFactory{
    //! \class EvenementFactory
    //! Design Pattern Abstract Factory
    //! On appelle newEvt avec un pointeur tache ou activité. Selon le QString passé en paramètre, on effectue un cast sur le pointeur
public:
    static Evt* NewEvt(const QString& description, void* ptr,const QDate& da, const Horaire& h,const Duree& d){     //void* ptr ?
        if(description=="tache")
            return new EvtTache(da,h,d,(TUnitaire*)ptr);
        if(description=="activite")
            return new EvtActivite(da,h,d,(Activite*)ptr);
        return NULL;
    };
};

#endif // EVENEMENT_H

