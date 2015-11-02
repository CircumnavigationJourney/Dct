#include "partofspeech.h"

PartOfSpeech::PartOfSpeech()
{

}

PartOfSpeech::~PartOfSpeech()
{

}

    QDataStream& operator<<(QDataStream& out, const PartOfSpeech& partOfSpeech){return out;}
    QDataStream& operator>>(QDataStream& in, PartOfSpeech& partOfSpeech)       {return in;}
