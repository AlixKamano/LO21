#include "evtManager.h"
//
//Méthodes de evtManager

   void EvtManager::ajouterEvt(const QString& desc, void* ptr, const QDate &da, const Horaire& hd, const Horaire& hf, const Duree& d){		//A vérifier

        if(nb==nbMax){
            nbMax +=10;
            Evt** tmp = new Evt*[nbMax];
            for(int i=0;i<nb;i++)
                tmp[i] = evt[i];
            Evt** old = evt;
            evt = tmp;
            delete[] old;
        }
<<<<<<< HEAD
        evt[nb++]=EvtFactory::NewEvt(desc,ptr,da,hd,hf,d);
=======
        evt[nb++]=EvtFactory::NewEvt(desc,ptr,da,h,d);
>>>>>>> 5433ea3f017db870657c4dfb1270cd47c79acf5e
   }
    EvtManager::Handler EvtManager::handler = EvtManager::Handler();

   // Evt* EvtManager::trouverEvt();	En a-t-on besoin ?
    EvtManager& EvtManager::getInstance(){
        if(handler.instance==0)
            handler.instance = new EvtManager;
        return *handler.instance;
    }

    void EvtManager::freeInstance(){
        if(handler.instance!=0)
            delete handler.instance;
        handler.instance=0;
    }

    EvtManager::IteratorSTL EvtManager::begin()const{
        return IteratorSTL(evt);
    }

    EvtManager::IteratorSTL EvtManager::end()const{
        return IteratorSTL(evt+nb);
    }
