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
    QString identificateur;     //!< Identificateur unique de la tâche
    QString titre;      //!< Titre de la tâche
    Tache** precedence;     //!< Tableau de tâches précédentes
    int nbPrec;     //!< Nombre de tâches précédenteq
    int nbPrecMax;  //!< Taille du tableau
    QDate dispo;    //!< Date de disponibilité
    QDate echeance; //!< Date d'échéance
    //! Surcharge de l'opérateur =
    Tache& operator=(const Tache& t);
public:
    //! Constructeur de tâche
    //! Cette fonction appelle la fonction addPrécédence pour ajouter une précédence de tâche
    Tache(const QString& id=0, const QString& t=0,Tache* prec=0, const QDate& disponible=QDate(0,0,0), const QDate& ech=QDate(0,0,0)) : statut(0), identificateur(id), titre(t),dispo(disponible), echeance(ech){
        nbPrec=0;
        nbPrecMax=10;
        precedence=new Tache*[nbPrecMax];
        if(prec!=0)
            addPrecedence(prec);
    }
    //! Constructeur de recopie
    Tache(const Tache& t);
    //! Accesseur au statut de la tâche
    int getStatut() const{return statut;}
    //! Accesseur à l'identifiant  de la tâche
    QString getId() const {return identificateur;}
    //! Accesseur au titre de la tâche
    QString getTitre() const {return titre;}
    //! Accesseur à la tâche précédente
    Tache** getPrecedence() const{return precedence;}
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
