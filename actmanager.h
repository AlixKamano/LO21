#ifndef ACTMANAGER_H
#define ACTMANAGER_H
#include "activite.h"
//! \class ActivitéManager
//! \brief Classe permettant de gérer les activités
Activite** activites;       //!< Tableau d'activités
class ActiviteManager{

    int nb;     //!< Nombre d'activités dans le tableau
    int nbMax;  //!< Taille maximale du tableau
    ActiviteManager():nb(0),nbMax(0),activites(0){} //!< Constructeur sans arguments privé
    ActiviteManager(const ActiviteManager& am); //!< Constructeur privé de recopie
    ~ActiviteManager(){         //!< Destructeur de la classe
        for(int i=0;i<nb;i++) delete activites[i];
        delete[] activites;
    }
    void addItem(Activite* p);      //!< Méthode privée permettant l'ajout d'une activité
    ActiviteManager& operator=(const ActiviteManager& am);      //!< Surcharge de l'opérateur =
    //! \struct Handler
    //! \brief Design Pattern Singleton, permet d'assurer de l'unicité de l'ActivitéManager
    struct Handler{

        ActiviteManager* instance;      //!< Pointeur vers ActivitéManager
        Handler():instance(0){}         //!< Constructeur privé
        ~Handler(){if(instance) delete instance;}   //!< Destructeur
    };
    static Handler handler;     //!< Permet l'existence du Handler même lorsqu'aucun objet ActivitéManager n'existe
public:
    //! \class IteratorSTL
    //! \brief Permet de parcourir les activités référencées dans ActivitéManager (Design Pattern Iterator)
    class IteratorSTL{

    private:
        friend class ActiviteManager;
        Activite** currentAct;      //!< Pointeur vers l'activité actuellement pointée
        IteratorSTL(Activite** a):currentAct(a){}   //!< Constructeur. Cette fonction instancie currentAct sur le pointeur passé en paramètre
    public:
        IteratorSTL operator++(){   //!< Surcharge de l'opérateur ++. Incrémente currentAct de 1.
            ++currentAct;
            return *this;
        }
        //! Surcharge de l'opérateur !=.
        //! Cette fonction prend en paramètre un autre itérateur et compare leur currentAct
        bool operator!=(const IteratorSTL& it)const{
            return currentAct!=it.currentAct;
        }
        const Activite& operator*()const{return **currentAct;}  //!< Surcharge de l'opérateur *. Retourne l'activité pointée par currentAct
    };
    //! Fonction permettant d'ajouter une activité
    //! \param QString& id : identifiant de l'activité, \param QString& t : titre de l'activité, \param Duree d : durée de la tâche
    void ajouterAct(const QString& id,const QString& t, const Duree d);
    //! Fonction permettant de trouver une activité
    //! \param QString& id : identifiant de la tâche à rechercher
    //! La fonction parcourtla tableau activite jusqu'à tomber sur l'activité ayant le bon id.
    Activite *trouverActivite(const QString& id) const;
    //! Accesseur retourant le tableau de pointeurs d'Activités : activites
    Activite** getAct(){return activites;}
    //!Accesseur retournant le singleton ActiviteManager
    //! Si le singleton n'existe pas encore, la fonction le créée, sinon elle se contente de le retourner
    static ActiviteManager& getInstance();
    //! Fonction permettant de détruire l'instance du Handler et donc de détruire ActivitéManager
    static void freeInstance();
    //! Fonction retournant un itérateur sur le début du tableau activité
    IteratorSTL begin()const;
    //! Fonction retournant un itérateur sur la fin du tableau activité
    IteratorSTL end()const;
};

#endif // ACTMANAGER_H

