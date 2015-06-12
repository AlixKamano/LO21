#ifndef ACTIVITE_H
#define ACTIVITE_H

class Activite {        //Ajout de statut aux activités ?
    /*! \class Activité
     * \brief Classe permettant de stocker des activités traditionnelles
     */
private:
    QString titre;  /*!< Titre de l'activit*/
    Duree duree;    /*!< Durée de l'activité*/
public:
    //! Constructeur à partir de string et duree
    //! \param s QString&
    //! \param d Duree*/
    Activite(const QString&  s, const Duree d): titre(s), duree(d){};
    //! Accesseur au titre de l'activité
    QString getTitre()const{return titre;};
    //! Accesseur à la durée de l'activité
    Duree getDuree()const {return duree;};
};

#endif // ACTIVITE_H

