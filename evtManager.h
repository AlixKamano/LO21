
#ifndef EVTMANAGER_H
#define EVTMANAGER_H
//
#include "evenement.h"
using namespace std;
class EvtManager {
    //Singleton
private:
    Evt** evt;
    int nb;
    int nbMax;
    EvtManager():nb(0), nbMax(0),evt(0){}
    EvtManager(const EvtManager& pm);
    ~EvtManager(){
        for(int i = 0; i<nb;i++) delete evt[i];
        delete[] evt;
    };
    EvtManager& operator=(const EvtManager& pm);

    struct Handler{
        EvtManager* instance;
        Handler():instance(0){};
        ~Handler(){if(instance) delete instance;}
    };
    static Handler handler;
public:
    class IteratorSTL{
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

