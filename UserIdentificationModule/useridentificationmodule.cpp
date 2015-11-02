#include "useridentificationmodule.h"

//#define TEST
UserIdentificationModule::UserIdentificationModule(QObject *parent) : QObject(parent), engine(nullptr)
{
    //engine = nullptr;
    fileName = "/userdb.dctdb";
#ifdef QT_DEBUG
    directory = "D:\\DRIVE\\Files\\Qt_Projects\\UserIdentificationForDicty";
#else
    directory = QApplication::applicationDirPath();
#endif
    loadData();
    for(int i = 0; i < allUsersData.size(); ++i){

        if(*(allUsersData.at(i).getUserName()) == "") allUsersData.removeAt(i);
    }
    qDebug() << this->metaObject()->className() << " created";
#ifdef TEST
    for(int i = 0; i < 1000; ++i)
        registerNewUser(QString::number(i), QString::number(1));
#endif

}

UserIdentificationModule::~UserIdentificationModule()
{
    if(!engine.isNull()){
        engine.clear();
    }
    qDebug() << "engine pointer isNull :" << engine.isNull();
    qDebug() << this->metaObject()->className() << " deleted";

}

void UserIdentificationModule::createWindow(Behavior behavior, QString userName){
    if(engine.isNull()){
        engine = QSharedPointer<QQmlEngine>(new QQmlEngine);
        engine.data()->rootContext()->setContextProperty("userListModel", &allUsersData);
        engine.data()->rootContext()->setContextProperty("UImodule", this);

        component = new QQmlComponent(engine.data());
        component->setParent(engine.data()); //to delete on engine deletion
        component->loadUrl(QUrl(QStringLiteral("qrc:/LoginWindow.qml")));
        Q_ASSERT(component->isReady());

        windowObj = component->create();
        //windowObj->setParent(engine.data()); //to delete on engine deletion
        //engine.data()->setObjectOwnership(windowObj, QQmlEngine::CppOwnership);
        loginWindow = qobject_cast<QQuickWindow *> (windowObj);
        loginWindow->setFlags(static_cast<Qt::WindowFlags>(Qt::WA_TranslucentBackground | /*Qt::WA_DeleteOnClose | */Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint | Qt::WA_OpaquePaintEvent | Qt::WA_NoSystemBackground));

        connect(loginWindow, SIGNAL(checkUser(QString, QString, int)), SLOT(checkUser(QString,QString,int)));
        connect(loginWindow, SIGNAL(closing(QQuickCloseEvent*)), SLOT(destroyWindow(QQuickCloseEvent*)));
        connect(this, SIGNAL(setReplyText(QVariant)), loginWindow, SLOT(getErrorMessage(QVariant)));
        connect(this, SIGNAL(initialize(QVariant, QVariant)), loginWindow, SLOT(getInitParameter(QVariant, QVariant)));

        emit initialize((QVariant)static_cast<int> (behavior), (QVariant) userName);
        loginWindow->show();
    }
    else loginWindow->show();
}

User UserIdentificationModule::getUser(){

    createWindow(Behavior::ChangePassword, QString());
    QEventLoop waitForUserResponse;
    connect(this, SIGNAL(currentUserChanged()), &waitForUserResponse, SLOT(quit()));
    connect(this, SIGNAL(windowDestroyed()), &waitForUserResponse, SLOT(quit()));
    waitForUserResponse.exec();

    if(currUser != nullptr)
        return *(currUser);
    else return User();

}
void UserIdentificationModule::checkUser(QString name, QString password, int behavior){
    int result;
    switch(behavior){
    case static_cast<int>(Behavior::Registration):
        if((result = registerNewUser(name, password)) >= 0) {
            currUser = &(allUsersData[result]);
            //concurrent process
            QFuture<bool> future = QtConcurrent::run(this, &(this->saveData));
            Q_ASSERT(future);
            qDebug() << "user id : " << currUser->getId()
                     << "\nuser name: " << *currUser->getUserName()
                     << "\nuser password: " << currUser->getPassword()
                     << "\nuser directory: " << currUser->getUserFolder();
            loginWindow->close();
            emit currentUserChanged(); return;
        }
        else emit setReplyText(checkUserReply(result));
        break;
    case static_cast<int>(Behavior::Login):
        if((result = loginUser(name, password)) >= 0) {
            currUser = &(allUsersData[result]);
            //saveData();
            qDebug() << "user id : " << currUser->getId()
                     << "\nuser name: " << *(currUser->getUserName())
                     << "\nuser password: " << currUser->getPassword()
                     << "\nuser directory: " << currUser->getUserFolder();
            loginWindow->close();
            emit currentUserChanged(); return;
        }
        else emit setReplyText(checkUserReply(result));
        break;
    case static_cast<int>(Behavior::ChangePassword):
        if((result = chagnePassword(name, password)) >= 0) {
            currUser = &(allUsersData[result]);
            qDebug() << "Password Was Changed for :"
                     << "user id : " << currUser->getId()
                     << "\nuser name: " << *(currUser->getUserName())
                     << "\nuser password: " << currUser->getPassword()
                     << "\nuser directory: " << currUser->getUserFolder();
            loginWindow->close();
            emit currentUserChanged(); return;
        }
        else emit setReplyText(checkUserReply(result));
        break;
    }
}
//TODO rewrite load and save functions. add more safety
bool UserIdentificationModule::loadData(){
    QString filePath(directory+fileName);
    QFile file(filePath);
    if(!file.open(QIODevice::ReadOnly)){
        qDebug() << filePath << " does not exists!";
        return false;
    }
    QDataStream inputData(&file);
    inputData >> allUsersData;
    file.close();
    return true;
}
bool UserIdentificationModule::saveData(){
    QString filePath(directory+fileName);
    QFile file(filePath);
    if(!file.open(QIODevice::WriteOnly)){
        qDebug() << filePath << " problem writing file!";
    }
    QDataStream outputData(&file);
    outputData << allUsersData;
    file.close();
    return true;
}

int UserIdentificationModule::registerNewUser(const QString &name, const QString &password){
    if(!allUsersData.isEmpty()){
        QString checkName = name.toLower();
        for(int i = 0; i < allUsersData.size(); ++i)
            if(allUsersData.at(i).getUserName()->toLower() == checkName)
                return static_cast<int>(Reply::UserIsAlreadyExists);
    }

    int userId = allUsersData.isEmpty() ? 1 : int(allUsersData.last().getId() + 1);
    QString folder = generateUserFolder(userId);
    QString upass = encrypt(password);
    QString code("");// may be it's bad idea to use cryptography here, поэтому если это понадобится, то код нужен для генерации индивидуальной строки с которой можно ксорить данные конкретного пользователя
    User temp(userId, name, upass, folder, code);
    allUsersData.append(temp);
    return (allUsersData.size() - 1);
}
int UserIdentificationModule::loginUser(const QString &name, const QString &password){
    int userindex = 0;
    if(!allUsersData.isEmpty()){
        QString checkName = name.toLower();
        while (userindex < allUsersData.size()){
            if(allUsersData.at(userindex).getUserName()->toLower() == checkName){
                if(allUsersData.at(userindex).getPassword() == encrypt(password)) return userindex;
                else return static_cast<int>(Reply::WrongPassword);
            }
            ++userindex;
        }
    }
    return static_cast<int>(Reply::CantFindUser);
}
int UserIdentificationModule::chagnePassword(const QString &name, const QString &password){
    int userindex = 0;
    if(!allUsersData.isEmpty()){
        QString checkName = name.toLower();
        while (userindex < allUsersData.size()){
            if(allUsersData.at(userindex).getUserName()->toLower() == checkName){
                allUsersData[userindex].setPassword(encrypt(password));
                return userindex;
            }
            ++userindex;
        }
    }
    return static_cast<int>(Reply::CantFindUser);
}

QString UserIdentificationModule::generateUserFolder(int id){
    QDir userDir;
    QString path;
    do{
        path = directory + "\\" + QString(QCryptographicHash::hash(QString::number(id).toUtf8(), QCryptographicHash::Md5).toHex());
        userDir.setPath(path);
        ++id;
    }while (userDir.exists());

    userDir.mkdir(userDir.path());
    return path;
}
QString UserIdentificationModule::encrypt(const QString &sourceStr) const{
    return QString(QCryptographicHash::hash(sourceStr.toUtf8(), QCryptographicHash::Sha1).toHex());
}
QString UserIdentificationModule::checkUserReply(int reply){
    switch (reply){
    case static_cast<int>(Reply::CantFindUser): return QObject::tr("User is not Found...");
    case static_cast<int>(Reply::UserIsAlreadyExists): return QObject::tr("The name is already registered. Try another one or Sign up...");
    case static_cast<int>(Reply::WrongPassword): return QObject::tr("Wrong password! try another one...");
    }
    return QObject::tr("ERROR, unexpected behavior detected. Please contact soft vendor");//TODO logs needed
}
bool UserIdentificationModule::isRegistered(const QString &name){
    if(allUsersData.isEmpty()) return false;
    for(int i = 0; i < allUsersData.size(); ++i){

        if(allUsersData.at(i).getUserName()->toLower() == name.toLower()) return true;
    }
    return false;
}
void UserIdentificationModule::destroyWindow(QQuickCloseEvent*event){

    //Q_UNUSED(event);

    if(!engine.isNull()) {
        qDebug() << "loginWindow destruction";
        disconnect(loginWindow, SIGNAL(checkUser(QString, QString, int)), this, SLOT(checkUser(QString,QString,int)));
        disconnect(this, SIGNAL(setReplyText(QVariant)), loginWindow, SLOT(getErrorMessage(QVariant)));
        disconnect(loginWindow, SIGNAL(closing(QQuickCloseEvent*)), this, SLOT(destroyWindow(QQuickCloseEvent*)));
        engine.data()->collectGarbage();
        windowObj->deleteLater();
        //engine.data()->clearComponentCache();
        //engine.clear();
    }
    emit windowDestroyed();
}

//Вариант с Вью который не работает
//void UserIdentificationModule::createWindow(){
//    if(engine.isNull()){
////        engine = QSharedPointer<QQmlEngine>(new QQmlEngine);
////        //component = QSharedPointer<QQmlComponent>(new QQmlComponent(engine));
////        component = new QQmlComponent(engine.data());
////        component->setParent(engine.data()); //to delete on engine deletion
//////        QQmlContext *context = engine->rootContext();
////        engine.data()->rootContext()->setContextProperty("userListModel", &allUsersData);
////        component->loadUrl(QUrl(QStringLiteral("qrc:/LoginWindow.qml")));
////        Q_ASSERT(component->isReady());
////        windowObj = component->create();
////        windowObj->setParent(engine.data()); //to delete on engine deletion
//        loginWindow = new QQuickView;
//        loginWindow->setSource(QUrl(QStringLiteral("qrc:/LoginWindow.qml")));
//        //engine.data()->setObjectOwnership(windowObj, QQmlEngine::CppOwnership);
//        //loginWindow = qobject_cast<QQuickView*> (windowObj);
//        //QQuickWindow::setDefaultAlphaBuffer(true);
//        loginWindow->setColor(Qt::transparent);
//        //loginWindow->setFlags(static_cast<Qt::WindowFlags>(Qt::WA_TranslucentBackground | Qt::WA_DeleteOnClose | Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint | Qt::WA_OpaquePaintEvent | Qt::WA_NoSystemBackground));
//        //loginWindow->setFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);
//        connect(loginWindow, SIGNAL(checkUser(QString, QString, int)), SLOT(checkUser(QString,QString,int)));
//        connect(this, SIGNAL(setReplyText(QVariant)), loginWindow, SLOT(getErrorMessage(QVariant)));
////        connect(loginWindow, SIGNAL(canceled()),SLOT(destroyWindow()));
//        connect(loginWindow, SIGNAL(closing(QQuickCloseEvent*)), SLOT(destroyWindow(QQuickCloseEvent*)));
//        loginWindow->show();
//    }
//    else loginWindow->show();
//}
