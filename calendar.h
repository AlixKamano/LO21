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
private :
    string titre;
    Duree duree;
public :
	string getTitre()const{return titre;};
	Duree getDuree()const {return duree;};
};

class EvtTache {
private :
    Duree duree;
    Tache* tache;
public :
    Duree getDuree()const{return duree;};
    Tache* getTache()const{return tache;};
};

class EvtActivite {
private :
    Activite* activite;
public :
    Activite* getActivite()const{return activite;};
};

class Programmation {
private :
    Date date;
    Horaire horaire;
public :
    Date getDate()const{return date;};
    Horaire getHoraire()const{return horaire;};
};

class ProgrammationManager {
	//Singleton
private :
    Programmation** prog;
    int nb;
    int nbMax;
public :
    Programmation** getProg()const{return prog;};
};



#endif
