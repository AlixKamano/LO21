#ifndef ACTMANAGER_H
#define ACTMANAGER_H
#include "activite.h"

class ActiviteManager{
    //! \class ActivitéManager
    //! \brief Classe permettant de gérer les activités
    Activite** activites;       //!< Tableau d'activités
    int nb;     //!< Nombre d'activités dans le tableau
    int nbMax;  //!< Taille maximale du tableau
    ActiviteManager():nb(0),nbMax(0),activites(0){} //!< Constructeur sans arguments privé
    ActiviteManager(const ActiviteManager& am); //!< Constructeur privé de recopie
    ~ActiviteManager(){         //!< Destructeur de la classe
        for(int i=0;i<nb;i++) delete activites[i];
        delete[] activites;
    }
    void addItem(Activite* p);      //!< Méthode permettant l'ajout d'une activité
    ActiviteManager& operator=(const ActiviteManager& am);      //!< Surcharge de l'opérateur =

    struct Handler{
       //! \class Handler
       //! \brief Design Pattern Singleton, permet d'assurer de l'unicité de l'ActivitéManager
        ActiviteManager* instance;      //!< Pointeur vers ActivitéManager
        Handler():instance(0){}         //!< Constructeur privé
        ~Handler(){if(instance) delete instance;}   //!< Destructeur
    };
    static Handler handler;     //!< Permet l'existence du Handler
public:
    class IteratorSTL{
    private:
        friend class ActiviteManager;
        Activite** currentAct;
        IteratorSTL(Activite** a):currentAct(a){}
    public:
        IteratorSTL operator++(){
            ++currentAct;
            return *this;
        }
        bool operator!=(const IteratorSTL& it)const{
            return currentAct!=it.currentAct;
        }
        const Activite& operator*()const{return **currentAct;}
    };
    void ajouterAct(const QString& id,const QString& t, const Duree d);
    Activite *trouverActivite(const QString& id) const;
    Activite** getAct(){return activites;}
    static ActiviteManager& getInstance();
    static void freeInstance();
    IteratorSTL begin()const;
    IteratorSTL end()const;
};

#endif // ACTMANAGER_H

