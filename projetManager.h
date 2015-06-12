#ifndef PROJETMANAGER_H
#define PROJETMANAGER_H

#include <iostream>
#include "projet.h"

class ProjetManager {
    //Singleton
    //
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
    void ajouterProjet(const QString& id, const QString& t, const QDate& dispo, const QDate& deadline, int max);
    Projet& getProjet(const QString& id);
    const Projet& getProjet(const QString& id) const;
    Projet *trouverProjet(const QString& id) const;
    static ProjetManager& getInstance();
    static void freeInstance();
    IteratorSTL begin();
    IteratorSTL end();
};

#endif // PROJETMANAGER_H

