#ifndef PROJETAJOUT_H
#define PROJETAJOUT_H
#include<QtWidgets>
#include"projetmanager.h"

class ProjetAjout: public QDialog
{
    Q_OBJECT
private:
    QVBoxLayout* vLayout;
    QHBoxLayout* h1Layout;
    QHBoxLayout* h2Layout;
    QHBoxLayout* h3Layout;
    QHBoxLayout* h4Layout;
    QLineEdit* id;
    QTextEdit* titre;
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
