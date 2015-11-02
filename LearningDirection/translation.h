#ifndef TRANSLATION_H
#define TRANSLATION_H

#include "partofspeech.h"

class Translation
{
private:
    QStringList fastTranslation; //necessary for testing
    QList<PartOfSpeech> partsOfSpeech;
   friend QDataStream& operator<<(QDataStream& out, const Translation& translation);
   friend QDataStream& operator>>(QDataStream& in, Translation& translation);

public:
   QStringList* getFastTranslations() {return &fastTranslation;}
   void setFastTranslations(QStringList ft){ fastTranslation = ft;}
    Translation();
    ~Translation();
};

#endif // TRANSLATION_H
