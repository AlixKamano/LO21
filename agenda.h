#ifndef AGENDA_H
#define AGENDA_H
#include<QtWidgets>
#include"projetmanager.h"
#include "evtManager.h"

class Agenda:public QDialog
{
    Q_OBJECT
private:
    QDate date;
    QPushButton* prec,* suiv;
    QHBoxLayout* hlayout, *hlayout1,*hlayout2,*hlayout3;
    QVBoxLayout* vlayout1;
    QLabel* ldate1, *ldate2,*ldate3,*ldate4,*ldate5,*ldate6,*ldate7;
public:
    Agenda(QWidget *fenetre);
    void AjouterJour(QDate d);
    void AjoutEvenement(Evt& e);

public slots:
    void Precedent();
    void Suivant();
};

//void AjouterJour(QDate d);
#endif // AGENDA_H
