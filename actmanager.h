#ifndef ACTMANAGER_H
#define ACTMANAGER_H
#include "activite.h"

class ActiviteManager{
    Activite** activites;
    int nb;
    int nbMax;
    ActiviteManager():nb(0),nbMax(0),activites(0){}
    ActiviteManager(const ActiviteManager& am);
    ~ActiviteManager(){
        for(int i=0;i<nb;i++) delete activites[i];
        delete[] activites;
    }
    ActiviteManager& operator=(const ActiviteManager& am);

    struct Handler{
        ActiviteManager* instance;
        Handler():instance(0){}
        ~Handler(){if(instance) delete instance;}
    };
    static Handler handler;
public:
    class IteratorSTL{
    private:
        friend class ActiviteManager;
        Activite** currentAct;
        IteratorSTL(Activite** a):currentAct(a){}
    public:
        IteratorSTL operator++(){
            ++currentAct;
            return *this;
        }
        bool operator!=(const IteratorSTL& it)const{
            return currentAct!=it.currentAct;
        }
        const Activite& operator*()const{return **currentAct;}
    };
    void ajouterAct(const QString& t, const Duree d);
    Activite** getAct(){return activites;}
    static ActiviteManager& getInstance();
    static void freeInstance();
    IteratorSTL begin()const;
    IteratorSTL end()const;
};

#endif // ACTMANAGER_H

