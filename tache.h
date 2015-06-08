#ifndef __LO21_projet__tache__
#define __LO21_projet__tache__

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
class Tache {
    private:
        int statut;
        QString identificateur;
        QString titre;
        Tache** precedence;
        Date dispo;
        Date echeance;
        Tache(const QString& id, const QString& t, const Date& disponible, const Date& ech) : statut(0),identificateur(id), titre(t),dispo(disponible), echeance(ech), precedence(0){};
        Tache(const Tache& t);
        Tache& operator=(const Tache& t);
        friend class TacheManager;
    public:
        int getStatut() const{return statut;};
        QString getId() const {return identificateur;};
        QString getTitre() const {return titre;};
        Tache** getPrecedence() const{return precedence;};
        Date getDispo()const{return dispo;};
        Date getEcheance()const{return echeance;};
        void setStatut(int s){statut=s;};
};



class TUnitaire : public Tache{
    private:
        bool preemptive;
        Duree duree;
    public:
        bool getPremptive()const{return preemptive;};
        Duree getDuree()const{return duree;};
};

class TComposite : public Tache{
    private:
        Tache** sousTaches;
        int nb;
        int nbMax;
        public :
        Tache** getSousTaches()const {return sousTaches;};
};

#endif 
