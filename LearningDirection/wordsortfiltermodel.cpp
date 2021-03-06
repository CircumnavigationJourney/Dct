#include "wordsortfiltermodel.h"

WordProxyModel::WordProxyModel(){}
WordProxyModel::~WordProxyModel(){}
bool WordProxyModel::filterAcceptsRow ( int source_row, const QModelIndex & source_parent ) const{
    int vocabFilter = sourceModel()->data(QModelIndex(), WordModel_Roles::WMR_ActiveVocabulary).toInt();
    if(vocabFilter != -1){
        //active vocabularies list
        QAbstractItemModel *SM = sourceModel();
        const QList<QVariant> activeVocabList = SM->data(SM->index(source_row, WordModel_Columns::WM_ActiveInVocabularyIndexList, source_parent)).toList();
        if(!activeVocabList.isEmpty()){
            for(int i = 0; i < activeVocabList.size(); ++i){
                if(activeVocabList.at(i).toInt() == vocabFilter){
                    return true;
                }
            }
        }
        if(mode == WordProxyModelMode::ShowDeleted){
            //deleted vocabularies list
            // QString deletedVocabList = (SM->data(SM->index(source_row, WordModel_Columns::WM_DeletedInVocabularyIndexList, source_parent))).toString();
            const QList<QVariant> delVocabList = SM->data(SM->index(source_row, WordModel_Columns::WM_DeletedInVocabularyIndexList, source_parent)).toList();
            if(delVocabList.isEmpty()){
                return false;
            } else if(delVocabList.contains(vocabFilter))
                return true;
        }
        return false;
    }
    return false;

}

bool WordProxyModel::filterAcceptsColumn(int source_column, const QModelIndex &source_parent) const{
    Q_UNUSED(source_parent)
    if(source_column == WordModel_Columns::WM_Word ||
            source_column == WordModel_Columns::WM_Transcription ||
            source_column == WordModel_Columns::WM_FastTranslation)
        return true;
    else return false;
}


//QHash<int, QByteArray> LearningDirectionModel::roleNames() const
//{
//    QHash<int, QByteArray> roles;
//    roles[LDMroleWord] = "word";
//    roles[LDMroleTranscription] = "transcription";
//    roles[LDMroleFastTranslation] = "translation";

//    return roles;
//}

QList<int> WordProxyModel::StringToIntList(QString & sourceString) const{
    QList<int> targetList;
    if (sourceString.isEmpty()) return targetList;
    QStringList temp = sourceString.split(";");
    for (int i = 0; i < temp.size(); ++i){
        targetList.append(temp.at(i).toInt());
    }
    return targetList;
}
void WordProxyModel::setVocabularyIDFilter(int keyID) {
    sourceModel()->setData(QModelIndex(), keyID, WordModel_Roles::WMR_ActiveVocabulary);
    this->invalidate();
}

//int WordProxyModel::getVocabFilter()  {
//    vocabFilter = sourceModel()->data(QModelIndex(), WordModel_Roles::WMR_ActiveVocabulary).toInt();
//    return vocabFilter;
//}
