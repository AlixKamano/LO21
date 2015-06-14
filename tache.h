#ifndef TACHE_H
#define TACHE_H

#include <iostream>
#include <QString>
#include "timing.h"
#include <QMessageBox>

using namespace std;
using namespace TIME;


//Statut = 0 => Tache non programmée, à venir. Date d'échéance non dépassée
//Statut = -1 => Tache non programmée, date d'échéance dépassée
//Statut = 1 => Tache programmée/réalisée
class Tache {
    private:
        int statut;
        QString identifiant;
        QString titre;
        Tache* precedence;
        QDate dispo;
        QDate echeance;
        //Tache(const QString& id, const QString& t, const QDate& disponible, const QDate& ech) : statut(0),identifiant(id), titre(t),dispo(disponible), echeance(ech), precedence(0){};
        //Tache(const Tache& t);
        Tache& operator=(const Tache& t);

    public:
        Tache(const QString& id=0, const QString& t=0,Tache* prec=0, const QDate& disponible=QDate(0,0,0), const QDate& ech=QDate(0,0,0)) : statut(0), identifiant(id),precedence(prec), titre(t),dispo(disponible), echeance(ech){}
        Tache(const Tache& t);
        int getStatut() const{return statut;}
        QString getId() const {return identifiant;}
        QString getTitre() const {return titre;}
        Tache* getPrecedence() const{return precedence;}
        int getStatutPrecedence()const;
        QDate getDispo()const{return dispo;}
        QDate getEcheance()const{return echeance;}
        void setStatut(int s) {statut=s;}
        virtual void afficher()=0;
        virtual bool getPreemptive()const=0;
        virtual QString getType() const=0;
        virtual ~Tache(){}
};

class TUnitaire : public Tache{
    private:
        bool preemptive;
        Duree duree;
    public:
        TUnitaire(const QString& id, const QString& t,Tache* prec, const QDate& disponible, const QDate& ech, bool premp, const Duree& dur) : Tache(id,t,prec,disponible,ech),preemptive(premp),duree(dur){}
        TUnitaire():Tache(),preemptive(0),duree(0){}
        virtual bool getPreemptive()const {return preemptive;}
        Duree getDuree()const{return duree;}
        void setDuree(const Duree& d){duree=d;}
        void afficher(){cout<<1;}
        QString getType() const{return "unitaire";}
        ~TUnitaire(){}
};

class TComposite : public Tache{
    private:
        Tache** sousTaches;
        int nb;
        int nbMax;
    public :
        virtual bool getPreemptive()const{return false;}
        class IteratorSTL{
            private:
                Tache** currentTache;
            public:
                IteratorSTL(Tache** u): currentTache(u){}
                IteratorSTL operator++(){
                    ++currentTache;
                    return *this;
                };
                IteratorSTL operator--(){
                    --currentTache;
                    return *this;
                };
                bool operator!=(const IteratorSTL& it) const {return currentTache!= it.currentTache;}
                const Tache& operator*() const {return **currentTache;}
            };
        TComposite(const QString& id, const QString& t,Tache* prec, const QDate& disponible, const QDate& ech) : Tache(id,t,prec,disponible,ech),sousTaches(0),nb(0),nbMax(0){}
        TComposite():Tache(),sousTaches(0),nb(0),nbMax(0){}
        Tache** getSousTaches()const {return sousTaches;}
        Tache* getSousTache(const QString& id)const;
        void ajouterSousTache(const QString& desc, const QString& id,Tache* prec, const QString& t,const Duree& du, const QDate& dispo, const QDate& deadline,bool preempt );
        void addSousTache(Tache* t);
        void afficher(){cout<<2;}
        ~TComposite(){delete[] sousTaches;}
        IteratorSTL begin() const;
        IteratorSTL end() const;
        QString getType()const{return "composite";}
};

class TacheFactory {
public:
    static Tache* NewTache(const QString& description ,const QString& id=0,Tache* prec=0,const QString& t=0,const QDate& disponible=QDate(0,0,0), const QDate& ech=QDate(0,0,0),const Duree& duree=0, bool preemp=0){
        if(description=="unitaire")
            return new TUnitaire(id,t,prec,disponible,ech,preemp,duree);
        if(description=="composite")
            return new TComposite(id,t,prec,disponible,ech);
        return NULL;
    }
};

#endif // TACHE_H
