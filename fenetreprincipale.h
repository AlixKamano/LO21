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

class FenetrePrincipale : public QWidget
{
    Q_OBJECT

public:
    FenetrePrincipale();

public slots:
    void ouvrirAfficher();
    void ouvrirAjoutP();
    void ouvrirAjoutT();
    void ouvrirAgenda();
    void ouvrirAjoutA();
    void Export();

private:
    QPushButton* afficher;
    QPushButton* ajoutP;
    QPushButton* quitter;
    QPushButton* ajoutA;
    QPushButton* ajoutT;
    QPushButton* afficherAgenda;
    QPushButton* Exporter;
};


#endif // FENPRINCIPALE_H
