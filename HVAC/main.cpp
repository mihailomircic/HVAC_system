#include "dialog.h"
#include <QApplication>

int main(int argc, char *argv[]) 
{
    QApplication a(argc, argv);
    Dialog termostat;
    termostat.show();
    return a.exec();
}
