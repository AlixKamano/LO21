#include "evenement.h"
#include "evtManager.h"
#include <QApplication>
#include "fenetreprincipale.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    FenetrePrincipale fenetre;

    fenetre.show();
    return app.exec();
}
