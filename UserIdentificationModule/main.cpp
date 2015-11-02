#include "widget.h"
#include <QApplication>
#include "useridentificationmodule.h"
int main(int argc, char *argv[])
{
    QGuiApplication a(argc, argv);
    a.setQuitOnLastWindowClosed(true);
    //Widget w;
    //w.show();
    UserIdentificationModule *module = new UserIdentificationModule;
    User user = module->getUser();
    User user2 = module->getUser();
    delete module;
    //module1.getUser();
//    module2.getUser();
//    module3.getUser();
//    module4.getUser();
//    module5.getUser();


    qDebug() << "here!";
    return a.exec();
}
