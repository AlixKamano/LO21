
#ifndef EVTMANAGER_H
#define EVTMANAGER_H
//
#include "evenement.h"
using namespace std;
class EvtManager {
    //! \class Evenement Manager
    //! \brief Classe permettant de gérer les différents évènements. Classe singleton
    //Singleton
private:
    Evt** evt;      //!< Tableau de pointeurs d'évènements
    int nb;         //!< Nombre d'évènements présents dans le tableau
    int nbMax;      //!< Taille du tableau
    EvtManager():nb(0), nbMax(10),evt(0){}   //!< Constructeur par défaut privé
    EvtManager(const EvtManager& pm);       //!< Constructeur de recopie privé
    //! Destructeur
    //! Détruit le tableau qui a été alloué dynamiquement
    ~EvtManager(){
        for(int i = 0; i<nb;i++) delete evt[i];
        delete[] evt;
    };
    EvtManager& operator=(const EvtManager& pm);    //!< Surcharge de l'opérateur =

    struct Handler{
        //! \struct Handler
        //! \brief Cette structure permet d'assurer l'unicité de l'EvenementManager
        EvtManager* instance;
        Handler():instance(0){};    //! Constructeur
        ~Handler(){if(instance) delete instance;}   //! Destructeur
    };
    static Handler handler; //!< Permet d'assurer l'existence du Handler même en absence d'objets EvtManager
public:
    class IteratorSTL{
        //! \class IteratorSTL
        //! \brief Classe permettant de parcourir les différents évènements du tableau
        private:
            friend class EvtManager;
            Evt** currentEvt;
            IteratorSTL(Evt** p):currentEvt(p){}
        public:
            IteratorSTL operator++(){
                ++currentEvt;
                return *this;
            }
            IteratorSTL operator--(){
                --currentEvt;
                return *this;
            }
            bool operator!=(const IteratorSTL& it) const {return currentEvt!=it.currentEvt;}
            const Evt& operator*() const{return **currentEvt;}
    };

    class ItSemaine{
    private:
        friend class EvtManager;
        Evt** currentEvt;
        int nb;
        const QDate debut;
        const QDate fin;
        ItSemaine(Evt** e,int n,QDate d,QDate f):currentEvt(e),nb(n),debut(d),fin(f){
            while(nb>0 && (debut>((*currentEvt)->getDate()) || fin<((*currentEvt)->getDate()))){
                   nb--;
                   currentEvt++;
                  }
        }
    public:
        ItSemaine():currentEvt(0),nb(0),debut(QDate(0,0,0)),fin(QDate(0,0,0)){}
        bool isDone()const{return nb==0;}
        void next(){
            do{
                currentEvt++;
                nb--;
            }while(nb>0 && (debut>((*currentEvt)->Evt::getDate()) || fin<((*currentEvt)->Evt::getDate())));
        }
        bool operator!=(const ItSemaine& it)const {return currentEvt!=it.currentEvt;}
        const Evt& operator*() const{return **currentEvt;}
        QDate getD(){return debut;}
        };
    ItSemaine getItSemaine(const QDate d, const QDate f){return ItSemaine(evt,nb,d,f);}

    void ajouterEvt(const QString& desc, void* ptr, const QDate& da, const Horaire& hd, const Horaire &hf, const Duree& d);
        //On appelle d'abord EvtFactory avec un signal permettant de choisir Tache/ActivitÃ©
        //Appel fct virtuelle pure "programmer" de Evt qui appelle "prgrammer" de EvtA ou EvtT
        //On fait ici les vÃ©rif d'evt qui ne se chevauchent pas.


    Evt** getEvt(){return evt;}
    //const Evt** getEvt()const{return evt;};
    //Evt* trouverEvt();	En a-t-on besoin ?
    int getNb(){return nb;}
    static EvtManager& getInstance();
    static void freeInstance();
    IteratorSTL begin()const;
    IteratorSTL end()const;
};

#endif // EVTMANAGER_H

