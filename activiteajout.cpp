#include "activiteajout.h"
#include "actmanager.h"

ActiviteAjout::ActiviteAjout(QWidget *fenetre):QDialog(fenetre){
    setWindowTitle("Ajouter une activité");
    setFixedSize(400,150);

    h1Layout=new QHBoxLayout;
    lid=new QLabel("Identifiant",this);
    id=new QLineEdit(this);
    ltitre=new QLabel("Titre",this);
    titre=new QLineEdit(this);
    h1Layout->addWidget(lid);
    h1Layout->addWidget(id);
    h1Layout->addWidget(ltitre);
    h1Layout->addWidget(titre);

    h2Layout=new QHBoxLayout;
    lduree=new QLabel("Durée",this);
    heure =new QSpinBox(this);
    minute =new QSpinBox(this);
    heure->setSuffix(" heures(s)");
    minute->setSuffix(" minute(s)");
    heure->setMinimum(0);
    heure->setMaximum(23);
    minute->setMinimum(0);
    minute->setMaximum(59);
    h2Layout->addWidget(lduree);
    h2Layout->addWidget(heure);
    h2Layout->addWidget(minute);

    h3Layout = new QHBoxLayout;
    annuler=new QPushButton("Annuler", this);
    ajouter = new QPushButton("Ajouter l'activité", this);
    ajouter->setEnabled(false);
    h3Layout->addWidget(annuler);
    h3Layout->addWidget(ajouter);

    vLayout1 = new QVBoxLayout;
    vLayout1->addLayout(h1Layout);
    vLayout1->addLayout(h2Layout);
    vLayout1->addLayout(h3Layout);

    this->setLayout(vLayout1);
    QObject::connect(id,SIGNAL(textChanged(QString)),this,SLOT(activerAjout()));
    QObject::connect(titre,SIGNAL(textChanged(QString)),this,SLOT(activerAjout()));
    QObject::connect(heure,SIGNAL(valueChanged(int)),this,SLOT(activerAjout()));
    QObject::connect(minute,SIGNAL(valueChanged(int)),this,SLOT(activerAjout()));
    QObject::connect(annuler,SIGNAL(clicked()),this,SLOT(accept()));
    QObject::connect(ajouter,SIGNAL(clicked()),this,SLOT(ajouterActivite()));
}

void ActiviteAjout::activerAjout(){
    if(titre->text()!=0 && Duree(heure->value(),minute->value()).getDureeEnMinutes()!=0 && id->text()!=0)
        ajouter->setEnabled(true);      //Boutton ajouter
    else
        ajouter->setEnabled(false);
}

void ActiviteAjout::ajouterActivite(){
    ActiviteManager& am = ActiviteManager::getInstance();
    if (am.trouverActivite(id->text())){
        QMessageBox::critical(this,"Erreur","L'activité existe déjà !");
        return;
    }
    am.ajouterAct(id->text(),titre->text(),Duree(heure->value(),minute->value()));
    this->accept();
}
