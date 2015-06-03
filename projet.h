#ifndef __LO21_projet__projet__
#define __LO21_projet__projet__

#include <iostream>
#include"tacheManager.h"

class ProjetException{
public:
    ProjetException(const string& message):info(message){}
    string getInfo() const { return info; }
private:
    string info;
};


//Statut = 0 => Projet non programmé, à venir
class Projet {
    private:
        int statut;
        int identificateur;
        string titre;
        Date dispo;
        Date echeance;
        Tache** taches;
        int nb;
        int nbMax;
        Projet(const int id, const string& t, const Date& disponible, const Date& ech, int max=10) : statut(0),identificateur(id), titre(t), dispo(disponible), echeance(ech), nbMax(max), nb(0), taches(new Tache*[max]){};
        Projet(const Projet& t);
        Projet& operator=(const Projet& t);
        friend class ProjetManager;
    public:
        string getId() const {return identificateur;};
        string getTitre() const {return titre;};
        Date getDispo()const{return dispo;};
        Date getEcheance()const{return echeance;};
        Tache** getTache()const{return taches;};
};

#endif
