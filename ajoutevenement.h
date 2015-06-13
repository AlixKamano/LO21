#ifndef AJOUTEVENEMENT_H
#define AJOUTEVENEMENT_H
#include<QtWidgets>
#include"evtManager.h"
#include "projetManager.h"
#include "actmanager.h"

class ajoutEvenement:public QDialog
{
    //! \class AjoutEvenement
    //! \brief Classe permettant d'afficher une fenêtre pour l'ajout d'un évènement : la programmation d'une activité ou d'une tâche
    Q_OBJECT
private:
    QHBoxLayout* classlayout, *listelayout,*timelayout,*dureelayout,*boutonlayout;
    QButtonGroup* evtclasse;
    QRadioButton *tacheevt, *activiteevt;
    QVBoxLayout *vLayout;
    QLabel *lliste, *lduree, *lhoraire, *ldate, *lpro;
    QComboBox* listeEle,*listePro;
    QSpinBox* hHoraire;
    QSpinBox* mHoraire, *mDuree;
    QDateEdit* date;
    QPushButton* annuler, *ajouter;

public:
    //! Constructeur d'AjoutEvenement
    ajoutEvenement(QWidget* fenetre);
    //!Fonction permettant d'afficher la liste des tâches unitaires en fonction d'un projet
    //! Pour cela, la fonction appelle l'itérateur de ProjetManager
    //! Puis nous affichons toutes les tâches de type Unitaire
    //! Si nous rencontrons une tâche composite, nous appelons  la fonction AfficheSousTacheU
    void afficheTacheU();
    //! Fonction permettant d'afficher la liste des activités enregistrées
    //! Nous appelons l'itérateur de la classe ActivitéManager
    //! Puis nous ajoutons toutes les activités non programmées à la liste déroulante
    void afficheActivite();
    //! Fonction permettant d'afficher la liste des sous-tâches unitaires d'une tâche composite
    //! \param TComposite& t : tâche composite dont il faut afficher les sous-têches
    //! La fonction appelle l'itérateur de la classe TComposite
    //! Nous affichons toutes les tâches unitaires rencontrées
    //! Si nous rencontrons à nouveau une sous-tâche composite, la fonction est appelée récursivement
    void afficheSousTacheU(const TComposite& t);
    //! Fonction permettant de contraindre l'ajout d'évènements
    //! \param QString s : ID de la tâche dont nous voulons vérifier les contraintes
    //! La fonction vérifie ici si la tâche est préemptive
    //! Les dates de disponibilité et d'échéance deviennent les dates minimum et maximum de l'évènement
    //! Ces dates ne peuvent pas être dépassées
    void contrainteTache(QString s);
    //! Fonction permettant de contraindre l'ajout d'activité
    //! Nous vérifions le respect de la date de disponibilité de l'activité
    void contrainteActivite();
    //! Fonction permettant de vérifier l'unicité d'un évènement
    //! \param QDate d : Date de l'évènement \param Horaire h1 : Horaire de début \param Horaire h2 : Horaire de fin
    //! Cette fonction appelle l'itérateur de la classe EvenementManager et vérifie qu'aucun évènement ne se chevauche
    bool verifUnique(QDate d, Horaire h1, Horaire h2);

/*private slots:
    void activerAjout();*/

public slots:
    void modifierSelection(bool b);
    void modifierContrainte(QString s);
    void modifierTache(int s);
    void ajouterEvenement();

};


#endif // AJOUTEVENEMENT_H
