#ifndef __LO21_projet__tacheManager__
#define __LO21_projet__tacheManager__
#include <iostream>
#include <QString>
#include "tache.h"
#include "calendar.h"

class TacheManager {
	//Singleton
private:
    Tache** tab;
    int nb;
    int nbMax;
    void addItem(Tache* t);
    TacheManager(): nb(0), nbMax(0), tab(0){};
    TacheManager(const TacheManager& tm);
    ~TacheManager(){
        for (int i=0;i<nb;i++) delete tab[i];
        delete[] tab;
    };
    TacheManager& operator=(const TacheManager& tm);

    struct Handler{
        TacheManager *instance;
        Handler():instance(0){};
        ~Handler(){if(instance) delete instance;};
    };
    static Handler handler;

    class IteratorSTL{
    private:
        friend class TacheManager;
        Tache** currentTache;
        IteratorSTL(Tache** u): currentTache(u){};
    public:
        IteratorSTL operator++(){
            ++currentTache;
            return *this;
        };
        IteratorSTL operator--(){
            --currentTache;
            return *this;
        };
        bool operator!=(const IteratorSTL& it) const {return currentTache!= it.currentTache;}
        const Tache& operator*() const {return **currentTache;}
    };
    
public:
    void ajouterTache(const QString& id, const QString& t, const Date& dispo, const Date& deadline);
    Tache& getTache(const QString& id);
    const Tache& getTache(const QString& id) const;
    Tache *trouverTache(const QString& id) const;
    static TacheManager& getInstance();
    static void freeInstance();
    IteratorSTL begin();
    IteratorSTL end();
};


#endif /* defined(__LO21_projet__tacheManager__) */
