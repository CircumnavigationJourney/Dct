#include "user.h"


User::User(int uid, QString uname, QString upassword, QString ufolder, QString ucode):
    id(uid), userName(uname), password(upassword), userFolder(ufolder), userCodeString(ucode)
{

}

User::~User()
{

}

 QDataStream& operator<<(QDataStream &out, const User& user){
    return out << user.id
    << user.userName
    << user.password
    << user.userFolder
    << user.userCodeString;
}
 QDataStream& operator>>(QDataStream &in, User& user){
    return in >> user.id
    >> user.userName
    >> user.password
    >> user.userFolder
    >> user.userCodeString;
}


