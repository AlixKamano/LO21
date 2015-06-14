#ifndef PROJETMANAGER_H
#define PROJETMANAGER_H

#include <iostream>
#include "projet.h"

//! \class ProjetManager
//! \brief Classe permettant de gérer les différents projets existant dans l'application
class ProjetManager {
private:
    Projet** projets;   //!< Tableau de pointeurs sur les différents projets de l'application
    int nb;     //!< Nombre de projets
    int nbMax;      //!< Taille du tableau
    //!< Fonction permettant d'ajouter un projet dans ProjetManaher
    void addItem(Projet* p);
    //! Constructeur par défaut
    ProjetManager():  projets(0), nb(0), nbMax(0){}
    //! Constructeur privé de recopie
    ProjetManager(const ProjetManager& pm);
    //! Destructeur de ProjetManager
    //! Cette fonction détruit le tableau de projets
    ~ProjetManager(){
        for (int i=0;i<nb;i++) delete projets[i];
        delete[] projets;
    };
    //! Surcharge de l'opérateur =
    ProjetManager& operator=(const ProjetManager& pm);
    //! \struct Handler
    //! \brief Permet d'assurer l'unicite du ProjetManager
    struct Handler{
        ProjetManager *instance;
        Handler():instance(0){};
        ~Handler(){if(instance) delete instance;}
    };
    static Handler handler; //!< Permet d'assurer l'existence du handler même lorsqu'aucun objet ProjetManager n'existe
public:
    //! \class Iterator STL
    //! \brief Classe permettant de parcourir les différents projets du tableau
    class IteratorSTL{
    private:
        friend class ProjetManager;
        Projet** currentProjet;
        IteratorSTL(Projet** p): currentProjet(p){};    //!< Constructeur de l'itérateur
    public:
        //! Surcharge de l'opérateur ++
        IteratorSTL operator++(){
            ++currentProjet;
            return *this;
        };
        //! Surcharge de l'opérateur --
        IteratorSTL operator--(){
            --currentProjet;
            return *this;
        };
        //! Surcharge de l'opérateur !=
        bool operator!=(const IteratorSTL& it) const {return currentProjet!= it.currentProjet;}
        //! Surcharge de l'opérateur *
        Projet& operator*() {return **currentProjet;}
    };
    //! Fonction permettant d'ajouter un projet
    //! La fonction crée le nouveau projet puis ajoute son pointeur dans le tableau projets
    void ajouterProjet(const QString& id, const QString& t, const QDate& dispo, const QDate& deadline, int max);
    //! Fonction retournant un projet ayant l'id spécifié en argument
    Projet& getProjet(const QString& id);
    //! Surcharge de getProjet
    const Projet& getProjet(const QString& id) const;
    //! Fonction identique à getProjet mais renvoyant un pointeur et non une référence
    Projet *trouverProjet(const QString& id) const;
    //! Accesseur retournant une référence vers ProjetManager et le créant s'il n'existait pas déjà
    static ProjetManager& getInstance();
    //! Fonction permettant de détruire ProjetManager en appelant son destructeur
    static void freeInstance();
    //! Fonction retournant un itérateur sur le début du tableau projets
    IteratorSTL begin();
    //! Fonction retourant un itérateur sur la fin du tableau projets
    IteratorSTL end();
};

#endif // PROJETMANAGER_H
