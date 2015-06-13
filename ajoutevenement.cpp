#include "ajoutevenement.h"

ajoutEvenement::ajoutEvenement(QWidget *fenetre): QDialog(fenetre)
{
    setWindowTitle("Créer evenement");
    setFixedSize(600,300);

    classlayout=new QHBoxLayout;
    evtclasse = new QButtonGroup;
    tacheevt = new QRadioButton("Tache");
    activiteevt = new QRadioButton("Activite");
    evtclasse->addButton(tacheevt);
    tacheevt->setChecked(true);
    evtclasse->addButton(activiteevt);
    classlayout->addWidget(tacheevt);
    classlayout->addWidget(activiteevt);

    listelayout=new QHBoxLayout;
    listePro = new QComboBox;
    lpro = new QLabel("Choisir un projet",this);
    ProjetManager& pm = ProjetManager::getInstance();
    for(ProjetManager::IteratorSTL it=pm.begin();it!=pm.end();++it)
        listePro->addItem((*it).getId());
    listeEle = new QComboBox;
    lliste = new QLabel("Choisir une tache unitaire",this);
    listelayout->addWidget(lpro);
    listelayout->addWidget(listePro);
    listelayout->addWidget(lliste);
    listelayout->addWidget(listeEle);
    afficheTacheU();

    timelayout=new QHBoxLayout;
    ldate = new QLabel("Date", this);
    date = new QDateEdit(QDate::currentDate(),this);
    lhoraire = new QLabel("Horaire de debut", this);
    hHoraire = new QSpinBox(this);
    mHoraire = new QSpinBox(this);
    hHoraire->setSuffix(" heures(s)");
    mHoraire->setSuffix(" minute(s)");
    hHoraire->setMinimum(0);
    hHoraire->setMaximum(23);
    mHoraire->setMinimum(0);
    mHoraire->setMaximum(59);
    timelayout->addWidget(ldate);
    timelayout->addWidget(date);
    timelayout->addWidget(lhoraire);
    timelayout->addWidget(hHoraire);
    timelayout->addWidget(mHoraire);


    dureelayout=new QHBoxLayout;
    lduree = new QLabel("durée", this);
    hDuree = new QSpinBox(this);
    mDuree = new QSpinBox(this);
    hDuree->setSuffix(" heures(s)");
    mDuree->setSuffix(" minute(s)");
    hDuree->setMinimum(0);
    hDuree->setMaximum(23);
    mDuree->setMinimum(0);
    mDuree->setMaximum(59);
    dureelayout->addWidget(lduree);
    dureelayout->addWidget(hDuree);
    dureelayout->addWidget(mDuree);

    boutonlayout=new QHBoxLayout;
    annuler= new QPushButton("Annuler");
    ajouter=new QPushButton("Ajouter evenement");
    boutonlayout->addWidget(annuler);
    boutonlayout->addWidget(ajouter);

    vLayout= new QVBoxLayout;
    vLayout->addLayout(classlayout);
    vLayout->addLayout(listelayout);
    vLayout->addLayout(timelayout);
    vLayout->addLayout(dureelayout);
    vLayout->addLayout(boutonlayout);
    this->setLayout(vLayout);
    QObject::connect(tacheevt, SIGNAL(toggled(bool)),this,SLOT(modifierSelection(bool)));
    QObject::connect(annuler, SIGNAL(clicked()),this, SLOT(accept()));
    QObject::connect(listeEle, SIGNAL(currentIndexChanged(QString)),this,SLOT(modifierContrainte(QString)));
    QObject::connect(listePro, SIGNAL(currentIndexChanged(QString)),this,SLOT(modifierTache(QString)));
}

void ajoutEvenement::afficheActivite(){
    while(listeEle->count()!=0){
        listeEle->removeItem(0);
    }
    ActiviteManager& am = ActiviteManager::getInstance();
    for(ActiviteManager::IteratorSTL it=am.begin();it!=am.end();++it)
        listeEle->addItem((*it).getId());
}

void ajoutEvenement::modifierTache(QString s){
    afficheTacheU();
}

void ajoutEvenement::afficheTacheU(){
    while(listeEle->count()!=0){
        listeEle->removeItem(0);
    }
    if(listePro->currentText()!=0){
    ProjetManager& pm = ProjetManager::getInstance();
    Projet* p =pm.trouverProjet(listePro->currentText());
        for(Projet::IteratorSTL itp=p->begin();itp!=p->end();++itp){
            if((*itp).getType()=="composite"){
                afficheSousTacheU(dynamic_cast<const TComposite&>(*itp));
            }
            else{
                if((*itp).getStatut()==0 && (*itp).getStatutPrecedence()==1)
                    listeEle->addItem((*itp).getId());
            }
         }
    }
}
void ajoutEvenement::afficheSousTacheU(const TComposite& t){
    for(TComposite::IteratorSTL it=t.begin();it!=t.end();++it)
        if((*it).getType()=="composite"){
            afficheSousTacheU(dynamic_cast<const TComposite&>(*it));
        }
    else
        if((*it).getStatut()==0 && (*it).getStatutPrecedence()==1)
            listeEle->addItem((*it).getId());
}

void ajoutEvenement::modifierSelection(bool b){
    if(b==true){
        afficheTacheU();
    }
    else{
        afficheActivite();
    }
}

void ajoutEvenement::modifierContrainte(QString s){
    if (tacheevt->isChecked())
        contrainteTache(s);
    else
        contrainteActivite();
}


void ajoutEvenement::contrainteTache(QString s){
   listePro->setEnabled(true);
   ProjetManager& pm=ProjetManager::getInstance();
   Projet* p= pm.trouverProjet(listePro->currentText());
   Tache* t=p->getTache(s);
   if(dynamic_cast<TUnitaire*>(t)->getPreemptive()){
       hDuree->setEnabled(true);
       mDuree->setEnabled(true);
       hDuree->setMaximum(dynamic_cast<TUnitaire*>(t)->getDuree().getheures());
       mDuree->setMaximum(dynamic_cast<TUnitaire*>(t)->getDuree().getminute());
   }
   else{
       hDuree->setEnabled(false);
       mDuree->setEnabled(false);
   }
   date->setMinimumDate(t->getDispo());
   date->setMaximumDate(t->getEcheance());
}

void ajoutEvenement::contrainteActivite(){
    hDuree->setEnabled(false);
    mDuree->setEnabled(false);
    listePro->setEnabled(false);
}
