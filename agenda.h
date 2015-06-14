#ifndef AGENDA_H
#define AGENDA_H
#include<QtWidgets>
#include"projetmanager.h"
#include "evtManager.h"
#include <vector>
//! \class Agenda
//! \brief Classe permettant d'afficher la fenêtre Agenda
class Agenda:public QDialog
{

    Q_OBJECT
private:
    vector<QPushButton*> boutons;//!< Vector contenant des QPushButton servant à afficher les cases dans l'agenda
    QDate dateref;//!< Date de référence permettant de connaitre la semaine à afficher
    QPushButton* prec,* suiv,*exporter,*fermer;
    QHBoxLayout* hlayout,*boutonLayout;
    QVBoxLayout* vlayout1,*vlayout2,*vlayout3,*vlayout4,*vlayout5,*vlayout6,*vlayout7,*vlayout8;
    QVBoxLayout *layoutCase1,*layoutCase2,*layoutCase3,*layoutCase4,*layoutCase5,*layoutCase6,*layoutCase7;
    QGroupBox *case1,*case2,*case3,*case4,*case5,*case6,*case7;
    QLabel* ldate1, *ldate2,*ldate3,*ldate4,*ldate5,*ldate6,*ldate7,*ldate;
    QDateEdit* findD;
public:
    //! Constructeur permettant d'afficher les évènements en fonction d'une semaine
    Agenda(QWidget *fenetre);
    //! Fonction permettant d'afficher les dates des jours d'une semaine
    //! \param QDate d : Date quelconque
    //! La fonction récupère ensuite le jour de la semaine correspondant à la date.
    //! Puis pour chaque jour de la semaine (lundi, mardi,...) nous calculons la date que nous stockons sous forme de texte
    void AjouterJour(QDate d);
    //! Fonction permettant d'ajouter un évènement à l'agenda
    //! \param const Evt& e : référence de l'évènement à ajouter
    //! La fonction récupère d'abord le type d'évènement associé (tache ou activité)
    //! Nous récupérons ensuite un horaire de début et de fin pour cet évènement
    //! et l'affichons dans le layout correspondant au jour auquel il est programmé
    void AjoutEvenement(const Evt &e);
    //! Fonction permettant de faire l'export dans un fichier XML d'une semaine de l'agenda
    //! \param QString& f : nom du fichier dans lequel sera exporté la semaine
    //! La fonction accède à ProjetManager::ItSemaine qui retourne les évènements programmés dans une certaine semaine
    //! Puis pour chaque évènement, nous écrivons chaque caractéristique dans le fichier
    void saveSemaine(QString& f);
    void afficherSemaine();

public slots:
    //! Slot permettant d'afficher la semaine précédente dans la fenêtre Agenda
    //! Nous nous contentons de retirer 7 à la date courante puis nous appelons AjouterJour
    void Precedent();
    //! Slot permmettant d'afficher la semaine suivante dans la fenêtre Agenda
    //! Ce slot fonction de la même manière que Précédent si ce n'est que nous ajoutons 7 au lieu de soustraire
    void Suivant();
    //! Slot permettant l'export de la semaine en XML
    //! Le nom de fichier ainsi que son emplacement sont choisis ici
    //! Puis le nom du fichier est transmis lors de l'appel de la fonction saveSemaine()
    void ExportSemaine();
    void changePage(QDate d);
};

#endif // AGENDA_H
