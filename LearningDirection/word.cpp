#include "word.h"

Word::Word(int id, QString learnigLangWord, QStringList ft, QString transcrip, int vocabID):
    ID(id),
    word(learnigLangWord),
    transcription(transcrip)

{
    activeInVocabularyList.append(vocabID);
    translations.setFastTranslations(ft);
    creationTime = QDateTime::currentDateTime();
}

Word::~Word()
{

}

QDataStream& operator<< (QDataStream& out, const Word& word){
    return out << word.word
               << word.translations
               << word.transcription
               << word.activeInVocabularyList
               << word.deletedInVocabularyList
               << word.creationTime
                  /*                  << word.remData
                                                      << word.wordTestsData
                                                      << word.wordStatisticsData*/;
}
QDataStream& operator>> (QDataStream& in, Word& word){
    return in >> word.word
              >> word.translations
              >> word.transcription
              >> word.activeInVocabularyList
              >> word.deletedInVocabularyList
              >> word.creationTime
                 /*                  >> word.remData
                                                         >> word.wordTestsData
                                                         >> word.wordStatisticsData*/;
}

bool Word::operator ==(const Word& w){

    qDebug() << QString(*(w.getWord()));//

    return (*(w.getWord()) == *(this->getWord())) ? true : false;
}
const QList<QVariant>* Word::getActiveInVocabularyList() const {
    return &activeInVocabularyList;
}
const QList<QVariant>* Word::getDeletedInVocabularyList() const {
    return &deletedInVocabularyList;
}

//QString Word::IntListToString(const QList<int> &data) const {
//    //for getting data through QVariant in view
//    if (data.isEmpty()) return QString();
//    QString temp;
//    int i = 0;
//    while(i < data.size()-1)
//    {
//        temp.append(QString::number(data.at(i)));
//        temp.append(";");
//        i++;
//    }
//    temp.append(QString::number(data.at(i)));
//    return temp;
//}

void Word::addToVocabulary(int vocabularyID){
    for(int i = 0; i < activeInVocabularyList.size(); ++i){
        if(activeInVocabularyList.at(i) == vocabularyID){
            return;
        }
    }
//    if (!activeInVocabularyList.contains(vocabularyID))
        activeInVocabularyList.push_back((int)vocabularyID);
}

void Word::deleteFromVocabulary(int vocabularyID){
    if (deletedInVocabularyList.contains(vocabularyID))
        return;

    if(activeInVocabularyList.contains(vocabularyID)){
        int index;
        index = activeInVocabularyList.indexOf(vocabularyID);
        activeInVocabularyList.removeAt(index);
    }
    deletedInVocabularyList.append(vocabularyID);

}
