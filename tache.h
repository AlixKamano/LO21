#ifndef TACHE_H
#define TACHE_H

#include <iostream>
#include <QString>
#include "timing.h"

using namespace std;
using namespace TIME;

class TacheException{
public:
    TacheException(const QString& message):info(message){}
    QString getInfo() const { return info; }
private:
    QString info;
};


//Statut = 0 => Tache non programmée, à venir. Date d'échéance non dépassée
//Statut = -1 => Tache non programmée, date d'échéance dépassée
//Statut = 1 => Tache programmée/réalisée
class Tache {
    friend class TUnitaire;
    private:
        int statut;
        QString identificateur;
        QString titre;
        Tache** precedence;
        int nbPrec;
        int nbPrecMax;
        Date dispo;
        Date echeance;
        //Tache(const QString& id, const QString& t, const Date& disponible, const Date& ech) : statut(0),identificateur(id), titre(t),dispo(disponible), echeance(ech), precedence(0){};
        //Tache(const Tache& t);
        Tache& operator=(const Tache& t);
    public:
        Tache(const QString& id=0, const QString& t=0, const Date& disponible=Date(0,0,0), const Date& ech=Date(0,0,0)) : statut(0),identificateur(id), titre(t),dispo(disponible), echeance(ech), precedence(0){};
        Tache(const Tache& t);
        int getStatut() const{return statut;};
        QString getId() const {return identificateur;};
        QString getTitre() const {return titre;};
        Tache** getPrecedence() const{return precedence;};
        int getStatutPrecedence()const;
        Date getDispo()const{return dispo;};
        Date getEcheance()const{return echeance;};
        void setStatut(int s){statut=s;};
        void addPrecedence(Tache* t);
        void rmPrecedence(Tache* t);
};

class TUnitaire : public Tache{
    private:
        bool preemptive;
        Duree duree;
    public:
        TUnitaire(const QString& id, const QString& t, const Date& disponible, const Date& ech, bool premp, const Duree& dur) : Tache(id,t,disponible,ech),preemptive(premp),duree(dur){};
        TUnitaire():Tache(),preemptive(0),duree(0){};
        bool getPreemptive()const{return preemptive;};
        Duree getDuree()const{return duree;};
        void setDuree(const Duree& d){duree=d;}
};

class TComposite : public Tache{
    private:
        Tache** sousTaches;
        int nb;
        int nbMax;
    public :
        TComposite(const QString& id, const QString& t, const Date& disponible, const Date& ech) : Tache(id,t,disponible,ech),sousTaches(0),nb(0),nbMax(0){};
        TComposite():Tache(),sousTaches(0),nb(0),nbMax(0){};
        Tache** getSousTaches()const {return sousTaches;};
        void addSousTache(Tache* t);
};

class TacheFactory {
public:
    static Tache* NewTache(const QString& description ,const QString& id=0,const QString& t=0, const Date& disponible=Date(0,0,0), const Date& ech=Date(0,0,0),bool preemp=0,const Duree& duree=0){
        if(description=="unitaire")
            return new TUnitaire(id,t,disponible,ech,preemp,duree);
        if(description=="composite")
            return new TComposite(id,t,disponible,ech);
        return NULL;
};
};

#endif // TACHE_H

