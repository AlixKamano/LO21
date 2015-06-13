
#include<QApplication>
#include <QFile>
#include <QTextCodec>
#include <QtXml>
#include <QMessageBox>

#include "projet.h"
#include "tache.h"
#include"evenement.h"


void Projet::addItem(Tache* t){
    if(nb==nbMax){
        Tache** new_tab=new Tache*[nbMax+10];
        for(int i=0;i<nb;i++){
            new_tab[i]=taches[i];
        }
        nbMax+=10;
        Tache **old_tab=taches;
        taches=new_tab;
        delete[] old_tab;
    }
    taches[nb]=t;
    nb++;
}

Tache* Projet::getTache(const QString &id) const{
    Tache* t=0;
    for(int i=0; i<nb;i++){
            if(id==taches[i]->getId()){
                return taches[i];
            }
            if(taches[i]->getType()=="composite")
                t=dynamic_cast<TComposite*>(taches[i])->getSousTache(id);
        }
        return t;
}


void Projet::ajouterTache(const QString& desc, const QString& id,Tache* prec, const QString& t, const Duree& du, const QDate& dispo, const QDate& deadline, bool preempt){
    if(getTache(id)){
        throw ProjetException("Error : L'identificateur existe deja");
    }
    //Appel à TacheFactory
    Tache* new_tache= TacheFactory::NewTache(desc,id,prec,t,dispo,deadline,du,preempt);
    Projet::addItem(new_tache);
}


Projet::IteratorSTL Projet::begin(){
    return IteratorSTL(taches);
}

Projet::IteratorSTL Projet::end(){
    return IteratorSTL(taches+nb);
}

void  Projet::save(const QString& f){
    file=f;
    QFile newfile( file);
    if (!newfile.open(QIODevice::WriteOnly | QIODevice::Text))
        throw CalendarException(QString("erreur sauvegarde tâches : ouverture fichier xml"));
    QXmlStreamWriter stream(&newfile);
    stream.setAutoFormatting(true);
    stream.writeStartDocument();
    stream.writeStartElement("taches");
    for(unsigned int i=0; i<nb; i++){
        stream.writeStartElement("tache");
        //stream.writeAttribute("preemptive", (taches[i]->getPreemptive())?"true":"false");
        stream.writeTextElement("identificateur",taches[i]->getId());
        stream.writeTextElement("titre",taches[i]->getTitre());
        stream.writeTextElement("disponibilite",taches[i]->getDispo().toString(Qt::ISODate));
        stream.writeTextElement("echeance",taches[i]->getEcheance().toString(Qt::ISODate));
        QString str;
        //str.setNum(taches[i]->getDuree().getDureeEnMinutes());
        stream.writeTextElement("duree",str);
        stream.writeEndElement();
    }
    stream.writeEndElement();
    stream.writeEndDocument();
    newfile.close();
}
