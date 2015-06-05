#ifndef LO21_projet_progManager_h
#define LO21_projet_progManager_h


#include "calendar.h"

class ProgManager {
	//Singleton
private:
    Prog** prog;
    int nb;
    int nbMax;
    ProgManager():nb(0), nbMax(0),pog(0){};
    ProgManager(const ProgManager& pm);
    ~ProgManager(){
    	for(int i = 0; i<nb;i++) delete prog[i];
    	delete[] prog;
    };
    ProgManager& operator=(const ProgManager& pm);

    struct Handler{
    	ProgManager* instance;
    	Handler():instance(0){};
    	~Handler(){if(instance) delete instance;};
    };
    static Handler handler;

    class IteratorSTL{
    	private:
    		friend class ProgManager;
    		Prog** currentProg;
    		IteratorSTL(Prog** p):currentProg(p){};
    	public:
    		IteratorSTL operator++(){
    			++currentProg;
    			return *this;
    		};
    		IteratorSTL operator--(){
    			--currentProg;
    			return *this;
    		};
    		bool operator!=(const IteratorSTL& it) const {return currentProg!=.it.currentProg;};
    		const Prog& operator*() const{return **currentProg};
    };
public:
    void ajouterProg(const Date& d, const Horaire& h);  //Poblème

    Prog** getProg()const{return prog;};
    const Prog* getProg()const{return prog;};
   // Prog* trouverProg();	En a-t-on besoin ? 
    static ProgManager& getInstance();
    static void freeInstance();	
    IteratorSTL begin()const;
    IteratorSTL end()const;	
};

#endif