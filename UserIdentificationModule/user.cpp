#include "user.h"


User::User(int uid, QString uname, QString upassword, QString ufolder, QString ucode):
    id(uid), userName(uname), password(upassword), userFolder(ufolder), userCodeString(ucode)
{
    //all new users get standard ui picture
    imageAdress = "standardUserPic.png";
}
User::User(const User &user){
    id = user.getId();
    userName = *(user.getUserName());
    password = *(user.getPassword());
    userFolder = *(user.getUserFolder());
    userCodeString = *(user.getUserCodeString());
    imageAdress = *(user.getUserImageAdress());
}

User& User::operator=(const User& user){
    if(this != &user) {
        this->User::~User();
        new(this) User(user);
    }
    return *this;
}

User::~User()
{

}

QDataStream& operator<<(QDataStream& out, const User& user){
    return out << user.id
               << user.userName
               << user.password
               << user.userFolder
               << user.userCodeString
               << user.imageAdress;
}
QDataStream& operator>>(QDataStream& in, User& user){
    return in >> user.id
              >> user.userName
              >> user.password
              >> user.userFolder
              >> user.userCodeString
              >> user.imageAdress;
}


