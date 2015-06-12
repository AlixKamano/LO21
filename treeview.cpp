#include "treeview.h"

treeView::treeView(QWidget *fenetre): QDialog(fenetre)
{
    QVBoxLayout *layoutp = new QVBoxLayout;
    tree = new QTreeWidget();
    retour = new QPushButton("Retour");
    AjouterArbre(tree);
    layoutp->addWidget(tree);
    layoutp->addWidget(retour);
    setLayout(layoutp);
    QObject::connect(retour, SIGNAL(clicked()),this, SLOT(accept()));
}


void treeView::AjouterArbre(QTreeWidget* t){
    ProjetManager& pm = ProjetManager::getInstance();
    for(ProjetManager::IteratorSTL it=pm.begin();it!=pm.end();++it){
        AjouterArbre(t,*it);
    }
}

void treeView::AjouterArbre(QTreeWidget* t, Projet& p){
    QTreeWidgetItem *projet = new QTreeWidgetItem(t,QStringList(p.getId()+QString(" ")+p.getTitre()));
    for(Projet::IteratorSTL it=p.begin();it!=p.end();++it){
        AjouterArbre(projet,(*it));
    }
}



void treeView::AjouterArbre(QTreeWidgetItem* t, const Tache &tc){
    if (tc.getType()=="composite"){
        QTreeWidgetItem* tache = new QTreeWidgetItem(t,QStringList(tc.getId()+QString(" ")+tc.getTitre()));
        for(TComposite::IteratorSTL it=dynamic_cast<const TComposite&>(tc).begin();it!=dynamic_cast<const TComposite&>(tc).end();++it){
            AjouterArbre(tache,(*it));
        }
    }
    if (tc.getType()=="unitaire")
    new QTreeWidgetItem(t,QStringList(tc.getId()+QString(" ")+tc.getTitre()));
}


