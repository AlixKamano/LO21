#ifndef FENPRINCIPALE_H
#define FENPRINCIPALE_H
#include<QtWidgets>
#include<QString>
#include"projetManager.h"
#include"tacheajout.h"
#include"projetajout.h"
#include"treeview.h"
class FenetrePrincipale : public QWidget
{
    Q_OBJECT

public:
    FenetrePrincipale();

public slots:
    void ouvrirAfficher();
    void ouvrirAjoutP();
    void ouvrirAjoutT();

private:
    QPushButton* afficher;
    QPushButton* ajoutP;
    QPushButton* quitter;
    QPushButton* ajoutT;
};


#endif // FENPRINCIPALE_H