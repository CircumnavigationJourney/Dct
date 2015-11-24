#include "useridentificationmodule.h"

//#define TEST
UserIdentificationModule::UserIdentificationModule(QObject *parent) : QObject(parent), engine(nullptr)
{
    //engine = nullptr;
    fileName = "\\userdb.dctdb";
    usersSubDir = "\\users";
    objectCount++;
#ifdef QT_DEBUG
    directory = "D:\\DRIVE\\Files\\Qt_Projects\\UserIdentificationForDicty";
#else
    directory = QApplication::applicationDirPath();
#endif
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

User UserIdentificationModule::getUser(){
    //objectCount needed to check that this module method invoked at app start (to check autologin)
    qDebug() << "UserIDmodule objCount = " << objectCount;
    if(objectCount == 1){
        currUser = allUsersData.getLastActiveUser();
        if(!currUser.isNull()){
            if(currUser.isAutologinEnabled()){
                return currUser;
            }
        }
    }
    createWindow(QString());
    //wait for response from window
    QEventLoop waitForUserResponse;
    //connect(this, SIGNAL(currentUserChanged()), &waitForUserResponse, SLOT(quit()));
    connect(this, SIGNAL(windowDestroyed()), &waitForUserResponse, SLOT(quit()));
    waitForUserResponse.exec();
    return currUser;
}

void UserIdentificationModule::createWindow(QString userName){
    Behavior windowBehavior = allUsersData.isEmpty() ? Behavior::Registration : Behavior::Login;
    if(engine.isNull()){
        engine = QSharedPointer<QQmlEngine>(new QQmlEngine);
        engine.data()->rootContext()->setContextProperty("userListModel", &allUsersData);
        engine.data()->rootContext()->setContextProperty("UImodule", this);
        //engine.data()->setObjectOwnership(windowObj, QQmlEngine::CppOwnership);

        component = new QQmlComponent(engine.data());
        //component->setParent(engine.data()); //to delete on engine deletion
        component->loadUrl(QUrl(QStringLiteral("qrc:/LoginWindow.qml")));
        Q_ASSERT(component->isReady());

        windowObj = component->create();

        loginWindow = qobject_cast<QQuickWindow *> (windowObj);
        loginWindow->setFlags(static_cast<Qt::WindowFlags>(Qt::WA_TranslucentBackground |
                                                           Qt::WA_DeleteOnClose |
                                                           Qt::FramelessWindowHint |
                                                           Qt::WindowSystemMenuHint |
                                                           Qt::WindowMinMaxButtonsHint |
                                                           //Qt::WindowStaysOnTopHint |
                                                           Qt::WA_OpaquePaintEvent |
                                                           Qt::WA_NoSystemBackground));

        connect(loginWindow, SIGNAL(checkUser(QString, QString, int)), SLOT(checkUser(QString,QString,int)));
        connect(loginWindow, SIGNAL(closing(QQuickCloseEvent*)), SLOT(destroyWindow(QQuickCloseEvent*)));
        connect(this, SIGNAL(setReplyText(QVariant)), loginWindow, SLOT(getErrorMessage(QVariant)));
        connect(this, SIGNAL(initialize(QVariant, QVariant)), loginWindow, SLOT(getInitParameter(QVariant, QVariant)));
        connect(this, SIGNAL(closeWindow()), loginWindow, SLOT(closeWindow()));

        emit initialize((QVariant)static_cast<int> (windowBehavior), (QVariant) userName);
        loginWindow->show();
    }
    else loginWindow->show();
}


//SLOTS begin:-------------------------------------------------------------------------------------------------------
//behavior come from UI and is about how to use name and password
//for example there is Registration, Login, Change Password behavior
void UserIdentificationModule::checkUser(QString name, QString password, int behavior){
    int result;
    switch(behavior){
    case static_cast<int>(Behavior::Registration):
        if((result = registerNewUser(name, password)) >= 0) {
            currUser = allUsersData.at(result);
            //concurrent process
            QFuture<bool> future = QtConcurrent::run(this, &(this->saveData));
            Q_ASSERT(future);
            QString currUser_autologin = currUser.isAutologinEnabled() ? "true" : "false";
            qDebug() << "user id : " << currUser.getId()
                     << "\nuser name: " << *currUser.getUserName()
                     << "\nuser password: " << *currUser.getPassword()
                     << "\nuser directory: " << *currUser.getUserFolder()
                     << "\nuser autologin: " << currUser_autologin;
           emit closeWindow();
            return;
        }
        else emit setReplyText(checkUserReply(result));
        break;
    case static_cast<int>(Behavior::Login):
        if((result = loginUser(name, password)) >= 0) {
            //concurrent process (for saving last active user)
            QFuture<bool> future = QtConcurrent::run(this, &(this->saveData));
            Q_ASSERT(future);
            QString currUser_autologin = currUser.isAutologinEnabled() ? "true" : "false";
            currUser = allUsersData.at(result);
            qDebug() << "user id : " << currUser.getId()
                     << "\nuser name: " << *currUser.getUserName()
                     << "\nuser password: " << *currUser.getPassword()
                     << "\nuser directory: " << *currUser.getUserFolder()
                     << "\nuser autologin: " << currUser_autologin;
            emit closeWindow();
            return;
        }
        else emit setReplyText(checkUserReply(result));
        break;
    case static_cast<int>(Behavior::ChangePassword):
        if((result = chagnePassword(name, password)) >= 0) {
            //concurrent process (for saving new password)
            QFuture<bool> future = QtConcurrent::run(this, &(this->saveData));
            Q_ASSERT(future);
            currUser = allUsersData.at(result);
            qDebug() << "Password Was Changed for :"
                     << "user id : " << currUser.getId()
                     << "\nuser name: " << *currUser.getUserName()
                     << "\nuser password: " << *currUser.getPassword()
                     << "\nuser directory: " << *currUser.getUserFolder();
            emit closeWindow();
            return;
        }
        else emit setReplyText(checkUserReply(result));
        break;
    }
}

void UserIdentificationModule::destroyWindow(QQuickCloseEvent*event){
    //Q_UNUSED(event);
    if(!engine.isNull()) {
        qDebug() << "loginWindow destruction";
        disconnect(loginWindow, SIGNAL(checkUser(QString, QString, int)), this, SLOT(checkUser(QString,QString,int)));
        disconnect(this, SIGNAL(setReplyText(QVariant)), loginWindow, SLOT(getErrorMessage(QVariant)));
        disconnect(loginWindow, SIGNAL(closing(QQuickCloseEvent*)), this, SLOT(destroyWindow(QQuickCloseEvent*)));
        engine.data()->collectGarbage();
        //engine.data()->clearComponentCache();
        //engine.clear();
    }
    emit windowDestroyed();
}
//SLOTS ends---------------------------------------------------------------------------------------------------------------

//TODO rewrite load and save functions. add more safety
bool UserIdentificationModule::loadData(){
    QString filePath(directory + usersSubDir + fileName);
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
    QDir userDir(directory + usersSubDir);
    if(!userDir.exists()){
        userDir.mkdir(directory + usersSubDir);
    }
    QString filePath(directory + usersSubDir + fileName);
    QFile file(filePath);
    if(!file.open(QIODevice::WriteOnly)){
        //TODO if file currently unavailable try to wait for some time
        //(may be it's concurrent process currently writing to file)
        qDebug() << filePath << " problem writing file!";
    }
    QDataStream outputData(&file);
    outputData << allUsersData;
    file.close();
    return true;
}

int UserIdentificationModule::registerNewUser(const QString &name, const QString &password){
    //Check if name already exists
    if(!allUsersData.isEmpty()){
        QString checkName = name.toLower();
        for(int i = 0; i < allUsersData.size(); ++i){
            if(allUsersData.at(i).getUserName()->toLower() == checkName){
                return static_cast<int>(Reply::UserIsAlreadyExists);
            }
        }
    } //Registration
    int userID = allUsersData.isEmpty() ? 1 : int(allUsersData.last().getId() + 1);
    QString folder = generateUserFolder(userID);
    QString upass = encrypt(password);
    QString code("");// may be it's bad idea to use cryptography here, поэтому если это понадобится, то код нужен для генерации индивидуальной строки с которой можно ксорить данные конкретного пользователя
    User temp(userID, name, upass, folder, code);
    allUsersData.append(temp);
    allUsersData.setLastActiveUser(userID);
    return (allUsersData.size() - 1);
}

int UserIdentificationModule::loginUser(const QString &name, const QString &password){
    int userindex = 0;
    if(!allUsersData.isEmpty()){
        QString checkName = name.toLower();
        while (userindex < allUsersData.size()){
            if(allUsersData.at(userindex).getUserName()->toLower() == checkName){
                if(*(allUsersData.at(userindex).getPassword()) == encrypt(password)){
                    allUsersData.setLastActiveUser(allUsersData.at(userindex).getId());
                    return userindex;
                }
                else {
                    return static_cast<int>(Reply::WrongPassword);
                }
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
                allUsersData.setLastActiveUser(allUsersData.at(userindex).getId());
                return userindex;
            }
            ++userindex;
        }
    }
    return static_cast<int>(Reply::CantFindUser);
}

//TODO need relative path to user directory
QString UserIdentificationModule::generateUserFolder(int id){
    QDir userDir;
    QDir mainUsersDir(directory + usersSubDir); //hold all users data in one folder named usersSubDir("users")
    if(!mainUsersDir.exists()){
        mainUsersDir.mkdir(directory + usersSubDir);
    }
    QString path;
    do{
        path = directory + usersSubDir + "\\" + QString(QCryptographicHash::hash(QString::number(id).toUtf8(),
                                                                   QCryptographicHash::Md5).toHex());
        userDir.setPath(path);
        ++id;
    } while (userDir.exists());

    userDir.mkdir(userDir.path());
    return path;
}

QString UserIdentificationModule::encrypt(const QString &sourceStr) const{
    return QString(QCryptographicHash::hash(sourceStr.toUtf8(), QCryptographicHash::Sha1).toHex());
}

QString UserIdentificationModule::checkUserReply(int reply){
    switch (reply){
    case static_cast<int>(Reply::CantFindUser):
        return QObject::tr("User is not Found...");
    case static_cast<int>(Reply::UserIsAlreadyExists):
        return QObject::tr("The name is already registered. Try another one or Sign up...");
    case static_cast<int>(Reply::WrongPassword):
        return QObject::tr("Wrong password! try another one...");
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
