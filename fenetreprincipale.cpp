#include "fenetreprincipale.h"
FenetrePrincipale::FenetrePrincipale() : QWidget(){
    QVBoxLayout *layoutp = new QVBoxLayout;

    /*QTableWidget table = new QTableWidget(12, 5, this);
    table->setHorizontalHeaderLabels(QStringList(QStringList()<<"Lundi"<<"Mardi"<<"Mercredi"<<"Jeudi"<<"Vendredi"<<"Samedi"<<"Dimanche"));
    table->setVerticalHeaderLabels(QStringList(QStringList()<<"0h-2h"<<"2h-4h"<<"4h-6h"<<"6h-8h"<<"8h-10h"<<"10h-12h"<<"12h-14h"<<"14h-16h"<<"16h-18h"<<"18h-20h"<<"20h-22h"<<"22h-24h"));
    QTableWidgetItem *newItem = new QTableWidgetItem("Miaou");
        table->setItem(2, 3, newItem);
    layoutp->addWidget(table);
    ProjetManager& pm = ProjetManager::getInstance();
    pm.ajouterProjet("P1","Creme au chocolat",Date(),Date());
    pm.ajouterProjet("P2","CHEESECAKE <3",Date(),Date());
    pm.ajouterProjet("P3","Creme au chocolat",Date(),Date());
    (*(pm.begin())).ajouterTache("unitaire","T1","Fondre Choco",Date(),Date());
    QTreeWidget *treeWidget = new QTreeWidget();


    AjouterArbre(treeWidget);

    layoutp->addWidget(treeWidget);*/
    afficher = new QPushButton("Afficher un tree-view", this);
    ajoutP = new QPushButton("Ajouter un Projet", this);
    ajoutT = new QPushButton("Ajouter une Tache", this);
    ajoutA = new QPushButton("Ajouter une Activité", this);
    quitter = new QPushButton("Quitter", this);
    QObject::connect(quitter, SIGNAL(clicked()),qApp, SLOT(quit()));
    QObject::connect(afficher, SIGNAL(clicked()), this, SLOT(ouvrirAfficher()));
    QObject::connect(ajoutP, SIGNAL(clicked()), this, SLOT(ouvrirAjoutP()));
    QObject::connect(ajoutA,SIGNAL(clicked()),this,SLOT(ouvrirAjoutA()));
    QObject::connect(ajoutT, SIGNAL(clicked()), this, SLOT(ouvrirAjoutT()));
    layoutp->addWidget(afficher);
    layoutp->addWidget(ajoutP);
    layoutp->addWidget(ajoutT);
    layoutp->addWidget(ajoutA);
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

void FenetrePrincipale::ouvrirAjoutA(){
ActiviteAjout* fenetreAjoutA = new ActiviteAjout(this);
fenetreAjoutA->exec();}
