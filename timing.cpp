#include <iomanip>
#include "timing.h"
#include <ctime>

using namespace TIME;

bool Horaire::operator<(const Horaire& h) const{
    if (heure<h.heure) return true;
    if (heure>h.heure) return false;
    if (minute<h.minute) return true;
    if (minute>h.minute) return false;
    return true;
}

Periode::Periode(unsigned int j, unsigned int m, unsigned int a):
           nb_jours(j), nb_mois(m), nb_annees(a) {
    if (j>364) throw TimeException("erreur: initialisation periode invalide");
    if (m>11) throw TimeException("erreur: initialisation periode invalide");
}


std::ostream& operator<<(std::ostream& f, const Intervalle& x){ x.afficher(f); return f;}
std::ostream& operator<<(std::ostream& f, const QDate& d){ return f;}

Intervalle::Intervalle(const QDate &d, const QDate &f):debut(d),fin(f){
    if (fin<debut) throw TimeException("Erreur dans la creation d'un intervalle: fin<debut");
}

bool Intervalle::operator&&(const Intervalle & v) const {
    if (debut<v.debut){
        if (fin<v.debut) return false; else return true;
    }
    if (v.fin<fin){
        if (v.fin<debut) return false; else return true;
    }
    return true;
}

Intervalle Intervalle::operator+(const Intervalle & i) const {
    QDate d=fin.addDays(1);
    if (d==i.debut){
        return Intervalle(debut,i.fin);
    }else throw TimeException("Ne peut pas faire l'union de 2 intervalles (ils ne se touchent pas...)");
}

void Intervalle::afficher(std::ostream& f) const {
    f<<"["<<debut<<" ; "<<fin<<"]";
}

std::istream& operator>>(std::istream& flot, QDate& date){
    unsigned int short j,m,a;
    bool ok=true;
    flot>>j;
    if (flot) while (flot.peek()==' ') flot.ignore(); // passe les espaces
    else ok=false;

    if (!flot) ok=false;

    if(flot.peek()=='/') {
        flot.ignore();
        flot>>m;
        if (!flot) ok=false;
    }
    else {
        ok=false;
    }
    if(flot.peek()=='/') {
        flot.ignore();
        flot>>a;
        if (!flot) ok=false;
    }
    else {
        ok=false;
    }

    if (ok) date=QDate(j,m,a); else flot.clear(std::ios::failbit);  //Vérifier si ça fonctionne
    return flot;
}

std::istream& operator>>(std::istream& flot, TIME::Duree& duree){
    unsigned int h,m;
    bool ok=true;
    flot>>h;
    if (flot) while (flot.peek()==' ') flot.ignore(); // passe les espaces
    else ok=false;

    if (!flot) ok=false;

    if(flot.peek()=='H') {
        flot.ignore();
        flot>>m;
        if (!flot) ok=false;
    }
    else {
        ok=false;
    }
    if (ok) duree=Duree(h,m); else flot.clear(std::ios::failbit);
    return flot;
}
