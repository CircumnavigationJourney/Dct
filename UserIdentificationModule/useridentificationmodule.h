#ifndef USERIDENTIFICATIONMODULE_H
#define USERIDENTIFICATIONMODULE_H

#include <QObject>
#include <QtQml/QQmlComponent>
#include <QtQml/QQmlEngine>
#include <QtQuick/QQuickWindow>
#include <QDebug>
#include <QApplication>
#include <QDesktopWidget>
#include <QApplication>
#include <QFile>
#include <QDir>
#include <QCryptographicHash>
#include <QVariant>
#include <QQmlContext>
#include <QVariant>
#include <QSharedPointer>

#include <QFuture>
#include <QtConcurrent/QtConcurrentRun>

#include "useraccountmanager.h"
//задача этого модуля - идентифицировать пользователя
//возможности :
//              1 регистрация нового пользователя
//              2 логин
//              3 смена пароля
// метод getUser возвращает копию объекта текущего пользователя
//в процессе разработки появилась идея разделить этот класс на несколько
//userAccountManager для работы чисто с пользовательскими данными
//и чисто функционал идентификации пользователя в рамках данного класса
//(создание всех необходимых окон и загрузка всех необходимых для этого файлов)

//TODO split this class in two or more
//(userAccountManager - class that can add and delete users and manage some users data)
class UserIdentificationModule : public QObject
{
    Q_OBJECT
public:
    enum class Behavior {
        Login = 0,
        Registration = 1,
        ChangePassword = 2
    };
    static int objectCount;
private:
    //positive reply is the user id, negative replies is about error
    enum class Reply {
        //Success = 0,
        CantFindUser = -1,
        UserIsAlreadyExists = -2,
        WrongPassword = -3
    };
    User currUser;
    UserListModel allUsersData;
    QSharedPointer<QQmlEngine> engine;
    //QQmlEngine *engine;
    QQmlComponent *component;
    QObject *windowObj;
    QQuickWindow *loginWindow;
//    QSharedPointer<QQmlComponent> component;
//    QSharedPointer<QObject> windowObj;
//    QSharedPointer<QQuickWindow> loginWindow;
    QString directory;
    QString usersSubDir;
    QString fileName;
    void createWindow(QString userName);
    int registerNewUser(const QString &name, const QString &password);
    int loginUser(const QString &name, const QString &password);
    int chagnePassword(const QString &name, const QString &password);
    QString generateUserFolder(int id);
    QString encrypt(const QString &sourceStr) const;
    QString checkUserReply(int reply);
public:
    bool loadData();
    bool saveData();
    Q_INVOKABLE bool isRegistered(const QString &name);
    User getUser();
    explicit UserIdentificationModule(QObject *parent = 0);
    ~UserIdentificationModule();
signals:
    void windowDestroyed();
    void closeWindow();
    void setReplyText(QVariant replyText);
    void initialize(QVariant beh, QVariant name);
private slots:
    void destroyWindow(QQuickCloseEvent *event);
    void checkUser(QString name, QString password, int behavior);
public slots:

};

#endif // USERIDENTIFICATIONMODULE_H
