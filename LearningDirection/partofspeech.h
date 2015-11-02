#ifndef PARTOFSPEECH_H
#define PARTOFSPEECH_H

#include <QList>
#include <QStringList>
#include <QDataStream>
class PartOfSpeech
{
public:
    friend QDataStream& operator<<(QDataStream& out, const PartOfSpeech& partOfSpeech);
    friend QDataStream& operator>>(QDataStream& in, PartOfSpeech& partOfSpeech);
    PartOfSpeech();
    ~PartOfSpeech();
};

#endif // PARTOFSPEECH_H
