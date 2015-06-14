#ifndef ACTIVITE_H
#define ACTIVITE_H
#include <QString>
#include "timing.h"

using namespace TIME;

class Activite {        //Ajout de statut aux activités ?
    /*! \class Activité
     * \brief Classe permettant de stocker des activités traditionnelles
     */
private:
    QString id; /*!< Titre de l'activité*/
    QString titre;  /*!< Titre de l'activité*/
    Duree duree;    /*!< Durée de l'activité*/
public:
    //! Constructeur à partir de string et duree
    //! \param s QString&
    //! \param d Duree*/
    Activite(const QString& i,const QString&  s, const Duree d):id(i), titre(s), duree(d){}
    //! Accesseur à l'identifiant de l'activité
    QString getId()const{return id;}
    //! Accesseur au titre de l'activité
    QString getTitre()const{return titre;}
    //! Accesseur à la durée de l'activité
    Duree getDuree()const {return duree;}
};

#endif // ACTIVITE_H

