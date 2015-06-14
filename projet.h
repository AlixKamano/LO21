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
//Statut = 0 => Projet non programmé, à venir
//! \class Projet
//! \brief Classe permettant de gérer les différentes tâches qui lui sont affectées
class Projet {

    private:
        int statut;     //!< Statut du projet. 1 : Projet terminé, 0 : Projet en cours
        QString identificateur;     //!< Identificateur du projet
        QString titre;      //!< Titre du projet
        QDate dispo;        //!< Date de disponibilité du projet
        QDate echeance;     //!< Date d'échéance du projet
        Tache** taches;     //!< Tableau de taches appartenant au projet
        int nb;         //!< Nombre de tâches dans le projet
        int nbMax;      //!< Taille du tableau
        QString file;   //!< Nom du fichier pour l'exportation
        //! Constructeur de recopie
        Projet(const Projet& t);
        //! Surcharge de l'opérateur =
        Projet& operator=(const Projet& t);
        //! Fonction permettant d'ajouter une Tache t au projet
        void addItem(Tache* t);
    public:
        //! \class IteratorSTL
        //! \brief Classe permettant de parcourir les différentes tâches du projet
        class IteratorSTL{
            private:
                Tache** currentTache;   //! Pointeur vers la tâche actuellement pointée
            public:
                //! Accesseur retournant la tâche actuellement pointée
                IteratorSTL(Tache** u): currentTache(u){}
                //! Surcharge de l'opérateur ++
                IteratorSTL operator++(){
                    ++currentTache;
                    return *this;
                };
                //! Surcharge de l'opérateur --
                IteratorSTL operator--(){
                    --currentTache;
                    return *this;
                };
                //! Surcharge de l'opérateur !=
                bool operator!=(const IteratorSTL& it) const {return currentTache!= it.currentTache;}
                //! Surcharge de l'opétateur *
                const Tache& operator*() const {return **currentTache;}
            };

        //! Constructeur
        Projet(const QString& id, const QString& t, const QDate& disponible, const QDate& ech, int max=10) : taches(new Tache*[max]),  identificateur(id), titre(t), dispo(disponible), echeance(ech),   statut(0), nb(0), nbMax(max){}
        ~Projet(){
            for(int i=0;i<nb;i++) delete taches[i];
            delete[] taches;}
        QString getId() const {return identificateur;}
        QString getTitre() const {return titre;}
        QDate getDispo()const{return dispo;}
        QDate getEcheance()const{return echeance;}
        //A def
        Tache* getTache(const QString& id)const;
        void ajouterTache(const QString& desc, const QString& id,Tache* prec, const QString& t,const Duree& du, const QDate& dispo, const QDate& deadline,bool preempt );
        IteratorSTL begin();
        IteratorSTL end();
        void load(const QString& f);
        void save(const QString& f);
};

#endif // PROJET_H
