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
    QString identifiant;     //!< identifiant du projet
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

    //! Constructeur de Projet
    //! \param QString& id : ID du projet \param QString& t : titre du projet \param QDate& disponible : date de disponiblité du projet
    //! \param QDate& echeance : date d'échéance du projet \param int max : taille initiale du tableau de tâches
    Projet(const QString& id, const QString& t, const QDate& disponible, const QDate& ech, int max=10) : taches(new Tache*[max]),  identifiant(id), titre(t), dispo(disponible), echeance(ech),   statut(0), nb(0), nbMax(max){}
    //! Destructeur de projet
    //! Cette fonction se charge de détruire le tableau de tâches
    ~Projet(){
        for(int i=0;i<nb;i++) delete taches[i];
        delete[] taches;}
    //! Accesseur retournant l'identifiant du projet
    QString getId() const {return identifiant;}
    //! Accesseur retournant le titre du projet
    QString getTitre() const {return titre;}
    //! Accesseur retournant la date de disponibilité du projet
    QDate getDispo()const{return dispo;}
    //! Accesseur retournant la date d'échéance du projet
    QDate getEcheance()const{return echeance;}
    //! Accesseur permettant de retourner un pointeur sur une tâche précise
    //! Pour cela, la fonction prend en paramère l'ID de la tâche à rechercher puis nous parcourons la liste des tâches pour retourner celle convenant
    Tache* getTache(const QString& id)const;
    //! Fonction permettant d'ajouter une tâche au projet.
    //! Cette fonction appelle addItem après avoir vérifié que la tâche n'existait pas déjà dans le projet
    void ajouterTache(const QString& desc, const QString& id,Tache* prec, const QString& t,const Duree& du, const QDate& dispo, const QDate& deadline,bool preempt );
    //! Fonction retournant un itérateur sur le début du tableau tâches
    IteratorSTL begin();
    //! Fonctionr retournant un itérateur sur la fin du tableau tâches
    IteratorSTL end();
    //! Fonction permettant l'export d'un projet au format XML
    //! Cette fonction parcourt toutes les tâches du projet et pour chacune réalise un export dans le fichier
    void save(const QString& f);
};

#endif // PROJET_H
