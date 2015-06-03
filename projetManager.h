#ifndef __LO21_projet__projetManager__
#define __LO21_projet__projetManager__

#include <iostream>
#include "projet.h"
class ProjetManager {
	//Singleton
private:
    Projet** projets;
    int nb;
    int nbMax;
    void addItem(Projet* p);
    ProjetManager(): nb(0), nbMax(0), projets(0){};
    ProjetManager(const ProjetManager& pm);
    ~ProjetManager(){
        for (int i=0;i<nb;i++) delete projets[i];
        delete[] projets;
    };
    ProjetManager& operator=(const ProjetManager& pm);
    struct Handler{
        ProjetManager *instance;
        Handler():instance(0){};
        ~Handler(){if(instance) delete instance;};
    };
    //Constructeur de recopie
    ProjetManager& (const ProjetManager& pm);
    static Handler handler;

    class IteratorSTL{
    private:
        friend class ProjetManager;
        Projet** currentProjet;
        IteratorSTL(Projet** p): currentProjet(p){};
    public:
        IteratorSTL operator++(){
            ++currentProjet;
            return *this;
        };
        IteratorSTL operator--(){
            --currentProjet;
            return *this;
        };
        bool operator!=(const IteratorSTL& it) const {return currentProjet!= it.currentProjet;}
        const Projet& operator*() const {return **currentProjet;}
    };
    
public:
    void ajouterProjet(const string& id, const string& t, const Date& dispo, const Date& deadline, int max);
    Projet& getProjet(const string& id);
    const Projet& getProjet(const string& id) const;
    Projet *trouverProjet(const string& id) const;
    static ProjetManager& getInstance();
    static void freeInstance();
    IteratorSTL begin();
    IteratorSTL end();
};

#endif
