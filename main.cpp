#include "tienda.h"

#include <QApplication>
#include <QTranslator>
#include <QInputDialog>
#include "tienda.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Tienda w;
    w.show();
    return a.exec();
}
