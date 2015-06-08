#ifndef __LO21_projet__projet__
#define __LO21_projet__projet__

#include <iostream>
#include"tacheManager.h"

class ProjetException{
public:
    ProjetException(const QString& message):info(message){}
    QString getInfo() const { return info; }
private:
    QString info;
};


//Statut = 0 => Projet non programmé, à venir
class Projet {
    private:
        int statut;
        QString identificateur;
        QString titre;
        Date dispo;
        Date echeance;
        Tache** taches;
        int nb;
        int nbMax;
        Projet(const QString& id, const QString& t, const Date& disponible, const Date& ech, int max=10) : statut(0),identificateur(id), titre(t), dispo(disponible), echeance(ech), nbMax(max), nb(0), taches(new Tache*[max]){};
        Projet(const Projet& t);
        Projet& operator=(const Projet& t);
        friend class ProjetManager;
    public:
        QString getId() const {return identificateur;};
        QString getTitre() const {return titre;};
        Date getDispo()const{return dispo;};
        Date getEcheance()const{return echeance;};
        Tache** getTache()const{return taches;};
};

#endif
