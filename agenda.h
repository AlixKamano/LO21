#ifndef AGENDA_H
#define AGENDA_H
#include<QtWidgets>
#include"projetmanager.h"
#include "evtManager.h"
#include <vector>

class Agenda:public QDialog
{
    Q_OBJECT
private:
    vector<QPushButton*> boutons;
    QDate dateref;
    QPushButton* prec,* suiv,*exporter,*fermer;
    QHBoxLayout* hlayout,*boutonLayout;
    QVBoxLayout* vlayout1,*vlayout2,*vlayout3,*vlayout4,*vlayout5,*vlayout6,*vlayout7,*vlayout8;
    QVBoxLayout *case1,*case2,*case3,*case4,*case5,*case6,*case7;
    QLabel* ldate1, *ldate2,*ldate3,*ldate4,*ldate5,*ldate6,*ldate7;
public:
    Agenda(QWidget *fenetre);
    void AjouterJour(QDate d);
    void AjoutEvenement(const Evt& e);
    void saveSemaine(QString& f);
    void afficherSemaine();
    void setDateref(int i){dateref=dateref.addDays(i);}

public slots:
    void Precedent();
    void Suivant();
    void ExportSemaine();
};

#endif // AGENDA_H
