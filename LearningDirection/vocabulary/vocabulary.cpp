#include "vocabulary.h"

Vocabulary::Vocabulary(int id, QString newVocName):
    ID(id),
    name(newVocName)

{
    qDebug() << "new Voc Created";
    creationDate = QDateTime::currentDateTime();
}

Vocabulary::~Vocabulary()
{

}

QDataStream& operator <<(QDataStream& out, const Vocabulary& voc){

    return out << voc.name
               << voc.status
               << voc.ID;
}

QDataStream& operator >>(QDataStream& in, Vocabulary& voc){

    return in >> voc.name
              >> voc.status
              >> voc.ID;
}
