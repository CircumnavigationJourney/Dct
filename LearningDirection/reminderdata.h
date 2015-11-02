#ifndef REMINDERDATA_H
#define REMINDERDATA_H

#include <QDateTime>

class ReminderData
{
public:
    friend QDataStream& operator<<(QDataStream& out, const ReminderData& remData);
    friend QDataStream& operator>>(QDataStream& in, ReminderData& remData);
    ReminderData();
    ~ReminderData();
};

#endif // REMINDERDATA_H
