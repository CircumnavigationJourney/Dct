#ifndef USER_H
#define USER_H
#include <QDataStream>
#include <QList>
#include <QDebug>
#include "usersettings.h"
class User
{
private:
    int id;
    QString userName;
    QString password;
    QString userFolder;
    QString userCodeString;
    QString imageAdress;
    UserSettings settings;
public:
    const QString* getUserName() const {return &userName;}
    const QString* getPassword() const {return &password;}
    const QString* getUserFolder() const {return &userFolder;}
    const QString* getUserCodeString() const {return &userCodeString;}
    const QString* getUserImageAdress() const {return &imageAdress;}
    bool isAutologinEnabled() const {return static_cast<bool> (settings.getAutologin());}
    void setUserName(QString newName){userName = newName;}
    void setPassword(QString newPassword) {password = newPassword;}
    void setImageAdress(QString newAdress){imageAdress = newAdress;}
    int getId() const {return id;}
    bool isNull() const {return (userName.isNull() || userFolder.isNull());}
    bool operator==(const User &u) const{ return u.getUserName()->toLower() == userName.toLower() ? true : false;}
    friend QDataStream& operator<<(QDataStream &out, const User& user);
    friend QDataStream& operator>>(QDataStream &in, User& user);
    User(){}
    User(int uid, QString uname, QString upassword, QString ufolder, QString ucode);
    User(const User& user);
    User& operator=(const User& user);
    ~User();
};

#endif // USER_H
