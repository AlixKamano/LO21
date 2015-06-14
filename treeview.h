#ifndef TREEVIEW_H
#define TREEVIEW_H
#include<QtWidgets>
#include"projetmanager.h"

class treeView: public QDialog
{
    //! \class TreeView
    //! \brief class permettant de gérer la fenêtre d'affichage des projets et des tâches sous forme d'arbre
    Q_OBJECT
private:
    QTreeWidget* tree;
    QPushButton* retour;
public:
    //! Constructeur de treeView
    treeView(QWidget* fenetre);
    //! Fonction permettant de faire une boucle sur le ProjetManager et d'appeler AjouterArbre pour chaque projet
     //! \param QTreeWidget *t : pointeur sur l'arbre où les projets et tâches sont ajoutées
    void AjouterArbre(QTreeWidget *t);
    //! Fonction permettant d'ajouter un projet dans l'abre
    //! \param QTreeWidget *t : pointeur sur l'arbre où les projets et tâches sont ajoutées
    //! \param Projet& p: référence sur le projet à insérer dans l'abre
    //! Appelle ensuite AjouterArbre sur les différentes tâches du projet
    void AjouterArbre(QTreeWidget *t, Projet& p);
    //! Fonction permettant d'ajouter une tâche dans l'abre
    //! \param QTreeWidget *t : pointeur sur l'arbre où les projets et tâches sont ajoutées
    //! \param const Tache& tc: référence sur la tâche, composite ou unitaire, à insérer dans l'abre
    //! Si la tâche est composite, ajoute la tâche à l'arbre et appelle AjouterArbre sur les sous-taches
    //! Sinon, rajoute la tâche ubitaire dans l'arbre
    void AjouterArbre(QTreeWidgetItem *t,const Tache& tc);
};

#endif // TREEVIEW_H
