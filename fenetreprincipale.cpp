#include "fenetreprincipale.h"
FenetrePrincipale::FenetrePrincipale() : QWidget(){
    setWindowTitle("Gestionnaire de tâche");
    setFixedSize(400,220);


    ajoutP = new QPushButton("Ajouter un projet", this);
    ajoutT = new QPushButton("Ajouter une tâche", this);
    ajoutA = new QPushButton("Ajouter une activité", this);
    ajoutEvt = new QPushButton("Ajouter un événement", this);
    vLayout1 = new QVBoxLayout;
    vLayout1->addWidget(ajoutP);
    vLayout1->addWidget(ajoutT);
    vLayout1->addWidget(ajoutA);
    vLayout1->addWidget(ajoutEvt);
    ajoutBox = new QGroupBox("Ajout",this);
    ajoutBox->setLayout(vLayout1);


    afficherTree = new QPushButton("Tree-view", this);
    afficherAgenda = new QPushButton("Agenda", this);
    vLayout2 = new QVBoxLayout;
    vLayout2->addWidget(afficherTree);
    vLayout2->addWidget(afficherAgenda);
    afficheBox = new QGroupBox("Affichage",this);
    afficheBox->setLayout(vLayout2);

    Exporter = new QPushButton("Exporter un projet",this);
    quitter = new QPushButton("Quitter", this);
    vLayout3 = new QVBoxLayout;
    vLayout3->addWidget(afficheBox);
    vLayout3->addWidget(Exporter);
    vLayout3->addWidget(quitter);

    pLayout = new QHBoxLayout;
    pLayout->addWidget(ajoutBox);
    pLayout->addLayout(vLayout3);
    this->setLayout(pLayout);

    QObject::connect(quitter, SIGNAL(clicked()),qApp, SLOT(quit()));
    QObject::connect(afficherTree, SIGNAL(clicked()), this, SLOT(ouvrirAfficher()));
    QObject::connect(ajoutP, SIGNAL(clicked()), this, SLOT(ouvrirAjoutP()));
    QObject::connect(ajoutA,SIGNAL(clicked()),this,SLOT(ouvrirAjoutA()));
    QObject::connect(ajoutT, SIGNAL(clicked()), this, SLOT(ouvrirAjoutT()));
    QObject::connect(afficherAgenda, SIGNAL(clicked()), this, SLOT(ouvrirAgenda()));
    QObject::connect(Exporter,SIGNAL(clicked()),this,SLOT(Export()));
    QObject::connect(ajoutEvt, SIGNAL(clicked()), this, SLOT(ouvrirAjoutEvt()));
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

void FenetrePrincipale::ouvrirAjoutA(){
ActiviteAjout* fenetreAjoutA = new ActiviteAjout(this);
fenetreAjoutA->exec();}

void FenetrePrincipale::Export(){
    ProjetExport* fenetrePExport = new ProjetExport(this);
    fenetrePExport->exec();
}

void FenetrePrincipale::ouvrirAjoutEvt(){
ajoutEvenement* fenetreAjoutEvt = new ajoutEvenement(this);
fenetreAjoutEvt->exec();}

