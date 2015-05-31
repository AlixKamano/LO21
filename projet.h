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

class Projet {
    private :
    string identificateur;
    string titre;
    Date dispo;
    Date echeance;
    Tache** taches;
    int nb;
    int nbMax;
    Projet(const string& id, const string& t, const Date& disponible, const Date& ech, int max=10) : identificateur(id), titre(t), dispo(disponible), echeance(ech), nbMax(max), nb(0), taches(new Tache*[max]){};
    Projet(const Projet& t);
    Projet& operator=(const Projet& t);
    friend class ProjetManager;
    public :
    string getId() const {return identificateur;};
    string getTitre() const {return titre;};
    Date getDispo()const{return dispo;};
    Date getEcheance()const{return echeance;};
    Tache** getTache()const{return taches;};
};

#endif
