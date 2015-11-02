#include "reminderdata.h"

ReminderData::ReminderData()
{

}

ReminderData::~ReminderData()
{

}

QDataStream& operator<<(QDataStream& out, const ReminderData& remData)
{
    return out;
}
QDataStream& operator>>(QDataStream& in, ReminderData& remData)
{
    return in;
}
