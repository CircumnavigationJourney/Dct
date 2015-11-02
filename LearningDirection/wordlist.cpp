#include "wordlist.h"

WordList::WordList()
{
    MAX_WORD_ID = getMaxID();
}

WordList::~WordList()
{

}

int WordList::vichislitPoID(int ID){

    if(wordList.isEmpty()) return -1;

    for (int i = 0; i < wordList.size(); ++i){
        if(wordList.at(i).getID() == ID)
            return i;
    }
    return -1;
}

int WordList::contains(QString word){
    if(wordList.isEmpty())
        return -1;
    for(int i = 0; i < wordList.size(); ++i){
        if(*(wordList[i].getWord()) == word)
            return i;
    }
    return -1;
}
void WordList::addFastWord(int currentVocab_ID, QString word, QStringList translation, QString transcription){

    wordList.append(Word(getMaxID(), word, translation, transcription, currentVocab_ID ));
}//temporary
void WordList::setTemporallyDeleted(int word_ID){
    int index = vichislitPoID(word_ID);
    if (index != -1 && index < wordList.size() && ACTIVE_VOCABULARY_ID != -1){
        wordList[index].deleteFromVocabulary(ACTIVE_VOCABULARY_ID);
    }
}

void WordList::setActive(int vocab_ID, int word_ID){
    int index = vichislitPoID(word_ID);
    if (index != -1 && index < wordList.size()){
        wordList[index].addToVocabulary(vocab_ID);
    }
}

void WordList::permanentDeletion(int ID){
    int index = vichislitPoID(ID);
    if (index != -1 && index < wordList.size())
        wordList.removeAt(index);
}

QDataStream& operator <<(QDataStream& out, const WordList& wList){
    return out << wList.wordList;
}
QDataStream& operator >>(QDataStream& in, WordList& wList){
    return in >> wList.wordList;
}
