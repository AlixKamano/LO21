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

class Activite {
private:
    string titre;
    Duree duree;
public:
    Activite(const string&  s, const Duree d): titre(s), duree(d){};
	string getTitre()const{return titre;};
	Duree getDuree()const {return duree;};
};

class EvtTache {
private:
    Duree duree;
    Tache* tache;
public:
    EvtTache(const Duree d, const Tache* t) : duree(d), tache(t){};
    Duree getDuree()const{return duree;};
    Tache* getTache()const{return tache;};
};

class EvtActivite {
private:
    Activite* activite;
public:
    EvtActivite(const Activite* a) : activite(a){};
    Activite* getActivite()const{return activite;};
};

class Prog {
private:
    Date date;
    Horaire horaire;
public:
    Prog(const Date d, const Horaire h) : date(d), horaire(h){};
    Date getDate()const{return date;};
    Horaire getHoraire()const{return horaire;};
};

#endif