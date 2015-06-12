#ifndef TACHEAJOUT_H
#define TACHEAJOUT_H
#include<QtWidgets>
#include"projetmanager.h"
//
class TacheAjout:public QDialog
{
    Q_OBJECT
private:
    QVBoxLayout* vLayout1, * vLayout2;
    QHBoxLayout* classlayout, *gLayout, *projLayout;
    QComboBox* listeProjet, *listeTacheC;
    QHBoxLayout* h1Layout;
    QHBoxLayout* h2Layout;
    QHBoxLayout* h3Layout;
    QHBoxLayout* h4Layout;
    QLineEdit* id;
    QTextEdit* titre;
    QSpinBox* heure;
    QSpinBox* minute;
    QDateEdit* dispo;
    QDateEdit* echeance;
    QLabel *lid, *ltitre, *ldispo, *lecheance, *lduree, *lprojet, *ltacheC;
    QCheckBox* preemptive;
    QPushButton* annuler;
    QPushButton* ajouter;
    QButtonGroup* classe;
    QRadioButton* unitaire, *composite;
    QGroupBox* groupe;

private slots:
    void modifierDate(QDate mdate);
    void activerAjout();

public slots:
    void ajoutTache();
    void afficheTacheC(QString s);

public:
    TacheAjout(QWidget* fenetre);

};


#endif // TACHEAJOUT_H
