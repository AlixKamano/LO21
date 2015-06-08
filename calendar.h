#ifndef LO21_projet_calendar_h
#define LO21_projet_calendar_h

#include "timing.h"
#include "projet.h"
using namespace std;
using namespace TIME;

class CalendarException{
public:
    CalendarException(const QString& message):info(message){}
    QString getInfo() const { return info; }
private:
    QString info;
};

class Activite {        //Ajout de statut aux activités ?
private:
    QString titre;
    Duree duree;
public:
    Activite(const QString&  s, const Duree d): titre(s), duree(d){};
    QString getTitre()const{return titre;};
	Duree getDuree()const {return duree;};
};

class Evt {    //Virtuelle pure
private:
    Date date;
    Horaire horaire;
    Duree duree;
public:
    Evt(const Date& d=Date(0,0,0), const Horaire& h=Horaire(0,0), const Duree& du=Duree(0,0)) : date(d), horaire(h),duree(du){};
    virtual ~Evt(){};
    Date getDate()const{return date;};
    Horaire getHoraire()const{return horaire;};
    Duree getDuree()const{return duree;};
    void setDate(Date& d){date = d;};
    void setHoraire(Horaire& h){horaire = h;};
    void setDuree(Duree& d){duree = d;};
    //virtual Evt* reprogrammer()=0;         // Attributs? La fct doit updater date & horaire
};

class EvtTache : public Evt{
private:
    Tache* tache;
public:
    EvtTache(const Date& da = Date(0,0,0), const Horaire& h=Horaire(0,0),const Duree& d=Duree(0), Tache* t=0) : Evt(da,h,d), tache(t){};
    Tache* getTache()const{return tache;};
    EvtTache* reprogrammer(const Date& da, const Horaire& h, const Duree& d);
};

class EvtActivite :public Evt{
private:
    Activite* activite;
public:
    EvtActivite(const Date& da = Date(0,0,0), const Horaire& h=Horaire(0,0),const Duree& d=Duree(0), Activite* a=0) : Evt(da,h,d), activite(a){};
    Activite* getActivite()const{return activite;};
    EvtActivite* reprogrammer(const Date& da, const Horaire& h, const Duree& d);
};

class EvtFactory{
    //Design Pattern Abstract Factory
    //Il faut définir un constructeur par défaut pour EvtTache & EvtActivité !
    static Evt* NewEvt(const QString& description){
        if(description=="tache")
            return new EvtTache;
        if(description=="activite")
            return new EvtActivite;
        return NULL;
    };
};

#endif
