#include "ajoutevenement.h"

ajoutEvenement::ajoutEvenement(QWidget *fenetre): QDialog(fenetre)
{
    setWindowTitle("Ajouter un evenement");
    setFixedSize(400,300);

    classlayout=new QHBoxLayout;
    lclasse=new QLabel("Type d'evenement",this);
    evtclasse = new QButtonGroup;
    tacheevt = new QRadioButton("Tache");
    activiteevt = new QRadioButton("Activite");
    tacheevt->setChecked(true);
    evtclasse->addButton(tacheevt);
    evtclasse->addButton(activiteevt);
    classlayout->addWidget(lclasse);
    classlayout->addWidget(tacheevt);
    classlayout->addWidget(activiteevt);


    liste1layout=new QHBoxLayout;
    listePro = new QComboBox;
    lpro = new QLabel("Choisir un projet",this);
    ProjetManager& pm = ProjetManager::getInstance();
    for(ProjetManager::IteratorSTL it=pm.begin();it!=pm.end();++it)
        listePro->addItem((*it).getId());

    liste1layout->addWidget(lpro);
    liste1layout->addWidget(listePro);

    liste2layout=new QHBoxLayout;
    listeEle = new QComboBox;
    lliste = new QLabel("Choisir une tache unitaire",this);
    liste2layout->addWidget(lliste);
    liste2layout->addWidget(listeEle);


    datelayout=new QHBoxLayout;
    ldate = new QLabel("Date", this);
    dateevt = new QDateEdit(QDate::currentDate(),this);
    datelayout->addWidget(ldate);
    datelayout->addWidget(dateevt);

    horlayout=new QHBoxLayout;
    lhoraire = new QLabel("Horaire de debut", this);
    hHoraire = new QSpinBox(this);
    mHoraire = new QSpinBox(this);
    hHoraire->setSuffix(" heures(s)");
    mHoraire->setSuffix(" minute(s)");
    hHoraire->setMinimum(0);
    hHoraire->setMaximum(23);
    mHoraire->setMinimum(0);
    mHoraire->setMaximum(59);
    horlayout->addWidget(lhoraire);
    horlayout->addWidget(hHoraire);
    horlayout->addWidget(mHoraire);

    dureelayout=new QHBoxLayout;
    lduree = new QLabel("Durée", this);
    mDuree = new QSpinBox(this);
    mDuree->setSuffix(" minute(s)");
    mDuree->setMinimum(0);
    mDuree->setMaximum(1440);
    dureelayout->addWidget(lduree);
    dureelayout->addWidget(mDuree);

    boutonlayout=new QHBoxLayout;
    annuler= new QPushButton("Annuler");
    ajouter=new QPushButton("Ajouter evenement");
    boutonlayout->addWidget(annuler);
    boutonlayout->addWidget(ajouter);
    ajouter->setEnabled(false);

    vLayout= new QVBoxLayout;
    vLayout->addLayout(classlayout);
    vLayout->addLayout(liste1layout);
    vLayout->addLayout(liste2layout);
    vLayout->addLayout(datelayout);
    vLayout->addLayout(horlayout);
    vLayout->addLayout(dureelayout);
    vLayout->addLayout(boutonlayout);
    this->setLayout(vLayout);

    QObject::connect(hHoraire, SIGNAL(valueChanged(int)),this, SLOT(activerAjout()));
    QObject::connect(mHoraire, SIGNAL(valueChanged(int)),this, SLOT(activerAjout()));
    QObject::connect(mDuree, SIGNAL(valueChanged(int)),this, SLOT(activerAjout()));
    QObject::connect(listePro, SIGNAL(currentIndexChanged(int)),this,SLOT(modifierTache()));
    QObject::connect(tacheevt, SIGNAL(toggled(bool)),this,SLOT(modifierSelection(bool)));
    QObject::connect(annuler, SIGNAL(clicked()),this, SLOT(accept()));
    QObject::connect(ajouter, SIGNAL(clicked()),this, SLOT(ajouterEvenement()));
    QObject::connect(listeEle, SIGNAL(currentIndexChanged(QString)),this,SLOT(modifierContrainte(QString)));
    afficheTacheU();
}

void ajoutEvenement::activerAjout(){
    if(listeEle->currentText()!=0 && Duree(hHoraire->value(),mHoraire->value()).getDureeEnMinutes()!=0 && mDuree!=0)
        if(tacheevt->isChecked())
            if(listePro->currentText()!=0)
                ajouter->setEnabled(true);
            else
                ajouter->setEnabled(false);
        else
            ajouter->setEnabled(true);
    else
        ajouter->setEnabled(false);
}

void ajoutEvenement::afficheActivite(){
    listeEle->clear();
    ActiviteManager& am = ActiviteManager::getInstance();
    for(ActiviteManager::IteratorSTL it=am.begin();it!=am.end();++it)
        listeEle->addItem((*it).getId());
}

void ajoutEvenement::modifierTache(){
    afficheTacheU();
}

void ajoutEvenement::afficheTacheU(){
    listeEle->clear();
    if(listePro->currentText()!=""){
    ProjetManager& pm = ProjetManager::getInstance();
    Projet* p =pm.trouverProjet(listePro->currentText());
        for(Projet::IteratorSTL itp=p->begin();itp!=p->end();++itp){
            if((*itp).getType()=="composite"){
                afficheSousTacheU(dynamic_cast<const TComposite&>(*itp));
            }
            if((*itp).getType()=="unitaire"){
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
        if((*it).getStatut()==0 && (*it).getStatutPrecedence()==1){
            if((*it).getEcheance()>QDate::currentDate())
                listeEle->addItem((*it).getId());
        }
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
    if (s!=0){
    if (tacheevt->isChecked())
        contrainteTache(s);
    if (activiteevt->isChecked())
        contrainteActivite(s);}
}


void ajoutEvenement::contrainteTache(QString s){
   listePro->setEnabled(true);
   if (listePro->currentText()!=""){
       ProjetManager& pm=ProjetManager::getInstance();
       Projet* p= pm.trouverProjet(listePro->currentText());
       Tache* t=p->getTache(s);
       if(dynamic_cast<TUnitaire*>(t)->getPreemptive()){
           mDuree->setEnabled(true);
           mDuree->setMaximum(dynamic_cast<TUnitaire*>(t)->getDuree().getDureeEnMinutes());
           mDuree->setValue(dynamic_cast<TUnitaire*>(t)->getDuree().getDureeEnMinutes());
       }
       else{
           mDuree->setEnabled(false);
           mDuree->setValue(dynamic_cast<TUnitaire*>(t)->getDuree().getDureeEnMinutes());
       }
        if(QDate::currentDate()<t->getDispo())
            dateevt->setMinimumDate(t->getDispo());
        else
            dateevt->setMinimumDate(QDate::currentDate());
        dateevt->setMaximumDate(t->getEcheance());
   }
}

void ajoutEvenement::contrainteActivite(QString s){
    ActiviteManager& am=ActiviteManager::getInstance();
    Activite* a=am.trouverActivite(listeEle->currentText());
    mDuree->setEnabled(false);
    mDuree->setValue(a->getDuree().getDureeEnMinutes());
    listePro->setEnabled(false);
    dateevt->setMinimumDate(QDate::currentDate());
    dateevt->clearMaximumDate();
}

bool ajoutEvenement::verifUnique(QDate d, Horaire h1, Horaire h2){
    EvtManager& em=EvtManager::getInstance();
    for(EvtManager::IteratorSTL it=em.begin();it!=em.end();++it){
        if(d==(*it).getDate() && (((*it).getHoraireD()<h1 && h1<(*it).getHoraireF()) || ((*it).getHoraireD()<h2 && h2<(*it).getHoraireF()) || ((*it).getHoraireD()<h2 && h1<(*it).getHoraireD()) || ((*it).getHoraireF()<h2 && h1<(*it).getHoraireF()))){
            return false;
        }
    }
    return true;
}

void ajoutEvenement::ajouterEvenement(){
    EvtManager& em=EvtManager::getInstance();
    if (activiteevt->isChecked()){
        ActiviteManager& am=ActiviteManager::getInstance();
        Activite* a=am.trouverActivite(listeEle->currentText());
        Duree temp((hHoraire->value())*60+mHoraire->value()+mDuree->value());
        if(temp.getheures()>24){
           int htemp=temp.getheures()-24;
           int mtemp=temp.getminute();
           Duree dureeenplus(htemp,mtemp);
           if(verifUnique(dateevt->date(),Horaire(hHoraire->value(),mHoraire->value()),Horaire(23,59)) && verifUnique(dateevt->date().addDays(1),Horaire(0,0),Horaire(htemp,mtemp))){
               em.ajouterEvt("activite",a,dateevt->date(),Horaire(hHoraire->value(),mHoraire->value()),Horaire(23,59),Duree(mDuree->value()-dureeenplus.getDureeEnMinutes()));
               em.ajouterEvt("activite",a,dateevt->date().addDays(1),Horaire(0,0),Horaire(htemp,mtemp),dureeenplus);
               this->accept();
           }
           else{
               QMessageBox::critical(this,"Erreur","C'est horaire est déjà pris !");
               return;
           }
        }
         else{
            if(verifUnique(dateevt->date(),Horaire(hHoraire->value(),mHoraire->value()),Horaire(temp.getheures(),temp.getminute()))){
                em.ajouterEvt("activite",a,dateevt->date(),Horaire(hHoraire->value(),mHoraire->value()),Horaire(temp.getheures(),temp.getminute()),Duree(a->getDuree()));
                this->accept();
            }
            else{
                QMessageBox::critical(this,"Erreur","C'est horaire est déjà pris !");
                return;
            }
        }
    }
    if (tacheevt->isChecked()){
        ProjetManager& pm=ProjetManager::getInstance();
        Projet* p=pm.trouverProjet(listePro->currentText());
        TUnitaire* t=dynamic_cast<TUnitaire*>(p->getTache(listeEle->currentText()));
        Duree temp((hHoraire->value())*60+mHoraire->value()+mDuree->value());
        if(temp.getheures()>24){
            int htemp=temp.getheures()-24;
            int mtemp=temp.getminute();
            Duree dureeenplus(htemp,mtemp);
            if(verifUnique(dateevt->date(),Horaire(hHoraire->value(),mHoraire->value()),Horaire(23,59)) && verifUnique(dateevt->date().addDays(1),Horaire(0,0),Horaire(htemp,mtemp))){
                em.ajouterEvt("tache",t,dateevt->date(),Horaire(hHoraire->value(),mHoraire->value()),Horaire(23,59),Duree(mDuree->value()-dureeenplus.getDureeEnMinutes()));
                em.ajouterEvt("tache",t,dateevt->date().addDays(1),Horaire(0,0),Horaire(htemp,mtemp),dureeenplus);
                if(!t->getPreemptive()) t->setStatut(1);
                this->accept();
            }
            else{
                QMessageBox::critical(this,"Erreur","C'est horaire est déjà pris !");
                return;
            }
        }
        else{
            if(verifUnique(dateevt->date(),Horaire(hHoraire->value(),mHoraire->value()),Horaire(temp.getheures(),temp.getminute()))){
                em.ajouterEvt("tache",t,dateevt->date(),Horaire(hHoraire->value(),mHoraire->value()),Horaire(temp.getheures(),temp.getminute()),Duree(mDuree->value()));
                if(!t->getPreemptive()) t->setStatut(1);
                this->accept();
            }
            else{
                QMessageBox::critical(this,"Erreur","C'est horaire est déjà pris !");
                return;
            }
        }
    }
}

