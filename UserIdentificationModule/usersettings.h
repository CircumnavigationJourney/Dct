#ifndef USERSETTINGS_H
#define USERSETTINGS_H
#include "uilanguage.h"
#include "uitheme.h"

#include <QDataStream>

class UserSettings
{

public:
    enum class Autologin{
        NotAllowed = 0,
        Allowed = 1
    };

    enum class Reminder{
        DoNotRemind = 0,
        SpacedRepetition = 1
    };

    UserSettings();
    ~UserSettings();

    friend QDataStream& operator<<(QDataStream& out, const UserSettings& settings);
    friend QDataStream& operator>>(QDataStream& in, UserSettings& settings);
    Autologin getAutologin() const {return autologin;}
private:
    UILanguage interfaceLang;
    UITheme theme;
    Autologin autologin;
    Reminder reminds;
};

#endif // USERSETTINGS_H
