#ifndef WORD_H
#define WORD_H

#include <QList>
#include <QDebug>

#include "translation.h"
#include "reminderdata.h"
#include "testsdata.h"
#include "statisticsdata.h"

class Word
{
private:
    int ID;
    QString word;
    Translation translations;
    QString transcription;
    QList<int> activeInVocabularyList;
    QList<int> deletedInVocabularyList;
    QDateTime creationTime;
    ReminderData remData;
    TestsData wordTestsData;
    StatisticsData wordStatisticsData;
public:

    int getID() const {return ID;}
    bool operator ==(const Word& w);
    const QString* getWord() const {return &word;}
    QStringList* getFastTranslation() {return translations.getFastTranslations();}
    QString* getIPATranscription() {return &transcription;}
    QString getActiveInVocabularyList();
    QString getDeletedInVocabularyList();
    QString IntListToString(QList<int>& data);
    QDateTime& getCreationDate(){return creationTime;}

    void addToVocabulary(int vocabularyID);
    void deleteFromVocabulary(int vocabularyID);
    friend QDataStream& operator<< (QDataStream& out, const Word& word);
    friend QDataStream& operator>> (QDataStream& in, Word& word);
    //experimental constructor TODO add copy constructor + additional word attributes
    explicit Word(int ID, QString learnigLangWord, QStringList translation, QString transcrip, int vocabID);
    Word(){} // temporary solution
    ~Word();
};

#endif // WORD_H
