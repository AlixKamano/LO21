#include "calendar.h"

EvtTache* EvtTache::reprogrammer(const Date& da, const Horaire& h, const Duree& d){
	if(tache.getStatut()!=0)
		tache.setStatut(0);
	duree = d;
	Prog::setDate(da);
	Prog::setHoraire(h);
	return *this;
}

EvtActivite* EvtActivite::reprogrammer(const Date& da, const Horaire& h){
	Prog::setDate(da);
	Prog::setHoraire(h)
	return *this;
}
