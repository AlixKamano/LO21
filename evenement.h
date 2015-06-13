#ifndef EVENEMENT_H
#define EVENEMENT_H
//
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
    QDate date;//!< \param Date de l'évènement
    Horaire horaireDebut;    //!< \param Horaire de fin de l'évènement
    Horaire horaireFin; //!< \param Horaire de debut de l'évènement
    Duree duree;        //!< \param Durée de l'évènement
public:
    //! Constructeur à partir de QDate, Horaire et Durée
    //! \param d const QDate par défaut à 0
    //! \param hd Horaire par défaut à 0
    //! \param hf Horaire par défaut à 0
    //! \param du Durée par défaut à 0
    Evt(const QDate& d=QDate(0,0,0), const Horaire& hd=Horaire(0,0), const Duree& du=Duree(0,0), const Horaire& hf=Horaire(0,0)) : date(d), horaireDebut(hd),duree(du),horaireFin(hf){}
    virtual ~Evt(){}
    //! Accesseur à la date de l'évènement
    QDate getDate()const{return date;}
    //! Accesseur à l'horaire de debut de l'évènement
    Horaire getHoraireD()const{return horaireDebut;}
    //! Accesseur à l'horaire de fin de l'évènement
    Horaire getHoraireF()const{return horaireFin;}
    //! Accesseur à la durée de l'évènement
    Duree getDuree()const{return duree;}
    //! Initialisateur de la date
    void setDate(QDate d){date = d;}
    //! Initialisateur de l'horaire de debut
    void setHoraireD(Horaire h){horaireDebut = h;}
    //! Initialisateur de l'horaire de fin
    void setHoraireF(Horaire h){horaireFin = h;}
    //! Initialisateur de la durée
    void setDuree(Duree d){duree = d;}
    //! Programmation d'un évènement. Méthode virtuelle pure
    virtual Evt* programmer(const QDate& d, const Horaire&h, const Duree& du)=0;         // Comment récupérer le pointeur vers Tache/Evt ?
    //! Permet de connaitre le type d'evenment. Méthode virtulle pure
    virtual QString getType() const=0;
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
    EvtTache(const QDate& da = QDate(0,0,0), const Horaire& hd=Horaire(0,0), const Horaire& hf=Horaire(0,0),const Duree& d=Duree(0),TUnitaire* t=0) : Evt(da,hd,d,hf), tache(t){
        Duree du;
        if(t->getPreemptive()!=0)
            t->setDuree(Duree(t->getDuree().getDureeEnMinutes()-d.getDureeEnMinutes()));
    }
    EvtTache(TUnitaire* t):Evt(),tache(t){}
    //! Accesseur à la tâche programmée
    TUnitaire* getTache()const{return tache;}
    //!Programmation de la tâche
    EvtTache* programmer(const QDate& da, const Horaire& h, const Duree& d);
    QString getType() const{return "tache";}
};

class EvtActivite :public Evt{
private:
    Activite* activite;
public:
    EvtActivite(const QDate& da=QDate(0,0,0), const Horaire& hd=Horaire(0,0), const Horaire& hf=Horaire(0,0),const Duree& d=Duree(0), Activite* a=0) : Evt(da,hd,d,hf), activite(a){}
    EvtActivite(Activite* a):Evt(),activite(a){}
    Activite* getActivite()const{return activite;}
    EvtActivite* programmer(const QDate& da, const Horaire& h, const Duree& d);
    QString getType() const{return "activite";}
};

class EvtFactory{
    //! \class EvenementFactory
    //! Design Pattern Abstract Factory
    //! On appelle newEvt avec un pointeur tache ou activité. Selon le QString passé en paramètre, on effectue un cast sur le pointeur
public:
    //Design Pattern Abstract Factory
    //On appelle newEvt avec un pointeur tache ou activité. Selon le QString passé en paramètre, on effectue un cast sur le pointeur
    static Evt* NewEvt(const QString& description, void* ptr,const QDate& da, const Horaire& hd,const Horaire& hf,const Duree& d){     //void* ptr ?
        if(description=="tache")
            return new EvtTache(da,hd,hf,d,(TUnitaire*)ptr);
        if(description=="activite")
            return new EvtActivite(da,hd,hf,d,(Activite*)ptr);
        return NULL;
    };
};

#endif // EVENEMENT_H

