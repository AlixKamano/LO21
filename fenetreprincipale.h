#ifndef FENPRINCIPALE_H
#define FENPRINCIPALE_H
#include<QtWidgets>
#include<QString>
#include"projetManager.h"
#include"tacheajout.h"
#include"projetajout.h"
#include"treeview.h"
#include"agenda.h"
#include"activiteajout.h"
#include"projetexport.h"
#include "ajoutevenement.h"

//! \class FenetrePrincipale
//! \brief Classe permettant d'afficher la fenêtre principale de l'application
class FenetrePrincipale : public QWidget
{
    Q_OBJECT

public:
    FenetrePrincipale();    //!< Constructeur de la fenêtre

public slots:
    //! Slot permettant d'ouvrir la fenêtre d'affichage du TreeView
    void ouvrirAfficher();
    //! Slot permettant d'ouvrir la fenêtre d'ajout de projet
    void ouvrirAjoutP();
    //! Slot permettant d'ouvrir la fenêtre d'ajout de tâches
    void ouvrirAjoutT();
    //! Slot permettant d'ouvrir la fenêtre d'affichage de l'agenda
    void ouvrirAgenda();
    //! Slot permettant d'ouvrir la fenêtre d'ajout d'activités
    void ouvrirAjoutA();
    //! Slot permettant d'ouvrir la fenêtre d'exportation de projets
    void Export();
    //! Slot permettant d'ouvrir la fenêtre d'ajout d'évènements
    void ouvrirAjoutEvt();

private:
    QPushButton* afficherTree;
    QPushButton* ajoutP;
    QPushButton* quitter;
    QPushButton* ajoutA;
    QPushButton* ajoutT;
    QPushButton* ajoutEvt;
    QPushButton* afficherAgenda;
    QPushButton* Exporter;
    QHBoxLayout* pLayout;
    QVBoxLayout* vLayout1, *vLayout2, *vLayout3;
    QGroupBox* ajoutBox, *afficheBox;
};


#endif // FENPRINCIPALE_H
