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
    QDate date;
    QPushButton* prec,* suiv;
    QHBoxLayout* hlayout;
    QVBoxLayout* vlayout1,*vlayout2,*vlayout3,*vlayout4,*vlayout5,*vlayout6,*vlayout7;
    QVBoxLayout *case1,*case2,*case3,*case4,*case5,*case6,*case7;
    QLabel* ldate1, *ldate2,*ldate3,*ldate4,*ldate5,*ldate6,*ldate7;
public:
    Agenda(QWidget *fenetre);
    void AjouterJour(QDate d);
    void AjoutEvenement(Evt& e);

public slots:
    void Precedent();
    void Suivant();
};

void AjouterJour(QDate d);
#endif // AGENDA_H
