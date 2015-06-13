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


void Projet::ajouterTache(const QString& desc, const QString& id, const QString& t, const Duree& du, const QDate& dispo, const QDate& deadline, bool preempt){
    if(getTache(id)){
        throw ProjetException("Error : L'identificateur existe deja");
    }
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

void Projet::load(const QString& f){
    //qDebug()<<"debut load\n";
    this->~Projet();
    file=f;
    QFile fin(file);
    // If we can't open it, let's show an error message.
    if (!fin.open(QIODevice::ReadOnly | QIODevice::Text)) {
        throw CalendarException("Erreur ouverture fichier tâches");
    }
    // QXmlStreamReader takes any QIODevice.
    QXmlStreamReader xml(&fin);
    //qDebug()<<"debut fichier\n";
    // We'll parse the XML until we reach end of it.
    while(!xml.atEnd() && !xml.hasError()) {
        // Read next element.
        QXmlStreamReader::TokenType token = xml.readNext();
        // If token is just StartDocument, we'll go to next.
        if(token == QXmlStreamReader::StartDocument) continue;
        // If token is StartElement, we'll see if we can read it.
        if(token == QXmlStreamReader::StartElement) {
            // If it's named taches, we'll go to the next.
            if(xml.name() == "taches") continue;
            // If it's named tache, we'll dig the information from there.
            if(xml.name() == "tache") {
                qDebug()<<"new tache\n";
                QString description;
                QString identificateur;
                QString titre;
                QDate disponibilite;
                QDate echeance;
                Duree duree;
                bool preemptive;

                QXmlStreamAttributes attributes = xml.attributes();
                /* Let's check that Task has attribute. */
                if(attributes.hasAttribute("preemptive")) {
                    QString val =attributes.value("preemptive").toString();
                    preemptive=(val == "true" ? true : false);
                }
                //qDebug()<<"preemptive="<<preemptive<<"\n";

                xml.readNext();
                //We're going to loop over the things because the order might change.
                //We'll continue the loop until we hit an EndElement named tache.


                while(!(xml.tokenType() == QXmlStreamReader::EndElement && xml.name() == "tache")) {
                    if(xml.tokenType() == QXmlStreamReader::StartElement) {
                        //We've found description
                        if(xml.name()== "description"){
                            xml.readNext();description=xml.text().toString();
                            //qDebug()<<"description="<<description<<"\n";
                        }
                        // We've found identificteur.
                        if(xml.name() == "identificateur") {
                            xml.readNext(); identificateur=xml.text().toString();
                            //qDebug()<<"id="<<identificateur<<"\n";
                        }

                        // We've found titre.
                        if(xml.name() == "titre") {
                            xml.readNext(); titre=xml.text().toString();
                            //qDebug()<<"titre="<<titre<<"\n";
                        }
                        // We've found disponibilite
                        if(xml.name() == "disponibilite") {
                            xml.readNext();
                            disponibilite=QDate::fromString(xml.text().toString(),Qt::ISODate);
                            //qDebug()<<"disp="<<disponibilite.toString()<<"\n";
                        }
                        // We've found echeance
                        if(xml.name() == "echeance") {
                            xml.readNext();
                            echeance=QDate::fromString(xml.text().toString(),Qt::ISODate);
                            //qDebug()<<"echeance="<<echeance.toString()<<"\n";
                        }
                        // We've found duree
                        if(xml.name() == "duree") {
                            xml.readNext();
                            duree.setDuree(0,xml.text().toString().toUInt());
                            //qDebug()<<"duree="<<duree.getDureeEnMinutes()<<"\n";
                        }
                    }
                    // ...and next...
                    xml.readNext();
                }
                //qDebug()<<"ajout tache "<<identificateur<<"\n";
                //récupérer une description
                ajouterTache(description,identificateur,titre,duree,disponibilite,echeance,preemptive);

            }
        }
    }
    // Error handling.
    if(xml.hasError()) {
        throw CalendarException("Erreur lecteur fichier taches, parser xml");
    }
    // Removes any device() or data from the reader * and resets its internal state to the initial state.
    xml.clear();
    //qDebug()<<"fin load\n";
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
