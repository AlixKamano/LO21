#ifndef ACTIVITEAJOUT_H
#define ACTIVITEAJOUT_H
#include <QtWidgets>
#include "actmanager.h"

class ActiviteAjout : public QDialog{
    //! \class ActivitéAjout
    //! \brief class permettant de gérer la fenêtre d'ajout des activités
    Q_OBJECT
private:
    QHBoxLayout* h1Layout, *h2Layout, *h3Layout;    //!< Layout horizontaux
    QVBoxLayout* vLayout1;                          //!< Layout vertical
    QLabel* ltitre, *lduree, *lid;                  //!< Labels
    QLineEdit* titre, *id;                          //!< Champs de texte
    QSpinBox* heure;                //!< SpinBox correspondant à l'heure de l'horaire
    QSpinBox* minute;               //!< SpinBox correspondant à la minute de l'horaire
    QPushButton* annuler;           //!< Bouton retour
    QPushButton* ajouter;           //!< Bouton ajout
private slots:
    void activerAjout();            //!< Slot autorisant l'ajout de l'activité
public slots:
    void ajouterActivite();         //!< Slot pour l'ajout d'une activité
public:
    ActiviteAjout(QWidget* fenetre);    //!< Fenêtre d'ajout
};

#endif // ACTIVITEAJOUT_H

