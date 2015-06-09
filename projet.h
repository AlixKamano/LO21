#ifndef PROJET_H
#define PROJET_H

#include <iostream>
#include<QString>
#include "timing.h"
#include "tache.h"

using namespace TIME;

class ProjetException{
public:
    ProjetException(const QString& message):info(message){}
    QString getInfo() const { return info; }
private:
    QString info;
};


//Statut = 0 => Projet non programmé, à venir
class Projet {
    //friend class ProjetManager;
    private:
        int statut;
        QString identificateur;
        QString titre;
        Date dispo;
        Date echeance;
        Tache** taches;
        int nb;
        int nbMax;

        Projet(const Projet& t);
        Projet& operator=(const Projet& t);
        void addItem(Tache* t);

        class IteratorSTL{
            private:
                Tache** currentTache;
            public:
                IteratorSTL(Tache** u): currentTache(u){};
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

    public:
        Projet(const QString& id, const QString& t, const Date& disponible, const Date& ech, int max=10) : statut(0),identificateur(id), titre(t), dispo(disponible), echeance(ech), nbMax(max), nb(0), taches(new Tache*[max]){};
        ~Projet(){
            for(int i=0;i<nb;i++) delete taches[i];
            delete[] taches;}
        QString getId() const {return identificateur;};
        QString getTitre() const {return titre;};
        Date getDispo()const{return dispo;};
        Date getEcheance()const{return echeance;};
        //A def
        Tache* getTache(const QString& id)const;
        void ajouterTache(const QString& desc, const QString& id, const QString& t, const Date& dispo, const Date& deadline );
        IteratorSTL begin();
        IteratorSTL end();
};

#endif // PROJET_H

