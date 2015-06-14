
#ifndef EVTMANAGER_H
#define EVTMANAGER_H
//
#include "evenement.h"
using namespace std;
//! \class Evenement Manager
//! \brief Classe permettant de gérer les différents évènements. Classe singleton
class EvtManager {

    //Singleton
private:
    Evt** evt;      //!< Tableau de pointeurs d'évènements
    int nb;         //!< Nombre d'évènements présents dans le tableau
    int nbMax;      //!< Taille du tableau
    EvtManager():nb(0), nbMax(10){evt = new Evt*[nbMax];}   //!< Constructeur par défaut privé
    EvtManager(const EvtManager& pm);       //!< Constructeur de recopie privé
    //! Destructeur
    //! Détruit le tableau qui a été alloué dynamiquement
    ~EvtManager(){
        for(int i = 0; i<nb;i++) delete evt[i];
        delete[] evt;
    };
    EvtManager& operator=(const EvtManager& pm);    //!< Surcharge de l'opérateur =
    //! \struct Handler
    //! \brief Cette structure permet d'assurer l'unicité de l'EvenementManager
    struct Handler{

        EvtManager* instance;
        Handler():instance(0){};    //! Constructeur
        ~Handler(){if(instance) delete instance;}   //! Destructeur
    };
    static Handler handler; //!< Permet d'assurer l'existence du Handler même en absence d'objets EvtManager
public:
    //! \class IteratorSTL
    //! \brief Classe permettant de parcourir les différents évènements du tableau d'EvenementManager
    class IteratorSTL{

        private:
            friend class EvtManager;
            Evt** currentEvt;   //!< Pointeur vers l'évènement actuellement pointé
            IteratorSTL(Evt** p):currentEvt(p){}    //!< Constructeur initialisant currentEvt sur le pointeur passé en argument
        public:
            //! Surcharge de l'opérateur ++
            IteratorSTL operator++(){
                ++currentEvt;
                return *this;
            }
            //! Surcharge de l'opérateur --
            IteratorSTL operator--(){
                --currentEvt;
                return *this;
            }
            //! Surcharge de l'opérateur !=
            bool operator!=(const IteratorSTL& it) const {return currentEvt!=it.currentEvt;}
            //! Surcharge de l'opérateur *
            //! Cette fonction nous retourne l'évènement pointé par currentEvt et non un pointeur
            const Evt& operator*() const{return **currentEvt;}
    };
    //! \class ItSemaine
    //! \brief Itérateur permettant d'accéder aux événments programmés durant une certaine semaine
    class ItSemaine{

    private:
        friend class EvtManager;
        Evt** currentEvt;   //!< Pointeur vers l'évènement actuellement pointé
        int nb;     //!< Nombre total d'évènement enregistrés
        const QDate debut;  //!< Date de début de la semaine
        const QDate fin;    //!< Date de fin de la semaine
        //! Constructeur de l'itérateur
        //! \param Evt** e : pointeur de pointeur d'évènement pour initialiser currentEvt
        //! \param int n : nombre d'évènements \param QDate d : date de début \param QDate f : date de fin
        //! Le constructeur parcourt tous les évènements à partir de e jusqu'à trouver un évènement programmé durant la semaine spécifiée.
        //! On initialise alors currentEvt sur cet évènement
        ItSemaine(Evt** e,int n,QDate d,QDate f):currentEvt(e),nb(n),debut(d),fin(f){
            while(nb>0 && (debut>((*currentEvt)->getDate()) || fin<((*currentEvt)->getDate()))){
                   nb--;
                   currentEvt++;
                  }
        }
    public:
        //! Constructeur sans arguments
        ItSemaine():currentEvt(0),nb(0),debut(QDate(0,0,0)),fin(QDate(0,0,0)){}
        //! Fonction permettant de savoir si l'itérateur a parcouru tous les évènements disponibles
        bool isDone()const{return nb==0;}
        //! Fonction permettant de passer au prochain évènement de la semaine
        //! Ici aussi nous parcourons le tableau d'évènements jusqu'à en trouver un qui convienne
        void next(){
            do{
                currentEvt++;
                nb--;
            }while(nb>0 && (debut>((*currentEvt)->Evt::getDate()) || fin<((*currentEvt)->Evt::getDate())));
        }
        //! Surcharge de l'opérateur !=
        bool operator!=(const ItSemaine& it)const {return currentEvt!=it.currentEvt;}
        const Evt& operator*() const{return **currentEvt;}
        QDate getD(){return debut;}
        };
    //! Fonction permettant d'initialiser un itérateur
    ItSemaine getItSemaine(const QDate d, const QDate f){return ItSemaine(evt,nb,d,f);}
    //! Fonctin permettant d'ajouter un évènement
    //! \param QString& desc : description de l'évènement (tâche ou activité)
    //! \param void *ptr : Pointeur vers l'évènements qui sera ensuite casté
    //! \param QDate da : Date de l'évènemenent \param Horaire& hd : Horaire de début de l'évènenement \param Horaire& hf : Horaire de fin \param Duree& d : Durée
    //! Cette fonction appelle d'abord EvtFactory en passant desc en paramètre afin que le bon type d'évènement soit créé. Nous stockons le pointeur retourné dans le tableau
    void ajouterEvt(const QString& desc, void* ptr, const QDate& da, const Horaire& hd, const Horaire &hf, const Duree& d);
    //! Accesseur au tableau d'évènement
    Evt** getEvt(){return evt;}
    //! Accesseur au nombre total d'évènement
    int getNb(){return nb;}
    //! Accesseur retournant le singleton EvenementManager
    static EvtManager& getInstance();
    //! Fonction permettant de détruire le singleton EvenementManager
    static void freeInstance();
    //! Fonction retournant un itérateur sur le début du tableau d'évènements
    IteratorSTL begin()const;
    //! Fonction retournant un itérateur sur la fin du tableau d'évènements
    IteratorSTL end()const;
};

#endif // EVTMANAGER_H

