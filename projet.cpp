#include <QApplication>
#include <QFile>
#include <QTextCodec>
#include <QtXml>
#include <QMessageBox>

#include "projet.h"
#include "tache.h"
#include "evenement.h"


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
    for(int i=0; i<nb;i++){
            if(id==taches[i]->getId()){
                return taches[i];
            }
        }
        return 0;
}


void Projet::ajouterTache(const QString& desc, const QString& id, const QString& t, const Duree& du, const QDate& dispo, const QDate& deadline, bool preempt){
    if(getTache(id)){
        throw ProjetException("Error : L'identificateur existe deja");
    }
    if(du.getDureeEnHeures()>12&&preempt==true)
        throw ProjetException("Error, la durée de la tâche doit être inférieure à 12h");
    //Appel à TacheFactory
    Tache* new_tache= TacheFactory::NewTache(desc,id,t,dispo,deadline,du,preempt);
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
        taches[i]->saveT(&stream);
    }
    stream.writeEndElement();
    stream.writeEndDocument();
    newfile.close();
}
