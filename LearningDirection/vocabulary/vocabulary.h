#ifndef VOCABULARY_H
#define VOCABULARY_H
#include <QString>
#include <QDataStream>
#include <QDateTime>
#include <QDebug>
class Vocabulary
{

    int status = 1;
    int ID = 0;
    QString name;
    QDateTime creationDate;

public:
    enum class VocabularyStatus{
        DELETED = 0,
        ACTIVE = 1,
        MAX
    };
    bool setStatus(int newStatus){/*return newStatus >= static_cast<int>(VocabularyStatus::MAX) ? false : */ qDebug() <<"setStatus = " << status;(status = newStatus); return true;}
    void setName(QString newName){ qDebug() << "new Voc name : " << newName; name = newName;}

    int getID() const {return ID;}
    int getStatus() const {return status;}
    const QString* getName() const {return &name;}

    friend QDataStream& operator <<(QDataStream& out, const Vocabulary& voc);
    friend QDataStream& operator >>(QDataStream& in, Vocabulary& voc);
    explicit Vocabulary(int id, QString newVocName);
    bool operator==(const Vocabulary& v){
      return v.getID() == this->getID() ? true : false;
    }
    Vocabulary(){} //temporary solution
    ~Vocabulary();
};

#endif // VOCABULARY_H
