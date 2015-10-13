#include "useridentificationmodule.h"

UserIdentificationModule::UserIdentificationModule(QObject *parent) : QObject(parent), engine(nullptr)
{
    //engine = nullptr;
    fileName = "\\userdb.dctdb";
#ifdef QT_DEBUG
    directory = "D:\\DRIVE\\Files\\Qt_Projects\\UserIdentificationForDicty";
#else
    directory = QApplication::applicationDirPath();
#endif
    loadData();
}

UserIdentificationModule::~UserIdentificationModule()
{
}

void UserIdentificationModule::createWindow(){
    if(engine == nullptr){
        engine = new QQmlEngine;
        QQmlComponent *component = new QQmlComponent(engine);

        component->loadUrl(QUrl(QStringLiteral("qrc:/LoginWindow.qml")));
        Q_ASSERT(component->isReady());
        windowObj = component->create();
        loginWindow = qobject_cast<QQuickWindow *> (windowObj);
        loginWindow->setFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);
        connect(loginWindow, SIGNAL(checkUser(QString, QString, int)), SLOT(checkUser(QString,QString,int)));
        connect(this,SIGNAL(setReplyText(QVariant)), loginWindow, SLOT(getErrorMessage(QVariant)));
        loginWindow->show();
    }
    else loginWindow->show();
}

void UserIdentificationModule::getUser(){
    createWindow();
    qDebug() << "created!";
}
void UserIdentificationModule::checkUser(QString name, QString password, int windowForm){
    int result;
    switch(windowForm){
    case static_cast<int>(WindowForm::Registration):
        if((result = registerNewUser(name, password)) >= 0) {
            User currUser = allUsersData.at(result);
            saveData();
            qDebug() << "user id : " << currUser.getId()
                     << "\nuser name: " << currUser.getUserName()
                     << "\nuser password: " << currUser.getPassword()
                     << "\nuser directory: " << currUser.getUserFolder();
        }
        else emit setReplyText(checkUserReply(result));
        break;
    case static_cast<int>(WindowForm::Login):
        if((result = loginUser(name, password)) >= 0) {
            User currUser = allUsersData.at(result);
            saveData();
            qDebug() << "user id : " << currUser.getId()
                     << "\nuser name: " << currUser.getUserName()
                     << "\nuser password: " << currUser.getPassword()
                     << "\nuser directory: " << currUser.getUserFolder();
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
    if(!allUsersData.isEmpty())
        for(int i = 0; i < allUsersData.size(); ++i)
            if(allUsersData.at(i).getUserName().toLower() == name.toLower())
                return static_cast<int>(Reply::UserIsAlreadyExists);
    int userId = allUsersData.isEmpty() ? 1 : int(allUsersData.last().getId() + 1);
    QString folder = generateUserFolder(userId);
    QString upass = encrypt(password);
    QString code("");// may be it's bad idea to use cryptography here, поэтому если это понадобится, то коде нужен для генерации индивидуальной строки с которой можно ксорить данные конкретного пользователя
    User temp(userId, name, upass, folder, code); //TODO folder code generator and password /user name encryption
    allUsersData.append(temp);
    return (allUsersData.size() - 1);
}
int UserIdentificationModule::loginUser(const QString &name, const QString &password){
    int userindex = 0;
    if(!allUsersData.isEmpty())
        while (userindex < allUsersData.size()){
            if(allUsersData.at(userindex).getUserName().toLower() == name.toLower()){
                if(allUsersData.at(userindex).getPassword() == encrypt(password)) return userindex;
                else return static_cast<int>(Reply::WrongPassword);
            }
            ++userindex;
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
    case static_cast<int>(Reply::CantFindUser): return QObject::tr("Error! User is not Found...");
    case static_cast<int>(Reply::UserIsAlreadyExists): return QObject::tr("The name is already registered. Try another one or Sign up...");
    case static_cast<int>(Reply::WrongPassword): return QObject::tr("Wrong password! try another one...");
    }
    return QObject::tr("ERROR, unexpected behavior detected. Please contact soft vendor");//TODO logs needed
}

void UserIdentificationModule::destroyWindow(){

    if(engine != nullptr) engine->deleteLater();
}
