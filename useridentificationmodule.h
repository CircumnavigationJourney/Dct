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

#include "user.h"
class UserIdentificationModule : public QObject
{
    Q_OBJECT

private:
    enum class WindowForm {
        Login = 0,
        Registration = 1
    };
    enum class Reply {
        //Success = 0,
        CantFindUser = -1,
        UserIsAlreadyExists = -2,
        WrongPassword = -3
    };
    QList<User> allUsersData;
    QQmlEngine *engine = nullptr;
    QObject *windowObj;
    QQuickWindow *loginWindow;
    QString directory;
    QString fileName;
    void createWindow();
    bool loadData();
    bool saveData();
    int registerNewUser(const QString &name, const QString &password);
    int loginUser(const QString &name, const QString &password);
    QString generateUserFolder(int id);
    QString encrypt(const QString &sourceStr) const;
    QString checkUserReply(int reply);
public:
    void getUser();
    explicit UserIdentificationModule(QObject *parent = 0);
    ~UserIdentificationModule();

signals:
    void setReplyText(QVariant replyText);
private slots:
    void destroyWindow();
    void checkUser(QString name, QString password, int windowForm);
public slots:

};

#endif // USERIDENTIFICATIONMODULE_H
