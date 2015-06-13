
#ifndef EVTMANAGER_H
#define EVTMANAGER_H
//
#include "evenement.h"
using namespace std;
// blabla
class EvtManager {
    //Singleton
private:
    Evt** evt;
    int nb;
    int nbMax;
    EvtManager():nb(0), nbMax(0),evt(0){};
    EvtManager(const EvtManager& pm);
    ~EvtManager(){
        for(int i = 0; i<nb;i++) delete evt[i];
        delete[] evt;
    };
    EvtManager& operator=(const EvtManager& pm);

    struct Handler{
        EvtManager* instance;
        Handler():instance(0){};
        ~Handler(){if(instance) delete instance;};
    };
    static Handler handler;
public:
    class IteratorSTL{
        private:
            friend class EvtManager;
            Evt** currentEvt;
            IteratorSTL(Evt** p):currentEvt(p){};
        public:
            IteratorSTL operator++(){
                ++currentEvt;
                return *this;
            };
            IteratorSTL operator--(){
                --currentEvt;
                return *this;
            };
            bool operator!=(const IteratorSTL& it) const {return currentEvt!=it.currentEvt;};
            const Evt& operator*() const{return **currentEvt;};
    };

    void ajouterEvt(const QString& desc, void* ptr, const QDate& da, const Horaire& hd, const Horaire &hf, const Duree& d);
        //On appelle d'abord EvtFactory avec un signal permettant de choisir Tache/ActivitÃ©
        //Appel fct virtuelle pure "programmer" de Evt qui appelle "prgrammer" de EvtA ou EvtT
        //On fait ici les vÃ©rif d'evt qui ne se chevauchent pas.

    Evt** getEvt(){return evt;};
    //const Evt** getEvt()const{return evt;};
    //Evt* trouverEvt();	En a-t-on besoin ?
    static EvtManager& getInstance();
    static void freeInstance();
    IteratorSTL begin()const;
    IteratorSTL end()const;
};

#endif // EVTMANAGER_H

