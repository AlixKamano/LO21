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
    this->setFixedSize(800,700);
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

    hlayout1=new QHBoxLayout;
    hlayout2=new QHBoxLayout;
    hlayout3=new QHBoxLayout;

    hlayout1->addWidget(lundi);
    hlayout2->addWidget(ldate1);

    hlayout1->addWidget(mardi);
    hlayout2->addWidget(ldate2);

    hlayout1->addWidget(mercredi);
    hlayout2->addWidget(ldate3);

    hlayout1->addWidget(jeudi);
    hlayout2->addWidget(ldate4);

    hlayout1->addWidget(vendredi);
    hlayout2->addWidget(ldate5);

    hlayout1->addWidget(samedi);
    hlayout2->addWidget(ldate6);


    hlayout1->addWidget(dimanche);
    hlayout2->addWidget(ldate7);

    QGroupBox* test1=new QGroupBox;
    test1->setFixedSize(80,576);
    hlayout3->addWidget(test1);

    QGroupBox* test2=new QGroupBox;
    test2->setFixedSize(80,576);
    hlayout3->addWidget(test2);
    QGroupBox* test3=new QGroupBox;
    test3->setFixedSize(80,576);
    hlayout3->addWidget(test3);
    QGroupBox* test4=new QGroupBox;
    test4->setFixedSize(80,576);
    hlayout3->addWidget(test4);
    QGroupBox* test5=new QGroupBox;
    test5->setFixedSize(80,576);
    hlayout3->addWidget(test5);
    QGroupBox* test6=new QGroupBox;
    test6->setFixedSize(80,576);
    hlayout3->addWidget(test6);
    QGroupBox* test7=new QGroupBox;
    test7->setFixedSize(80,576);
    hlayout3->addWidget(test7);

    prec=new QPushButton("<");
    prec->setFixedSize(50,500);
    suiv=new QPushButton(">");
    suiv->setFixedSize(50,500);
    vlayout1=new QVBoxLayout;
    AjouterJour(date);
    hlayout->addWidget(prec);
    vlayout1->addLayout(hlayout1);
    vlayout1->addLayout(hlayout2);
    vlayout1->addLayout(hlayout3);
    hlayout->addLayout(vlayout1);
    hlayout->addWidget(suiv);
    this->setLayout(hlayout);
    QObject::connect(prec, SIGNAL(clicked()),this, SLOT(Precedent()));
    QObject::connect(suiv, SIGNAL(clicked()),this, SLOT(Suivant()));
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
}


void Agenda::Suivant(){
    date=date.addDays(7);
    AjouterJour(date);
}

void AjoutEvenement(Evt& e){

}
