#ifndef VOCABULARYLIST_H
#define VOCABULARYLIST_H

//#include "vocabulary/vocabulary.h"
#include "vocabulary.h"
class VocabularyList
{

    int MAX_VOCAB_ID;
    int LAST_ACTIVE_ID = -1;
    QList<Vocabulary> vocabularyList;

public:


//    int getStatus(int index) const;
//    int getID(int index);
    int getLastActiveVocabularyID(){return LAST_ACTIVE_ID;}
    void setLastActiveVocabularyID(int id);

    int size(){return vocabularyList.size();}
    Vocabulary& operator[](int index){ return vocabularyList[index];} //TODO check for empty list
    bool containsName(QString name);
    bool containsID(int id);
    bool isEmpty(){return vocabularyList.isEmpty();}
    int getMaxID() {return vocabularyList.isEmpty() ? 1 : (vocabularyList.last().getID()+1);}
    //service
    //************************************************
    void createNewVocabulary(QString vocabularyName);
    void renameVocabulary(int ID, QString newName);
    void setStatusDeleted(int ID); //delete
    void setStatusActive(int ID); //recover
    void permanentDeletion(int ID);
    void join(int ID1,int ID2, QString newName);
    void importVocabulary(){//TODO
    }
    void exportVocabulary(){//TODO
    }
    //************************************************
    friend QDataStream& operator <<(QDataStream& out, const VocabularyList& vocabList);
    friend QDataStream& operator >>(QDataStream& in, VocabularyList& vocabList);
    VocabularyList();
    ~VocabularyList();
};

#endif // VOCABULARYLIST_H
