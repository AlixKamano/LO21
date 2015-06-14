//Pour commit !
#include "projetajout.h"

ProjetAjout::ProjetAjout(QWidget *fenetre): QDialog(fenetre)
{
    setWindowTitle("Ajouter un projet");
    setFixedSize(300,300);

    idLayout=new QHBoxLayout;
    lid=new QLabel("Idenetificateur", this);
    id = new QLineEdit(this);
    idLayout->addWidget(lid);
    idLayout->addWidget(id);

    titreLayout=new QHBoxLayout;
    ltitre=new QLabel("Titre", this);
    titre=new QLineEdit;
    titreLayout->addWidget(ltitre);
    titreLayout->addWidget(titre);

    dispoLayout=new QHBoxLayout;
    ldispo = new QLabel("Disponibilité", this);
    dispo = new QDateEdit(QDate::currentDate(),this);
    dispoLayout->addWidget(ldispo);
    dispoLayout->addWidget(dispo);

    echeLayout=new QHBoxLayout;
    lecheance = new QLabel("Echéance", this);
    echeance = new QDateEdit(QDate::currentDate().addDays(1),this);
    echeLayout->addWidget(lecheance);
    echeLayout->addWidget(echeance);

    boutonLayout = new QHBoxLayout;
    annuler=new QPushButton("Annuler", this);
    ajouter = new QPushButton("Ajouter le projet", this);
    ajouter->setEnabled(false);
    boutonLayout->addWidget(annuler);
    boutonLayout->addWidget(ajouter);

    vLayout = new QVBoxLayout;
    vLayout->addLayout(idLayout);
    vLayout->addLayout(titreLayout);
    vLayout->addLayout(dispoLayout);
    vLayout->addLayout(echeLayout);
    vLayout->addLayout(boutonLayout);
    this->setLayout(vLayout);

    dispo->setMinimumDate(QDate::currentDate());
    dispo->setMaximumDate(echeance->date().addDays(-1));
    echeance->setMinimumDate(QDate::currentDate().addDays(1));

    QObject::connect(id, SIGNAL(textChanged(QString)),this, SLOT(activerAjout()));
    QObject::connect(titre, SIGNAL(textChanged(QString)),this, SLOT(activerAjout()));
    QObject::connect(echeance, SIGNAL(dateChanged(QDate)),this,SLOT(modifierDate(QDate)));
    QObject::connect(annuler, SIGNAL(clicked()),this, SLOT(accept()));
    QObject::connect(ajouter, SIGNAL(clicked()),this, SLOT(ajoutProjet()));
}



void ProjetAjout::modifierDate(QDate mdate){
    dispo->setMaximumDate(mdate.addDays(-1));
}


void ProjetAjout::activerAjout(){
    if(titre->text()!=0  && id->text()!=0)
        ajouter->setEnabled(true);      //Boutton ajouter
    else
        ajouter->setEnabled(false);
}

void ProjetAjout::ajoutProjet(){
    ProjetManager& pm = ProjetManager::getInstance();
    if (pm.trouverProjet(id->text())){
        QMessageBox::critical(this,"Erreur","Ce projet existe déjà  !");
        return;
    }
    pm.ajouterProjet(id->text(), titre->text(), dispo->date(), echeance->date(), 5);
    this->accept();
}
