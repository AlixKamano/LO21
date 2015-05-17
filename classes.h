class Tache {
	private :
		string titre;
		Tache** precedence;
		Date dispo;
		Date echeance;
	public : 
		string getTitre() const {return titre;};
		Tache** getPrecedence() const{return precedence;};
		Date getDispo()const{return dispo;};
		Date getEcheance()const{return echeance;};
};

class TacheManager {
	//Singleton
	private :
		Tache** tab;
		int nb;
		int nbMax; 
		static ? instance;
	public : 
		static getInstance();
		static freeInstance();
};


class TUnitaire : public Tache{
	private :
		bool preemptive;
		Duree duree;
	public :
		bool getPremptive()const{return preemptive;};
		Duree getDuree()const{return duree;};
};

class TComposite : public Tache{
	private :
		Tache** sousTaches;
		int nb;
		int nbMax; 
	public :
		Tache** getSousTaches()const {return sousTaches;};
};

class Activite {
	private : 
		string titre;
		Duree duree;
	public : 
	string getTitre()const{return titre;};
	Duree getDuree()const {return duree};
};

class EvtTache {
	private : 
		Duree duree;
		Tache* tache;
	public : 
		Duree getDuree()const{return duree;};
		Tache* getTache()const{return tache;};
};

class EvtActivite {
	private : 
		Activite* activite;
	public : 
		Activite* getActivite()const{return activite;};
};

class Programmation {
	private :
		Date date;
		Horaire horaire;
	public : 
		Date getDate()const{return date;};
		Horaire getHoraire()const{return horaire;};
};

class ProgrammationManager {
	//Singleton
	private :
		Programmation** prog;
		int nb;
		int nbMax; 
	public : 
		Programmation** getProg()const{return prog;};
};

class Projet {
	private :
		Date dispo;
		Date echeance;
		Tache** taches;
		int nb;
		int nbMax;
	public :
		Date getDispo()const{return dispo;};
		Date getEcheance()const{return echeance;};
		Tache** getTache()const{return taches;};
};

class ProjetManager {
	//Singleton
	private :
		Projet** projet;
		int nb;
		int nbMax; 
	public : 
};