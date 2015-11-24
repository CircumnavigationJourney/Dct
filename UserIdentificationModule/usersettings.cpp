#include "usersettings.h"

UserSettings::UserSettings()
{
    autologin = Autologin::Allowed;
    reminds = Reminder::SpacedRepetition;
}

UserSettings::~UserSettings()
{

}

QDataStream& operator<<(QDataStream& out, const UserSettings& settings){
    // TODO interface lang
    return out << (int)settings.autologin
               //<< settings.interfaceLang
               << (int)settings.reminds
               << settings.theme;
}

QDataStream& operator>>(QDataStream& in, UserSettings& settings){
   //TODO is it right decision to use temp int values and then convert it to enum class?
    int t_autologin, t_reminds;
    return in >> t_autologin
              //>> settings.interfaceLang
              >> t_reminds
              >> settings.theme;
    settings.autologin = static_cast<UserSettings::Autologin> (t_autologin);
    settings.reminds = static_cast<UserSettings::Reminder>(t_reminds);
}
