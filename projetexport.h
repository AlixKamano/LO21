#ifndef PROJETEXPORT_H
#define PROJETEXPORT_H
#include <QtWidgets>
#include "projetmanager.h"

//! \class ProjetExport
//! \brief Classe permettant d'afficher la fenêtre d'export de projet
class ProjetExport : public QDialog{
    Q_OBJECT
private:
    QHBoxLayout* h1Layout, *h2Layout;
    QVBoxLayout* vLayout;
    QLabel* lprojet;
    QComboBox* listeProjet;
    QPushButton* exporter;
    QPushButton* annuler;

public slots :
    //! Slot permettant d'appeler la fonction save du projet sélectionné dans la liste déroulante
    void exportProjet();
    //! Slot permettant d'activer le bouton "Exporter" si un projet est sélectionné dans la liste déroulante
    void activerExport();
public:
    //! Constructeur de la fenêtre ProjetExport
    ProjetExport(QWidget* fenetre);
};


#endif // PROJETEXPORT_H

