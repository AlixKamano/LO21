//Pour commit !
#include "projetajout.h"

ProjetAjout::ProjetAjout(QWidget *fenetre): QDialog(fenetre)
{
    setWindowTitle("Ajout Tache");
    setFixedSize(600,300);

    h1Layout=new QHBoxLayout;
    lid=new QLabel("idenetificateur", this);
    id = new QLineEdit(this);
    h1Layout->addWidget(lid);
    h1Layout->addWidget(id);

    h2Layout=new QHBoxLayout;
    ltitre=new QLabel("Titre", this);
    titre=new QTextEdit("Titre exemple",this);
    h2Layout->addWidget(ltitre);
    h2Layout->addWidget(titre);

    h3Layout=new QHBoxLayout;
    ldispo = new QLabel("Disponibilité", this);
    lecheance = new QLabel("Echéance", this);
    dispo = new QDateEdit(QDate::currentDate(),this);
    echeance = new QDateEdit(QDate::currentDate(),this);
    dispo->setMaximumDate(echeance->date());
    h3Layout->addWidget(ldispo);
    h3Layout->addWidget(dispo);
    h3Layout->addWidget(lecheance);
    h3Layout->addWidget(echeance);

    h4Layout = new QHBoxLayout;
    annuler=new QPushButton("Annuler", this);
    ajouter = new QPushButton("Ajouter", this);
    ajouter->setEnabled(false);
    h4Layout->addWidget(annuler);
    h4Layout->addWidget(ajouter);

    vLayout = new QVBoxLayout;
    vLayout->addLayout(h1Layout);
    vLayout->addLayout(h2Layout);
    vLayout->addLayout(h3Layout);
    vLayout->addLayout(h4Layout);
    this->setLayout(vLayout);
    QObject::connect(id, SIGNAL(textChanged(QString)),this, SLOT(activerAjout()));
    QObject::connect(echeance, SIGNAL(dateChanged(QDate)),this,SLOT(modifierDate(QDate)));
    QObject::connect(annuler, SIGNAL(clicked()),this, SLOT(accept()));
    QObject::connect(ajouter, SIGNAL(clicked()),this, SLOT(ajoutProjet()));
}



void ProjetAjout::modifierDate(QDate mdate){
    dispo->setMaximumDate(mdate);
}

void ProjetAjout::activerAjout(){
    if (id->text()!=0)
        ajouter->setEnabled(true);
    if(id->text()==0)
        ajouter->setEnabled(false);
}

void ProjetAjout::ajoutProjet(){
    ProjetManager& pm = ProjetManager::getInstance();
    if (pm.trouverProjet(id->text())){
        QMessageBox::critical(this,"Erreur","Ce projet existe déjà  !");
        return;
    }
    pm.ajouterProjet(id->text(), titre->toPlainText(), dispo->date(), echeance->date(), 5);
    this->accept();
}
