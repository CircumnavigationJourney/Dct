#ifndef USER_H
#define USER_H
#include <QDataStream>
#include <QList>
#include <QDebug>

class User
{
private:
    int id;
    QString userName;
    QString password;
    QString userFolder;
    QString userCodeString;
public:
    const QString* getUserName() const {return &userName;}
    const QString* getPassword() const {return &password;}
    void setUserName(QString newName){userName = newName;}
    void setPassword(QString newPassword) {password = newPassword;}
    QString getUserFolder() const {return userFolder;}
    QString getUserCodeString() const {return userCodeString;}
    int getId() const {return id;}
    bool isNull() const {return (userName.isNull() && userFolder.isNull());}
    bool operator==(const User &u) const{ return u.getUserName()->toLower() == userName.toLower() ? true : false;}
    friend QDataStream& operator<<(QDataStream &out, const User& user);
    friend QDataStream& operator>>(QDataStream &in, User& user);
    User(int uid, QString uname, QString upassword, QString ufolder, QString ucode);
    User(){}
    ~User();
};

#endif // USER_H
