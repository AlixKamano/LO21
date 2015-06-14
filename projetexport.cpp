#include "projetexport.h"

ProjetExport::ProjetExport(QWidget* fenetre) :  QDialog(fenetre){
    setWindowTitle("Export de projet");
    setFixedSize(400,150);

    h1Layout = new QHBoxLayout;
    listeProjet = new QComboBox;
    lprojet = new QLabel("Choisir le projet : ",this);
    ProjetManager& pm = ProjetManager::getInstance();
    listeProjet->addItem("--Vide--");
    for(ProjetManager::IteratorSTL it=pm.begin();it!=pm.end();++it)
        listeProjet->addItem((*it).getId());
    h1Layout->addWidget(lprojet);
    h1Layout->addWidget(listeProjet);

    h2Layout = new QHBoxLayout;
    exporter = new QPushButton("Exporter",this);
    exporter->setEnabled(false);
    annuler = new QPushButton("Annuler",this);
    h2Layout->addWidget(exporter);
    h2Layout->addWidget(annuler);

    vLayout = new QVBoxLayout;
    vLayout->addLayout(h1Layout);
    vLayout->addLayout(h2Layout);

    this->setLayout(vLayout);

    QObject::connect(annuler,SIGNAL(clicked()),this,SLOT(accept()));
    QObject::connect(exporter,SIGNAL(clicked()),this,SLOT(exportProjet()));
    QObject::connect(listeProjet,SIGNAL(currentIndexChanged(int)),this,SLOT(activerExport()));

}

void ProjetExport::exportProjet(){
    ProjetManager& pm = ProjetManager::getInstance();
    Projet& p = *pm.trouverProjet(listeProjet->currentText());
    QString filename = QFileDialog::getSaveFileName(this->parentWidget(),listeProjet->currentText(),"export_projet.xml","Fichier XML (*.xml)");
    p.save(filename);
    this->accept();
}

void ProjetExport::activerExport(){
    if(listeProjet->currentText()!=0)
        exporter->setEnabled(true);
}
