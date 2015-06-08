#include "evtManager.h"

//Méthodes de evtManager
   void EvtManager::ajouterEvt(const Date& d, const Horaire& h){		//A vérifier
   		if(nb==nbMax){
   			nbMax +=10;
   			Evt** tmp = new Evt*[nbMax];
   			for(int i=0;i<nb;i++)
   				tmp[i] = evt[i];
   			Evt** old = evt;
   			evt = tmp;
   			delete[] old;
   		}
        //evt[nb++]=Evt(d,h); Evt doit retourner un pointeur
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
