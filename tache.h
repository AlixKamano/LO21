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
//! \class Tache
//! \brief Classe abstraite permettant de stocker des tâches
class Tache {
private:
    int statut;     //!< Statut de la tâche. 0: Têche non programmée, échéance non dépassée. 1 : Tache programmée. -1 : Tache non programmée, échéance dépassée
    QString identifiant;     //!< Identificateur unique de la tâche
    QString titre;      //!< Titre de la tâche
    Tache* precedence;     //!< Pointeur vers la tâche précédente
    int nbPrec;     //!< Nombre de tâches précédenteq
    int nbPrecMax;  //!< Taille du tableau
    QDate dispo;    //!< Date de disponibilité
    QDate echeance; //!< Date d'échéance
    //! Surcharge de l'opérateur =
    Tache& operator=(const Tache& t);
public:
    //! Constructeur de tâche
    //! Cette fonction appelle la fonction addPrécédence pour ajouter une précédence de tâche
    Tache(const QString& id=0, const QString& t=0,Tache* prec=0, const QDate& disponible=QDate(0,0,0), const QDate& ech=QDate(0,0,0)) : statut(0), identifiant(id),precedence(prec), titre(t),dispo(disponible), echeance(ech){}
    //! Constructeur de recopie
    Tache(const Tache& t);
    //! Accesseur au statut de la tâche
    int getStatut() const{return statut;}
    //! Accesseur à l'identifiant  de la tâche
    QString getId() const {return identifiant;}
    //! Accesseur au titre de la tâche
    QString getTitre() const {return titre;}
    //! Accesseur à la tâche précédente
    Tache* getPrecedence() const{return precedence;}
    //! Fonction retournant le statut de la tâche précédente
    int getStatutPrecedence()const;
    //! Accesseur à la date de disponibilité de la  tâche
    QDate getDispo()const{return dispo;}
    //! Accesseur à la date d'échéance de la tâche
    QDate getEcheance()const{return echeance;}
    //! Fonction permettant de modifier le statut de la tâche
    void setStatut(int s) {statut=s;}
    // //! Fonction permettant d'ajouter une précédence
    //void addPrecedence(Tache* t);
    //! Fonction virtuelle pure permettant de savoir si une tâche est préemptive ou non
    virtual bool getPreemptive()const=0;
    //! Fonction virtuelle pure retournant le type de tâche (unitaire ou composite)
    virtual QString getType() const=0;
    //! Destructeur virtuel de tâche
    virtual ~Tache(){}
};

//! \class TacheUnitaire
//! \brief Classe fille de Tache. Permet de créer des tâches unitaires
class TUnitaire : public Tache{
private:
    bool preemptive;    //!< Indicateur de la préemptabilité de la tâche
    Duree duree;        //!< Durée de la tâche
public:

    //! Constructeur de TacheUnitaire
    //! Ce constructeur fait appel au constructeur de Tâche
    TUnitaire(const QString& id, const QString& t,Tache* prec, const QDate& disponible, const QDate& ech, bool premp, const Duree& dur) : Tache(id,t,prec,disponible,ech),preemptive(premp),duree(dur){}
    //! Constructeur par défaut de TacheUnitaire
    TUnitaire():Tache(),preemptive(0),duree(0){}
    //! Accesseur retournant si la tâche est préemptive ou non
    virtual bool getPreemptive()const {return preemptive;}
    //! Accesseur retournant la durée de la tâche
    Duree getDuree()const{return duree;}
    //! Fonction permettant de modifier la date
    //! Cette fonction est utile lorsqu'on programme une tâche préemptive
    void setDuree(const Duree& d){duree=d;}
    //! Fonction retournant le type de la tâche (unitaire)
    QString getType() const{return "unitaire";}
    ~TUnitaire(){}
};

//! \class TacheComposite
//! \brief Classe fille de Tache. Permet de créer des tâches composites
class TComposite : public Tache{
private:
    Tache** sousTaches;     //!< Tableau de pointeurs sur des sous-tâches
    int nb;     //!< Nombre de sous-tâches
    int nbMax;  //!< Taille du tableau
public :
    //! Accesseur permettant de retourner que la tâche n'est pas préemptive
    virtual bool getPreemptive()const{return false;}
    //! \class IteratorSTL
    //! \brief Classe permettant de parcourir les sous-tâches du tableau
    class IteratorSTL{
    private:
        Tache** currentTache;       //!< Pointeur vers la tâche actuellement pointée
    public:
        //! Constructeur de l'itérateur
        IteratorSTL(Tache** u): currentTache(u){}
        //! Surcharge de l'opérateur ++
        IteratorSTL operator++(){
            ++currentTache;
            return *this;
        };
        //! Surcharge de l'opérateur--
        IteratorSTL operator--(){
            --currentTache;
            return *this;
        };
        //! Surcharge de l'opérateur !=
        bool operator!=(const IteratorSTL& it) const {return currentTache!= it.currentTache;}
        //! Surcharge de l'opérateur *
        const Tache& operator*() const {return **currentTache;}
    };
    //! Constructeur de TacheComposite
    //! Ce constructeur fait appel au constructeur de Tache
    TComposite(const QString& id, const QString& t,Tache* prec, const QDate& disponible, const QDate& ech) : Tache(id,t,prec,disponible,ech),sousTaches(0),nb(0),nbMax(0){}
    //! Constructeur par défaut  de TacheComposite
    TComposite():Tache(),sousTaches(0),nb(0),nbMax(0){}
    //! Accesseur retournant le tableau de sous-tâches
    Tache** getSousTaches()const {return sousTaches;}
    //! Accesseur permettant de retourner la sous-tâche ayant un id égal à celui passé en argument
    Tache* getSousTache(const QString& id)const;
    //! Fonction permettant d'ajouter une sous-tâche au tableau.
    //! Cette fonction fait appel au constructeur de tâche
    void ajouterSousTache(const QString& desc, const QString& id,Tache* prec, const QString& t,const Duree& du, const QDate& dispo, const QDate& deadline,bool preempt );
    //! Fonction permettant d'ajouter une sous-tâche au tableau
    //! Cette fonction prend en argument un pointeur de Tache* qui est ensuite inséré dans le tableau
    void addSousTache(Tache* t);
    //! Destructeur de TacheComposite détruisant le tableau de sous-tâches
    ~TComposite(){delete[] sousTaches;}
    //! Fonction retournant un itérateur sur le début du tableau de sous-tâches
    IteratorSTL begin() const;
    //! Fonction retournant un itérateur sur la fin du tableau de sous-tâches
    IteratorSTL end() const;
    //! Accesseur retournant le type de la tâche (composite)
    QString getType()const{return "composite";}
};

//! \class TacheFactory
//! \brief Classe permettant de créer une TacheUnitaire ou une TacheComposite
//! Design Pattern Abstract Factory
class TacheFactory {
public:
    //! Fonction permettant de créer une TUnitaire ou une TComposite en fonction de la description passée en paramètre.
    //! La fonction retourne ensuite un pointeur vers la tâche créée
    static Tache* NewTache(const QString& description ,const QString& id=0,Tache* prec=0,const QString& t=0,const QDate& disponible=QDate(0,0,0), const QDate& ech=QDate(0,0,0),const Duree& duree=0, bool preemp=0){
        if(description=="unitaire")
            return new TUnitaire(id,t,prec,disponible,ech,preemp,duree);
        if(description=="composite")
            return new TComposite(id,t,prec,disponible,ech);
        return NULL;
    }
};

#endif // TACHE_H
