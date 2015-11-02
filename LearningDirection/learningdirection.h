#ifndef LEARNINGDIRECTION_H
#define LEARNINGDIRECTION_H
#include "vocabulary/vocabularyproxymodel.h"
#include "wordsortfiltermodel.h"
#include "langlistiso.h"
//#define TEST_LD
#include <QFile>
#include <QTextCodec>

//loading vocabularies and words of learning direction
//connects words proxy model and vocabularies proxy model
class LearningDirection
{
    QString learningLanguageISOCode;
    QString knownLanguageISOCode;
    QString path;

    VocabularyList *vocabListData;
    WordList *wordListData;

    //TODO make a loader according to current user
    bool LoadLearningDirectionData();

#ifdef TEST_LD
    void oldDicty();
#endif
public:
    VocabularyModel *vocabModel;
    VocabularyProxyModel *vocabProxyModel;

    WordModel *wordModel;
    WordProxyModel *wordProxyModel;


    QString getName();
    int getLastActiveVocabulary(){return vocabListData->getLastActiveVocabularyID();}
    LearningDirection(QString learningLang, QString knownLang);
    ~LearningDirection();
};

#endif // LEARNINGDIRECTION_H
