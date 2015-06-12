#include<QApplication>
#include <QFile>
#include <QTextCodec>
#include<QTextStream>
#include <QtXml>
#include <QMessageBox>

#include"tache.h"
#include "evenement.h"
//Uniquemet pour avoir accès à CalendarException
//
int Tache::getStatutPrecedence()const{
    int statut=1;
    for(int i =0;i<nbPrec;i++)
        statut*=precedence[i]->getStatut();
    return statut;
}

void Tache::addPrecedence(Tache* t){
    //Vérifier si la tache n'est pas dans le tableau
    for(int i=0;i<nbPrec;i++)
        if(precedence[i]->getId()==t->getId())
            throw CalendarException ("La tâche a déjà été ajoutée comme précédente");
    //Ajouter le pointeur
    if(nbPrec==nbPrecMax){
        Tache** new_tab = new Tache*[nbPrecMax+10];
        for(int i=0;i<nbPrec;i++)
            new_tab[i]=precedence[i];
        nbPrecMax+=10;
        Tache** old_tab=precedence;
        precedence=new_tab;
        delete[] old_tab;
    }
    precedence[nbPrec]=t;
    nbPrec++;
}

void Tache::rmPrecedence(Tache* t){
    int i=0;
    while(i<nbPrec && precedence[i]!=t)
        i++;
    for(int j=i;j<nbPrec;j++)
        precedence[j]=precedence[j+1];
}

void TComposite::addSousTache(Tache* t){
    for(int i=0;i<nb;i++)
        if(sousTaches[i]==t)
            throw CalendarException("Cette tâche est déjà une sous-tache");
    if(nb==nbMax){
        Tache** new_tab = new Tache*[nbMax+10];
        for(int i=0;i<nb;i++)
            new_tab[i]=sousTaches[i];
        nbMax+=10;
        Tache** old_tab=sousTaches;
        sousTaches=new_tab;
        delete[] old_tab;
    }
    sousTaches[nb]=t;
    nb++;

}

void TUnitaire::saveT(QXmlStreamWriter *stream){
    stream->writeStartElement("tache");
    stream->writeStartElement("unitaire");       //Description
    stream->writeAttribute("preemptive", (getPreemptive())?"true":"false");
    stream->writeTextElement("identificateur",getId());
    stream->writeTextElement("titre",getTitre());
    stream->writeTextElement("disponibilite",getDispo().toString(Qt::ISODate));
    stream->writeTextElement("echeance",getEcheance().toString(Qt::ISODate));
    QString str;
    str.setNum(getDuree().getDureeEnMinutes());
    stream->writeTextElement("duree",str);
    stream->writeEndElement();
}

void TComposite::saveT(QXmlStreamWriter *stream){
    stream->writeStartElement("tache");
    stream->writeStartElement("composite");       //Description
    stream->writeTextElement("identificateur",getId());
    stream->writeTextElement("titre",getTitre());
    stream->writeTextElement("disponibilite",getDispo().toString(Qt::ISODate));
    stream->writeTextElement("echeance",getEcheance().toString(Qt::ISODate));
    if(nb!=0){
        stream->writeStartElement("Sous-taches:");
        for(int i=0;i<nb;i++)
            sousTaches[i]->saveT(stream);
    }
    stream->writeEndElement();
}
