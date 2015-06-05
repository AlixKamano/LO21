#ifndef LO21_projet_calendar_h
#define LO21_projet_calendar_h

#include "timing.h"
#include "projet.h"
#include <iostream>
using namespace std;
using namespace TIME;

class CalendarException{
public:
    CalendarException(const string& message):info(message){}
    string getInfo() const { return info; }
private:
    string info;
};

class Activite {        //Ajout de statut aux activités ?
private:
    string titre;
    Duree duree;
public:
    Activite(const string&  s, const Duree d): titre(s), duree(d){};
	string getTitre()const{return titre;};
	Duree getDuree()const {return duree;};
};

class Prog {    //Virtuelle pure
private:
    Date date;
    Horaire horaire;
public:
    Prog(const Date& d, const Horaire& h) : date(d), horaire(h){};
    Date getDate()const{return date;};
    Horaire getHoraire()const{return horaire;};
    void setDate(Date& d){date = d;};
    void setHoraire(Horaire& h){horaire = h;};
    virtual Prog* reprogrammer()=0;         // Attributs? La fct doit updater date & horaire
};

//Soit prog pointe vers un evt (evtTache & evtActivité héritent de evt) 
//Ou evt* héritent de prog -> problème dans progManager, comment on ajoute une programmation ?

class EvtTache : public Prog{
private:
    Duree duree;
    Tache* tache;
public:
    EvtTache(const Date& da, const Horaire& h,const Duree& d, const Tache* t) : Prog(da,h),duree(d), tache(t){};
    Duree getDuree()const{return duree;};
    Tache* getTache()const{return tache;};
    EvtTache* reprogrammer(const Date& da, const Horaire& h, const Duree& d);
};

class EvtActivite :public Prog{
private:
    Activite* activite;
public:
    EvtActivite(const Date& d, const Horaire& hconst Activite* a) : Prog(d,h), activite(a){};
    Activite* getActivite()const{return activite;};
    EvtActivite* reprogrammer(const Date& da, const Horaire& h);
};

#endif