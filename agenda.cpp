#include "agenda.h"
#include "evtManager.h"
#include <QSize>

Agenda::Agenda(QWidget *fenetre) : QDialog(fenetre)
{
    dateref=QDate::currentDate();
    setWindowTitle("Agenda");
    this->setFixedSize(1050,730);
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
    vlayout8=new QVBoxLayout;


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

    layoutCase1=new QVBoxLayout;
    layoutCase1->setAlignment(Qt::AlignTop);
    layoutCase2=new QVBoxLayout;
    layoutCase2->setAlignment(Qt::AlignTop);
    layoutCase3=new QVBoxLayout;
    layoutCase3->setAlignment(Qt::AlignTop);
    layoutCase4=new QVBoxLayout;
    layoutCase4->setAlignment(Qt::AlignTop);
    layoutCase5=new QVBoxLayout;
    layoutCase5->setAlignment(Qt::AlignTop);
    layoutCase6=new QVBoxLayout;
    layoutCase6->setAlignment(Qt::AlignTop);
    layoutCase7=new QVBoxLayout;
    layoutCase7->setAlignment(Qt::AlignTop);


     case1=new QGroupBox;
    case1->setFixedSize(120,576);
    case1->setLayout(layoutCase1);
    vlayout1->addWidget(case1);

    case2=new QGroupBox;
    case2->setFixedSize(120,576);
    case2->setLayout(layoutCase2);
    vlayout2->addWidget(case2);

    case3=new QGroupBox;
    case3->setFixedSize(120,576);
    case3->setLayout(layoutCase3);
    vlayout3->addWidget(case3);

    case4=new QGroupBox;
    case4->setFixedSize(120,576);
    case4->setLayout(layoutCase4);
    vlayout4->addWidget(case4);

    case5=new QGroupBox;
    case5->setFixedSize(120,576);
    case5->setLayout(layoutCase5);
    vlayout5->addWidget(case5);

    case6=new QGroupBox;
    case6->setFixedSize(120,576);
    case6->setLayout(layoutCase6);
    vlayout6->addWidget(case6);

    case7=new QGroupBox;
    case7->setFixedSize(120,576);
    case7->setLayout(layoutCase7);
    vlayout7->addWidget(case7);

    prec=new QPushButton("<");
    prec->setFixedSize(50,500);
    suiv=new QPushButton(">");
    suiv->setFixedSize(50,500);
    AjouterJour(dateref);
    hlayout->addWidget(prec);
    hlayout->addLayout(vlayout1);
    hlayout->addLayout(vlayout2);
    hlayout->addLayout(vlayout3);
    hlayout->addLayout(vlayout4);
    hlayout->addLayout(vlayout5);
    hlayout->addLayout(vlayout6);
    hlayout->addLayout(vlayout7);
    hlayout->addWidget(suiv);
    hlayout->setAlignment(Qt::AlignHCenter);

    boutonLayout = new QHBoxLayout;
    boutonLayout->setAlignment(Qt::AlignLeft);
    ldate = new QLabel("Choississez une date:", this);
    findD = new QDateEdit(dateref,this);
    exporter = new QPushButton("Exporter la semaine",this);
    exporter->setFixedWidth(250);
    fermer = new QPushButton("Fermer",this);
    fermer->setFixedWidth(250);
    boutonLayout->addWidget(ldate);
    boutonLayout->addWidget(findD);
    boutonLayout->addWidget(exporter);
    boutonLayout->addWidget(fermer);
    vlayout8->addLayout(hlayout);
    vlayout8->addLayout(boutonLayout);



    this->setLayout(vlayout8);
    QObject::connect(findD, SIGNAL(dateChanged(QDate)),this, SLOT(changePage(QDate)));
    QObject::connect(prec, SIGNAL(clicked()),this, SLOT(Precedent()));
    QObject::connect(suiv, SIGNAL(clicked()),this, SLOT(Suivant()));
    QObject::connect(fermer, SIGNAL(clicked()),this, SLOT(accept()));
    QObject::connect(exporter, SIGNAL(clicked()),this, SLOT(ExportSemaine()));
    afficherSemaine();
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
    dateref=dateref.addDays(-7);
    AjouterJour(dateref);
    afficherSemaine();
}


void Agenda::Suivant(){
    dateref=dateref.addDays(7);
    AjouterJour(dateref);
    afficherSemaine();
}

void Agenda::changePage(QDate d){
    dateref=d;
    AjouterJour(dateref);
    afficherSemaine();
}

void Agenda::AjoutEvenement(const Evt &e){
    QString type;
    QString hd_h,hd_m,hf_h,hf_m;
    if (e.getType()=="tache")
        type=dynamic_cast<const EvtTache&>(e).getTache()->getId();
    if (e.getType()=="activite")
        type=dynamic_cast<const EvtActivite&>(e).getActivite()->getId();
    hd_h.setNum(e.getHoraireD().getHeure());
    hd_m.setNum(e.getHoraireD().getMinute());
    hf_h.setNum(e.getHoraireF().getHeure());
    hf_m.setNum(e.getHoraireF().getMinute());
    boutons.push_back(new QPushButton(type+"\n"+hd_h+"h"+hd_m+"-"+hf_h+"h"+hf_m));
    int j=e.getDate().dayOfWeek();
    switch(j){
    case 1:
        layoutCase1->addWidget(boutons[boutons.size()-1]);
         break;
    case 2:
        layoutCase2->addWidget(boutons[boutons.size()-1]);
        break;
    case 3:
        layoutCase3->addWidget(boutons[boutons.size()-1]);
        break;
    case 4:
        layoutCase4->addWidget(boutons[boutons.size()-1]);
        break;
    case 5:
        layoutCase5->addWidget(boutons[boutons.size()-1]);
        break;
    case 6:
        layoutCase6->addWidget(boutons[boutons.size()-1]);
        break;
    case 7:
        layoutCase7->addWidget(boutons[boutons.size()-1]);
        break;

    }
}


void Agenda::afficherSemaine(){
    for(unsigned int i=0;i<boutons.size();i++){
        delete boutons[i];
    }
    boutons.clear();
    int j = dateref.dayOfWeek();
    EvtManager& em=EvtManager::getInstance();
    for(EvtManager::ItSemaine it = em.getItSemaine(dateref.addDays(1-j),dateref.addDays(7-j)); !(it.isDone());it.next()){
        AjoutEvenement(*it);
    }
}

void Agenda::ExportSemaine(){
    QString filename = QFileDialog::getSaveFileName(this->parentWidget(),
                                                    QString::fromStdString("Exporter la semaine"),
                                                    "export_semaine.xml",
                                                    "Fichier XML (*.xml)");
    this->saveSemaine(filename);
    this->accept();
}

void Agenda::saveSemaine(QString &f){
    EvtManager& em = EvtManager::getInstance();
    QFile newfile(f);
    if(!newfile.open(QIODevice::WriteOnly | QIODevice::Text))
        throw CalendarException("erreur sauvegarde semaine : ouverture fichier XML");
    QXmlStreamWriter stream(&newfile);
    stream.setAutoFormatting(true);
    stream.writeStartDocument();
    stream.writeStartElement("Programmation");
    int j = dateref.dayOfWeek();
    for(EvtManager::ItSemaine it = em.getItSemaine(dateref.addDays(1-j),dateref.addDays(7-j));!it.isDone();it.next()){
        stream.writeStartElement("programmation");
        stream.writeTextElement("date",(*it).getDate().toString());
        stream.writeTextElement("horaire",((*it).getHoraireD().toString()));
        if((*it).getType()=="tache"){
            TUnitaire* t = dynamic_cast<const EvtTache&>((*it)).getTache();
        stream.writeTextElement("titre",t->getTitre());
        }
        if((*it).getType()=="activite"){
            Activite* a = dynamic_cast<const EvtActivite&>((*it)).getActivite();
        stream.writeTextElement("titre",a->getTitre());
        }
        QString str;
        str.setNum((*it).getDuree().getDureeEnMinutes());
        stream.writeTextElement("duree",str);
        stream.writeEndElement();
    }
    stream.writeEndElement();
    stream.writeEndElement();
    stream.writeEndDocument();
    newfile.close();
}

