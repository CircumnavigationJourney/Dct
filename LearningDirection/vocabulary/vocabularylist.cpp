#include "vocabularylist.h"
#define INITIALIZATION

void VocabularyList::setLastActiveVocabularyID(int id){
    if(containsID(id))
        LAST_ACTIVE_ID = id;
    else LAST_ACTIVE_ID = -1;
}

VocabularyList::VocabularyList()
{

    MAX_VOCAB_ID = getMaxID();

}

VocabularyList::~VocabularyList()
{

}
//надо решить, нужны ли эти проверки, или вызывать эти функции через индекс напрямую из модели
//int VocabularyList::getStatus(int index) const{
//    if (index > -1 && index < vocabularyList.size())
//        return vocabularyList[index].getStatus();
//    else return -1;
//}
//int VocabularyList::getID(int index){
//    if (index > -1 && index < vocabularyList.size())
//        return vocabularyList.at(index).getID();
//    else return -1;
//}
bool VocabularyList::containsName(QString name){
    if (!vocabularyList.isEmpty())
        return false;
    for (int i = 0; i < vocabularyList.size(); ++i)
        if (*(vocabularyList.at(i).getName()) == name)
            return true;

    return false;
}
bool VocabularyList::containsID(int id){
    if(!vocabularyList.isEmpty())
        return false;
    for(int i = 0; i < vocabularyList.size(); ++i)
        if(vocabularyList.at(i).getID() == id)
            return true;
    return false;

}
void VocabularyList::createNewVocabulary(QString vocabularyName){

    vocabularyList.append(Vocabulary(getMaxID(),vocabularyName));
    //qDebug() << "new voc creation " + QString(*(vocabularyList.last().getName()));
}

void VocabularyList::renameVocabulary(int ID, QString newName){
    if (vocabularyList.isEmpty()){
        qDebug() << "Error vocab list is empty !!!";
        return;
    }
    for (int i = 0; i < vocabularyList.size(); ++i){
        if (vocabularyList.at(i).getID() == ID){
            vocabularyList[i].setName(newName);
            return;
        }
    }
    qDebug() << "Trying to rename non existent vocabulary";
}

void VocabularyList::setStatusDeleted(int ID){
    if (vocabularyList.isEmpty()){
        qDebug() << "Error vocab list is empty !!!";
        return;
    }
    for (int i = 0; i < vocabularyList.size(); ++i){
        if (vocabularyList.at(i).getID() == ID){
            vocabularyList[i].setStatus(static_cast<int>(Vocabulary::VocabularyStatus::DELETED));
            return;
        }
    }
    qDebug() << "Trying to set Status to non existent vocabulary";
}
void VocabularyList::setStatusActive(int ID){
    if (vocabularyList.isEmpty()){
        qDebug() << "Error vocab list is empty !!!";
        return;
    }
    for (int i = 0; i < vocabularyList.size(); ++i){
        if (vocabularyList.at(i).getID() == ID){
            vocabularyList[i].setStatus(static_cast<int>(Vocabulary::VocabularyStatus::ACTIVE));
            return;
        }
    }
    qDebug() << "Trying to set Status to non existent vocabulary";
}
void VocabularyList::permanentDeletion(int ID){
    //TODO ******************************************
}
void VocabularyList::join(int ID1,int ID2, QString newName){
    //TODO ******************************************
}
QDataStream& operator <<(QDataStream& out, const VocabularyList& vocabList){
    return out << vocabList.MAX_VOCAB_ID << vocabList.LAST_ACTIVE_ID <<  vocabList.vocabularyList;
}
QDataStream& operator >>(QDataStream& in, VocabularyList& vocabList){
    return in >> vocabList.MAX_VOCAB_ID >> vocabList.LAST_ACTIVE_ID >> vocabList.vocabularyList;
}
