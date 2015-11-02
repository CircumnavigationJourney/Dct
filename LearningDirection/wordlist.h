#ifndef WORDLIST_H
#define WORDLIST_H

#include "word.h"
class WordList{
    int MAX_WORD_ID;
    int ACTIVE_VOCABULARY_ID = -1;
    QList<Word> wordList;
public:
    inline void setVocabularyFilter(int id) {ACTIVE_VOCABULARY_ID = id;}
    inline int getVocabularyFilter(){return ACTIVE_VOCABULARY_ID;}
    Word& operator[](int index){return wordList[index];} //TODO check for empty list
    int size() {return wordList.size();}
    int contains(QString word);
    bool isEmpty(){return wordList.isEmpty();}
    int getMaxID() {return wordList.isEmpty() ? 1 : (wordList.last().getID()+1);}
    void addFastWord(int currentVocab_ID, QString word, QStringList translation, QString transcription);//temporary

    void setTemporallyDeleted(int word_ID);
    void setActive(int vocab_ID, int word_ID);
    void permanentDeletion(int ID);
    int vichislitPoID(int ID);
    friend QDataStream& operator <<(QDataStream& out, const WordList& wList);
    friend QDataStream& operator >>(QDataStream& in, WordList& wList);
    WordList();
    ~WordList();
};

#endif // WORDLIST_H
