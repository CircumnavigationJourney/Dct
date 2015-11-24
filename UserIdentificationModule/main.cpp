#include "widget.h"
#include <QApplication>
#include "useridentificationmodule.h"
int UserIdentificationModule::objectCount = 0;
int main(int argc, char *argv[])
{
    QGuiApplication a(argc, argv);
    a.setQuitOnLastWindowClosed(true);
    //Widget w;
    //w.show();

    UserIdentificationModule *module = new UserIdentificationModule;
    module->loadData();

    User user(module->getUser());
    qDebug() << *(user.getUserName()) << " = " <<  (user.getUserName())->isEmpty();
//    if((*user.getUserName()).isEmpty()){
//        qDebug() << *(user.getUserName()) << " = " <<  (user.getUserName())->isEmpty();
//        a.quit();
//    }


    //User user2 = module->getUser();
    delete module;
    //module1.getUser();
    //    module2.getUser();
    //    module3.getUser();
    //    module4.getUser();
    //    module5.getUser();

    // return a.exec();
}
