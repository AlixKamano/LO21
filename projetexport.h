#ifndef PROJETEXPORT_H
#define PROJETEXPORT_H
#include <QtWidgets>
#include "projetmanager.h"

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
    void exportProjet();
    void activerExport();
public:
    ProjetExport(QWidget* fenetre);
};


#endif // PROJETEXPORT_H

