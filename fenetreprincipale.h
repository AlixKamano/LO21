#ifndef FENPRINCIPALE_H
#define FENPRINCIPALE_H
#include<QtWidgets>
#include<QString>
#include"projetManager.h"
#include"tacheajout.h"
#include"projetajout.h"
#include"treeview.h"
<<<<<<< HEAD
#include"agenda.h"
=======
#include"activiteajout.h"
>>>>>>> 5c2cc245a30c417039aa7e583883766be910a42f
class FenetrePrincipale : public QWidget
{
    Q_OBJECT

public:
    FenetrePrincipale();

public slots:
    void ouvrirAfficher();
    void ouvrirAjoutP();
    void ouvrirAjoutT();
<<<<<<< HEAD
    void ouvrirAgenda();
=======
    void ouvrirAjoutA();
>>>>>>> 5c2cc245a30c417039aa7e583883766be910a42f

private:
    QPushButton* afficher;
    QPushButton* ajoutP;
    QPushButton* quitter;
    QPushButton* ajoutA;
    QPushButton* ajoutT;
    QPushButton* afficherAgenda;
};


#endif // FENPRINCIPALE_H
