#ifndef PROJETAJOUT_H
#define PROJETAJOUT_H
#include<QtWidgets>
#include"projetmanager.h"

//! \class ProjetAjout
//! \brief Classe permettant d'afficher la fenêtre d'ajout de projet
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
    //! Constructeur de la fenêtre
    ProjetAjout( QWidget* fenetre);

private slots:
    //! Slot permettant d'activer le bouton "Ajouter" si les champs de titre et Id sont remplis
    void activerAjout();
    //! Slot permettant de modifier la date maximum de disponibilité du projet en fonction de la date d'échéance
    void modifierDate(QDate mdate);

public slots:
    //! Slot permettant d'ajouter le projet à ProjetManager après avoir vérifié que le projet n'existait pas déjà
    void ajoutProjet();

};
//

#endif // PROJETAJOUT_H
