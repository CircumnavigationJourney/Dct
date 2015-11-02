#include "translation.h"

Translation::Translation()
{

}

Translation::~Translation()
{

}

QDataStream& operator<<(QDataStream& out, const Translation& translation){

    return out << translation.fastTranslation
               << translation.partsOfSpeech;
}
QDataStream& operator>>(QDataStream& in, Translation& translation){

    return in >> translation.fastTranslation
              >> translation.partsOfSpeech;
}
