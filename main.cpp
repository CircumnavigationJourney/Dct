#include "widget.h"
#include <QApplication>
#include "useridentificationmodule.h"
int main(int argc, char *argv[])
{
    QGuiApplication a(argc, argv);
    a.setQuitOnLastWindowClosed(false);
    //Widget w;
    //w.show();
    UserIdentificationModule module;
//    UserIdentificationModule module1;
//    UserIdentificationModule module2;
//    UserIdentificationModule module3;
//    UserIdentificationModule module4;
//    UserIdentificationModule module5;
    module.getUser();
//    module1.getUser();
//    module2.getUser();
//    module3.getUser();
//    module4.getUser();
//    module5.getUser();


    qDebug() << "here!";
    return a.exec();
}
