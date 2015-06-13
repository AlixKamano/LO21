#ifndef ACTIVITEAJOUT_H
#define ACTIVITEAJOUT_H
#include <QtWidgets>
#include "actmanager.h"

class ActiviteAjout : public QDialog{
    Q_OBJECT
private:
    QHBoxLayout* h1Layout, *h2Layout, *h3Layout;
    QVBoxLayout* vLayout1;
    QLabel* ltitre, *lduree, *lid;
    QLineEdit* titre, *id;
    QSpinBox* heure;
    QSpinBox* minute;
    QPushButton* annuler;
    QPushButton* ajouter;
private slots:
    void activerAjout();
public slots:
    void ajouterActivite();
public:
    ActiviteAjout(QWidget* fenetre);
};

#endif // ACTIVITEAJOUT_H

