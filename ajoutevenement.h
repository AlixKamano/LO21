#ifndef AJOUTEVENEMENT_H
#define AJOUTEVENEMENT_H
#include<QtWidgets>
#include"evtManager.h"
#include "projetManager.h"
#include "actmanager.h"

class ajoutEvenement:public QDialog
{
    Q_OBJECT
private:
    QHBoxLayout* classlayout, *liste1layout,*liste2layout,*datelayout, *horlayout,*dureelayout,*boutonlayout;
    QButtonGroup* evtclasse;
    QRadioButton *tacheevt, *activiteevt;
    QVBoxLayout *vLayout;
    QLabel *lliste, *lduree, *lhoraire, *ldate, *lpro, *lclasse;
    QComboBox* listeEle,*listePro;
    QSpinBox* hHoraire;
    QSpinBox* mHoraire, *mDuree;
    QDateEdit* dateevt;
    QPushButton* annuler, *ajouter;

public:
    ajoutEvenement(QWidget* fenetre);
    void afficheTacheU();
    void afficheActivite();
    void afficheSousTacheU(const TComposite& t);
    void contrainteTache(QString s);
    void contrainteActivite(QString s);
    bool verifUnique(QDate d, Horaire h1, Horaire h2);

/*private slots:
    void activerAjout();*/

public slots:
    void modifierSelection(bool b);
    void modifierContrainte(QString s);
    void modifierTache();
    void ajouterEvenement();
    void activerAjout();

};


#endif // AJOUTEVENEMENT_H
