#ifndef TACHEAJOUT_H
#define TACHEAJOUT_H

#include<QtWidgets>
#include"projetmanager.h"

//! \class TacheAjout
//! \brief Classe permettant d'afficher la fenêtre d'ajout de tâches
class TacheAjout:public QDialog
{
    Q_OBJECT
private:
    QVBoxLayout* vLayout1, * vLayout2;
    QHBoxLayout* classlayout, *gLayout, *projLayout;
    QComboBox* listeProjet, *listeTacheC,*listeTacheP;
    QHBoxLayout* h1Layout;
    QHBoxLayout* h2Layout;
    QHBoxLayout* h3Layout;
    QHBoxLayout* h4Layout;
    QLineEdit* id;
    QLineEdit* titre;
    QSpinBox* heure;
    QSpinBox* minute;
    QDateEdit* dispo;
    QDateEdit* echeance;
    QLabel *lid, *ltitre, *ldispo, *lecheance, *lduree, *lprojet, *ltacheC, *ltacheP, *ltache;
    QCheckBox* preemptive;
    QPushButton* annuler;
    QPushButton* ajouter;
    QButtonGroup* classe;
    QRadioButton* unitaire, *composite;
    QGroupBox* groupe;

private slots:
    //! Slot permettant de modifier la date maximum de disponibilité en fonction de la date passée en argument
    void modifierDate(QDate mdate);
    //! Slot permettant d'activer le bouton Ajouter si toutes les contraintes sont respectées
    void activerAjout();
    //! Fonction permettant de limiter les dates de disponibilité et d'échéance de la tâche par celles du projet
    void changeDate(QString t);

public slots:
    //! Slot  permmettant d'ajouter la tâche au projet
    void ajoutTache();
    //! Slot permettant d'afficher la liste des tâches composites du projet
    void afficheTacheC(QString s);
    //! Slot permettant d'afficher la liste des tâches du projet pour pouvoir préciser une précédence
    void afficheTacheP(QString s);
    //! Fonction permettant d'afficher des  sous-tâches composites
    void afficheSousTacheC(const TComposite &t);
    //! Fonction permettant de modifier la durée de la tâche selon si elle est préemptive ou non
    void modifierDuree(bool b);

public:
    //! Constructeur de TacheAjout
    TacheAjout(QWidget* fenetre);

};


#endif // TACHEAJOUT_H
