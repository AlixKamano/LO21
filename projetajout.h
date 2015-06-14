#ifndef PROJETAJOUT_H
#define PROJETAJOUT_H
#include<QtWidgets>
#include"projetmanager.h"

class ProjetAjout: public QDialog
{
    Q_OBJECT
private:
    QVBoxLayout* vLayout;
    QHBoxLayout* idLayout;
    QHBoxLayout* titreLayout;
    QHBoxLayout* dispoLayout;
    QHBoxLayout* echeLayout;
    QHBoxLayout* boutonLayout;
    QLineEdit* id;
    QLineEdit* titre;
    QDateEdit* dispo;
    QDateEdit* echeance;
    QLabel *lid, *ltitre, *ldispo, *lecheance;
    QPushButton* annuler;
    QPushButton* ajouter;

public:
    ProjetAjout( QWidget* fenetre);

private slots:
    void activerAjout();
    void modifierDate(QDate mdate);

public slots:
    void ajoutProjet();

};
//

#endif // PROJETAJOUT_H
