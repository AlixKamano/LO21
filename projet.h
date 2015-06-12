#ifndef PROJET_H
#define PROJET_H

#include<QtWidgets>
#include <iostream>
#include<QString>
#include<QDate>
#include<QTextStream>
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
        QDate dispo;
        QDate echeance;
        Tache** taches;
        int nb;
        int nbMax;
        QString file;

        Projet(const Projet& t);
        Projet& operator=(const Projet& t);
        void addItem(Tache* t);
    public:
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
<<<<<<< HEAD
        class AProgIterator{
        private:
            Tache** currentTache;
            unsigned int nb;
            AProgIterator(Tache** u,unsigned int n):currentTache(u),nb(n){
                while(nb!=0&&(*currentTache)->getStatut!=-1){
                   nb--; currentTache++;
                }
            };
        public:
            bool isDone()const{return nb==0;}
            void next(){
                if(isDone()) throw CalendarException("Erreur, pas de prochaine tache");
                do{ currentTache++;nb--;}while(nb!=0&&(*currentTache)->getStatut()!=-1);}
        };
=======
>>>>>>> 9c78b1d40b3e82b6b14be9425bda3cbad992eef1


        Projet(const QString& id, const QString& t, const QDate& disponible, const QDate& ech, int max=10) : statut(0),identificateur(id), titre(t), dispo(disponible), echeance(ech), nbMax(max), nb(0), taches(new Tache*[max]){}
        ~Projet(){
            for(int i=0;i<nb;i++) delete taches[i];
            delete[] taches;}
        QString getId() const {return identificateur;}
        QString getTitre() const {return titre;}
        QDate getDispo()const{return dispo;}
        QDate getEcheance()const{return echeance;}
        //A def
        Tache* getTache(const QString& id)const;
        void ajouterTache(const QString& desc, const QString& id, const QString& t,const Duree& du, const QDate& dispo, const QDate& deadline,bool preempt );
        IteratorSTL begin();
        IteratorSTL end();
<<<<<<< HEAD
        AProgIterator getAProgIterator(){return AProgIterator(taches,nb);}
=======
        void load(const QString& f);
>>>>>>> 9c78b1d40b3e82b6b14be9425bda3cbad992eef1
        void save(const QString& f);
};

#endif // PROJET_H

