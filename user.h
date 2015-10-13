#ifndef USER_H
#define USER_H
#include <QDataStream>
#include <QList>

class User
{
private:
    int id;
    QString userName;
    QString password;
    QString userFolder;
    QString userCodeString;
public:
    QString getUserName() const {return userName;}
    void setUserName(QString newName){userName = newName;}
    QString getPassword() const {return password;}
    void setPassword(QString newPassword) {password = newPassword;}
    QString getUserFolder() const {return userFolder;}
    QString getUserCodeString() const {return userCodeString;}
    int getId() const {return id;}

    bool operator==(const User &u) const{ return u.getUserName().toLower() == userName.toLower() ? true : false;}
    friend QDataStream& operator<<(QDataStream &out, const User& user);
    friend QDataStream& operator>>(QDataStream &in, User& user);
    User(int uid, QString uname, QString upassword, QString ufolder, QString ucode);
    User(){}
    ~User();

};

#endif // USER_H
