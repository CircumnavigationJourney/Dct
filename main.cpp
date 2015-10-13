#include "widget.h"
#include <QApplication>
#include "useridentificationmodule.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //Widget w;
    //w.show();
    UserIdentificationModule module;
    module.getUser();
    qDebug() << "here!";
    return a.exec();
}
