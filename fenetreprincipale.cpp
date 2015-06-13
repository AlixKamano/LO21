#include "fenetreprincipale.h"
FenetrePrincipale::FenetrePrincipale() : QWidget(){
    QVBoxLayout *layoutp = new QVBoxLayout;
    afficher = new QPushButton("Afficher un tree-view", this);
    ajoutP = new QPushButton("Ajouter un Projet", this);
    ajoutT = new QPushButton("Ajouter une Tache", this);
    afficherAgenda = new QPushButton("Agenda", this);
    quitter = new QPushButton("Quitter", this);
    QObject::connect(quitter, SIGNAL(clicked()),qApp, SLOT(quit()));
    QObject::connect(afficher, SIGNAL(clicked()), this, SLOT(ouvrirAfficher()));
    QObject::connect(ajoutP, SIGNAL(clicked()), this, SLOT(ouvrirAjoutP()));
    QObject::connect(ajoutT, SIGNAL(clicked()), this, SLOT(ouvrirAjoutT()));
    QObject::connect(afficherAgenda, SIGNAL(clicked()), this, SLOT(ouvrirAgenda()));
    layoutp->addWidget(afficher);
    layoutp->addWidget(ajoutP);
    layoutp->addWidget(ajoutT);
    layoutp->addWidget(afficherAgenda);
    layoutp->addWidget(quitter);
    setLayout(layoutp);
}

void FenetrePrincipale::ouvrirAfficher(){
treeView* fenetreTree = new treeView(this);
fenetreTree->exec();}

void FenetrePrincipale::ouvrirAjoutP(){
ProjetAjout* fenetreAjoutP = new ProjetAjout(this);
fenetreAjoutP->exec();}

void FenetrePrincipale::ouvrirAjoutT(){
TacheAjout* fenetreAjoutT = new TacheAjout(this);
fenetreAjoutT->exec();}

void FenetrePrincipale::ouvrirAgenda(){
Agenda* fenetreAgenda = new Agenda(this);
fenetreAgenda->exec();}
