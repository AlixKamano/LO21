#include "tacheajout.h"
//
TacheAjout::TacheAjout(QWidget *fenetre) : QDialog(fenetre)
{
    setWindowTitle("Ajouter une tache");
    setFixedSize(630,280);

    classlayout=new QHBoxLayout;
    classe = new QButtonGroup;
    ltache = new QLabel("Tache:",this);
    unitaire = new QRadioButton("Unitaire");
    composite = new QRadioButton("Composite");
    classe->addButton(unitaire);
    unitaire->setChecked(true);
    classe->addButton(composite);
    classlayout->addWidget(ltache);
    classlayout->addWidget(unitaire);
    classlayout->addWidget(composite);

    h1Layout=new QHBoxLayout;
    lid=new QLabel("Identifiant", this);
    id = new QLineEdit(this);
    h1Layout->addWidget(lid);
    h1Layout->addWidget(id);

    h2Layout=new QHBoxLayout;
    ltitre=new QLabel("Titre", this);
    titre=new QLineEdit(this);
    h2Layout->addWidget(ltitre);
    h2Layout->addWidget(titre);

    h3Layout=new QHBoxLayout;
    ldispo = new QLabel("Disponibilité", this);
    lecheance = new QLabel("Echéance", this);
    dispo = new QDateEdit(QDate::currentDate(),this);
    echeance = new QDateEdit(QDate::currentDate().addDays(1),this);
    dispo->setMinimumDate(QDate::currentDate());
    echeance->setMinimumDate(QDate::currentDate().addDays(1));
    dispo->setMaximumDate(echeance->date().addDays(-1));
    h3Layout->addWidget(ldispo);
    h3Layout->addWidget(dispo);
    h3Layout->addWidget(lecheance);
    h3Layout->addWidget(echeance);

    groupe = new QGroupBox("Attributs d'une tâche unitaire");
    groupe->setEnabled(true);
    gLayout = new QHBoxLayout;
    lduree = new QLabel("Durée", this);
    heure = new QSpinBox(this);
    minute = new QSpinBox(this);
    heure->setSuffix(" heures(s)");
    minute->setSuffix(" minute(s)");
    heure->setMinimum(0);
    heure->setMaximum(23);
    minute->setMinimum(0);
    minute->setMaximum(59);
    preemptive=new QCheckBox("Préemptive",this);
    gLayout->addWidget(lduree);
    gLayout->addWidget(heure);
    gLayout->addWidget(minute);
    gLayout->addWidget(preemptive);
    groupe->setLayout(gLayout);

    h4Layout = new QHBoxLayout;
    annuler=new QPushButton("Annuler", this);
    ajouter = new QPushButton("Ajouter la tâche", this);
    ajouter->setEnabled(false);
    h4Layout->addWidget(annuler);
    h4Layout->addWidget(ajouter);

    vLayout1 = new QVBoxLayout;
    vLayout1->addLayout(classlayout);
    vLayout1->addLayout(h1Layout);
    vLayout1->addLayout(h2Layout);
    vLayout1->addLayout(h3Layout);
    vLayout1->addWidget(groupe);
    vLayout1->addLayout(h4Layout);

    listeProjet = new QComboBox;
    lprojet = new QLabel("Choisir le projet:", this);
    ProjetManager& pm = ProjetManager::getInstance();
    for(ProjetManager::IteratorSTL it=pm.begin();it!=pm.end();++it)
        listeProjet->addItem((*it).getId());
    listeTacheC = new QComboBox;
    ltacheC = new QLabel("Choisir une tâche composite",this);
    afficheTacheC(listeProjet->currentText());
    //Choix des précédences
    listeTacheP = new QComboBox;
    ltacheP = new QLabel("Choisir une tâche précédente",this);
    afficheTacheP(listeProjet->currentText());
    vLayout2 = new QVBoxLayout;
    vLayout2->addWidget(lprojet);
    vLayout2->addWidget(listeProjet);
    vLayout2->addWidget(ltacheC);
    vLayout2->addWidget(listeTacheC);
    vLayout2->addWidget(ltacheP);
    vLayout2->addWidget(listeTacheP);
    vLayout2->setAlignment(Qt::AlignTop);

    projLayout = new QHBoxLayout;
    projLayout->addLayout(vLayout2);
    projLayout->addLayout(vLayout1);
    this->setLayout(projLayout);
    changeDate(listeProjet->currentText());
    QObject::connect(id, SIGNAL(textChanged(QString)),this, SLOT(activerAjout()));
    QObject::connect(titre, SIGNAL(textChanged(QString)),this, SLOT(activerAjout()));
    QObject::connect(heure, SIGNAL(valueChanged(int)),this, SLOT(activerAjout()));
    QObject::connect(minute, SIGNAL(valueChanged(int)),this, SLOT(activerAjout()));
    QObject::connect(unitaire, SIGNAL(toggled(bool)),this,SLOT(activerAjout()));
    QObject::connect(annuler, SIGNAL(clicked()),this, SLOT(accept()));
    QObject::connect(echeance, SIGNAL(dateChanged(QDate)),this,SLOT(modifierDate(QDate)));
    QObject::connect(unitaire, SIGNAL(toggled(bool)),groupe,SLOT(setEnabled(bool)));
    QObject::connect(ajouter, SIGNAL(clicked()),this, SLOT(ajoutTache()));
    QObject::connect(listeProjet, SIGNAL(currentIndexChanged(QString)),this,SLOT(afficheTacheC(QString)));
    QObject::connect(listeProjet, SIGNAL(currentIndexChanged(QString)),this,SLOT(afficheTacheP(QString)));
    QObject::connect(listeProjet, SIGNAL(currentIndexChanged(QString)),this,SLOT(changeDate(QString)));
    QObject::connect(preemptive, SIGNAL(toggled(bool)),this,SLOT(modifierDuree(bool)));
}


void TacheAjout::changeDate(QString t){
    if(t!=0){
        ProjetManager& pm = ProjetManager::getInstance();
        Projet& p=*pm.trouverProjet(t);
        dispo->setMinimumDate(p.getDispo());
        echeance->setMaximumDate(p.getEcheance());
    }
}

void TacheAjout::modifierDuree(bool b){
    if (b){
            heure->setMaximum(23);
    }
    else{
            heure->setMaximum(11);
    }
}

void TacheAjout::modifierDate(QDate mdate){
    dispo->setMaximumDate(mdate.addDays(-1));
}


void TacheAjout::activerAjout(){
    if(titre->text()!=0 && id->text()!=0 && listeProjet->currentText()!=0)
        if(unitaire->isChecked())
            if( Duree(heure->value(),minute->value()).getDureeEnMinutes()!=0 )
                ajouter->setEnabled(true);
            else
                ajouter->setEnabled(false);
        else
            ajouter->setEnabled(true);
    else
        ajouter->setEnabled(false);
}

void TacheAjout::ajoutTache(){
    QString desc;
    if (unitaire->isChecked())
        desc="unitaire";
    else
        desc="composite";
    ProjetManager& pm = ProjetManager::getInstance();
    Projet& p=*pm.trouverProjet(listeProjet->currentText());
    if (p.getTache(id->text())){
        QMessageBox::critical(this,"Erreur","La tâche existe déjà !");
        return;
    }
    if (listeTacheP->currentText()=="--Vide--"){
        if (listeTacheC->currentText()=="--Vide--"){
            p.ajouterTache(desc,id->text(),0,titre->text(),Duree(heure->value(),minute->value()),dispo->date(), echeance->date(),preemptive->isChecked());
            this->accept();
        }
        else{
            Tache* tc=p.getTache(listeTacheC->currentText());
            dynamic_cast<TComposite*>(tc)->ajouterSousTache(desc,id->text(),0,titre->text(),Duree(heure->value(),minute->value()),dispo->date(), echeance->date(),preemptive->isChecked());
            this->accept();
        }
    }else{
        Tache* prec = p.getTache(listeTacheP->currentText());
        if (listeTacheC->currentText()=="--Vide--"){
            p.ajouterTache(desc,id->text(),prec,titre->text(),Duree(heure->value(),minute->value()),dispo->date(), echeance->date(),preemptive->isChecked());
            this->accept();
        }
        else{
            Tache* tc=p.getTache(listeTacheC->currentText());
            dynamic_cast<TComposite*>(tc)->ajouterSousTache(desc,id->text(),prec,titre->text(),Duree(heure->value(),minute->value()),dispo->date(), echeance->date(),preemptive->isChecked());
            this->accept();
        }
    }

}

void TacheAjout::afficheTacheC(QString s){
    if (s!=0){
        listeTacheC->clear();
        ProjetManager& pm = ProjetManager::getInstance();
        Projet& p=*pm.trouverProjet(s);
        listeTacheC->addItem("--Vide--");
        for(Projet::IteratorSTL it=p.begin();it!=p.end();++it)
            if((*it).getType()=="composite"){
                listeTacheC->addItem((*it).getId());
                afficheSousTacheC(dynamic_cast<const TComposite&>(*it));
            }
    }

}

void TacheAjout::afficheTacheP(QString s){
    if (s!=0){
        while(listeTacheP->count()!=0){
            listeTacheP->removeItem(0);
        }
        ProjetManager& pm = ProjetManager::getInstance();
        Projet& p=*pm.trouverProjet(s);
        listeTacheP->addItem("--Vide--");
        for(Projet::IteratorSTL it=p.begin();it!=p.end();++it)
            listeTacheP->addItem((*it).getId());
    }
}

void TacheAjout::afficheSousTacheC(const TComposite& t){
    for(TComposite::IteratorSTL it=t.begin();it!=t.end();++it)
        if((*it).getType()=="composite"){
            listeTacheC->addItem((*it).getId());
            afficheSousTacheC(dynamic_cast<const TComposite&>(*it));
        }
    }
