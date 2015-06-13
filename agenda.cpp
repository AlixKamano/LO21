#include "agenda.h"

Agenda::Agenda(QWidget *fenetre) : QDialog(fenetre)
{
    /*QHBoxLayout* layoutp=new QHBoxLayout;
    QTableWidget* table = new QTableWidget(12, 5, this);
    table->setHorizontalHeaderLabels(QStringList(QStringList()<<"Lundi"<<"Mardi"<<"Mercredi"<<"Jeudi"<<"Vendredi"<<"Samedi"<<"Dimanche"));
    table->setVerticalHeaderLabels(QStringList(QStringList()<<"0h-2h"<<"2h-4h"<<"4h-6h"<<"6h-8h"<<"8h-10h"<<"10h-12h"<<"12h-14h"<<"14h-16h"<<"16h-18h"<<"18h-20h"<<"20h-22h"<<"22h-24h"));
    QPushButton* m=new QPushButton;
    QTableWidgetItem *newItem = new QTableWidgetItem(m);
        table->setItem(2, 3, newItem);
    layoutp->addWidget(table);
    this->setLayout(layoutp);*/
    date=QDate::currentDate();
    this->setFixedSize(1000,700);
    QLabel* lundi=new QLabel("Lundi", this);
    QLabel* mardi=new QLabel("Mardi", this);
    QLabel* mercredi=new QLabel("Mercredi", this);
    QLabel* jeudi=new QLabel("Jeudi", this);
    QLabel* vendredi=new QLabel("Vendredi", this);
    QLabel* samedi=new QLabel("Samedi", this);
    QLabel* dimanche=new QLabel("Dimanche", this);
    ldate1=new QLabel(this);
    ldate2=new QLabel(this);
    ldate3=new QLabel(this);
    ldate4=new QLabel(this);
    ldate5=new QLabel(this);
    ldate6=new QLabel(this);
    ldate7=new QLabel(this);
    hlayout=new QHBoxLayout;
    hlayout->setAlignment(Qt::AlignJustify);

    vlayout1=new QVBoxLayout;
    vlayout2=new QVBoxLayout;
    vlayout3=new QVBoxLayout;
    vlayout4=new QVBoxLayout;
    vlayout5=new QVBoxLayout;
    vlayout6=new QVBoxLayout;
    vlayout7=new QVBoxLayout;


    vlayout1->addWidget(lundi);
    vlayout1->addWidget(ldate1);

    vlayout2->addWidget(mardi);
    vlayout2->addWidget(ldate2);

    vlayout3->addWidget(mercredi);
    vlayout3->addWidget(ldate3);

    vlayout4->addWidget(jeudi);
    vlayout4->addWidget(ldate4);

    vlayout5->addWidget(vendredi);
    vlayout5->addWidget(ldate5);

    vlayout6->addWidget(samedi);
    vlayout6->addWidget(ldate6);


    vlayout7->addWidget(dimanche);
    vlayout7->addWidget(ldate7);

    case1=new QVBoxLayout;
    case1->setAlignment(Qt::AlignTop);
    case2=new QVBoxLayout;
    case2->setAlignment(Qt::AlignTop);
    case3=new QVBoxLayout;
    case3->setAlignment(Qt::AlignTop);
    case4=new QVBoxLayout;
    case4->setAlignment(Qt::AlignTop);
    case5=new QVBoxLayout;
    case5->setAlignment(Qt::AlignTop);
    case6=new QVBoxLayout;
    case6->setAlignment(Qt::AlignTop);
    case7=new QVBoxLayout;
    case7->setAlignment(Qt::AlignTop);


    QGroupBox* test1=new QGroupBox;
    test1->setFixedSize(120,576);
    test1->setLayout(case1);
    vlayout1->addWidget(test1);

    QGroupBox* test2=new QGroupBox;
    test2->setFixedSize(120,576);
    test2->setLayout(case2);
    vlayout2->addWidget(test2);

    QGroupBox* test3=new QGroupBox;
    test3->setFixedSize(120,576);
    test3->setLayout(case3);
    vlayout3->addWidget(test3);

    QGroupBox* test4=new QGroupBox;
    test4->setFixedSize(120,576);
    test4->setLayout(case4);
    vlayout4->addWidget(test4);

    QGroupBox* test5=new QGroupBox;
    test5->setFixedSize(120,576);
    test5->setLayout(case5);
    vlayout5->addWidget(test5);

    QGroupBox* test6=new QGroupBox;
    test6->setFixedSize(120,576);
    test6->setLayout(case6);
    vlayout6->addWidget(test6);

    QGroupBox* test7=new QGroupBox;
    test7->setFixedSize(120,576);
    test7->setLayout(case7);
    vlayout7->addWidget(test7);

    prec=new QPushButton("<");
    prec->setFixedSize(50,500);
    suiv=new QPushButton(">");
    suiv->setFixedSize(50,500);
    AjouterJour(date);
    hlayout->addWidget(prec);
    hlayout->addLayout(vlayout1);
    hlayout->addLayout(vlayout2);
    hlayout->addLayout(vlayout3);
    hlayout->addLayout(vlayout4);
    hlayout->addLayout(vlayout5);
    hlayout->addLayout(vlayout6);
    hlayout->addLayout(vlayout7);
    hlayout->addWidget(suiv);
    this->setLayout(hlayout);
    QObject::connect(prec, SIGNAL(clicked()),this, SLOT(Precedent()));
    QObject::connect(suiv, SIGNAL(clicked()),this, SLOT(Suivant()));
    ProjetManager &pm=ProjetManager::getInstance();
    pm.ajouterProjet("P","t",QDate(10,04,2000),QDate(10,04,3000),5);
    ProjetManager::IteratorSTL it=pm.begin();
    (*it).ajouterTache("unitaire","Pan",0,"t",Duree(0,0),QDate(),QDate(),false);
    Tache* t=(*it).getTache("Pan");
    EvtTache e(QDate(2015,06,13),Horaire(8,20),Horaire(9,30),Duree(10),dynamic_cast<TUnitaire*>(t));
    AjoutEvenement(e);
}

void Agenda::AjouterJour(QDate d){
    int jour=d.dayOfWeek();
    ldate1->setText(d.addDays(1-jour).toString("dd.MM.yyyy"));
    ldate2->setText(d.addDays(2-jour).toString("dd.MM.yyyy"));
    ldate3->setText(d.addDays(3-jour).toString("dd.MM.yyyy"));
    ldate4->setText(d.addDays(4-jour).toString("dd.MM.yyyy"));
    ldate5->setText(d.addDays(5-jour).toString("dd.MM.yyyy"));
    ldate6->setText(d.addDays(6-jour).toString("dd.MM.yyyy"));
    ldate7->setText(d.addDays(7-jour).toString("dd.MM.yyyy"));
}

void Agenda::Precedent(){
    date=date.addDays(-7);
    AjouterJour(date);
    ProjetManager &pm=ProjetManager::getInstance();
    pm.ajouterProjet("MK","t",QDate(10,04,2000),QDate(10,04,3000),5);
    ProjetManager::IteratorSTL it=pm.begin();
    (*it).ajouterTache("unitaire","Ma",0,"O",Duree(0,0),QDate(),QDate(),false);
    Tache* t=(*it).getTache("Ma");
    EvtTache e(QDate(2015,06,10),Horaire(8,20),Horaire(9,30),Duree(10),dynamic_cast<TUnitaire*>(t));
    AjoutEvenement(e);
}


void Agenda::Suivant(){
    date=date.addDays(7);
    AjouterJour(date);
}

void Agenda::AjoutEvenement(Evt& e){
    QString type;
    QString hd_h,hd_m,hf_h,hf_m;

    if (e.getType()=="tache")
        type=dynamic_cast<EvtTache&>(e).getTache()->getId();
    if (e.getType()=="activite")
        type=dynamic_cast<EvtActivite&>(e).getActivite()->getId();
    hd_h.setNum(e.getHoraireD().getHeure());
    hd_m.setNum(e.getHoraireD().getMinute());
    hf_h.setNum(e.getHoraireF().getHeure());
    hf_m.setNum(e.getHoraireF().getMinute());
    boutons.push_back(new QPushButton(type+"\n"+hd_h+"h"+hd_m+"-"+hf_h+"h"+hf_m));
    int j=e.getDate().dayOfWeek();
    switch(j){
    case 1:
        case1->addWidget(boutons[boutons.size()-1]);
         break;
    case 2:
        case2->addWidget(boutons[boutons.size()-1]);
        break;
    case 3:
        case3->addWidget(boutons[boutons.size()-1]);
        break;
    case 4:
        case4->addWidget(boutons[boutons.size()-1]);
        break;
    case 5:
        case5->addWidget(boutons[boutons.size()-1]);
        break;
    case 6:
        case6->addWidget(boutons[boutons.size()-1]);
        break;
    case 7:
        case7->addWidget(boutons[boutons.size()-1]);
        break;

    }
}
