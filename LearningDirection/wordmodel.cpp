#include "wordmodel.h"


WordModel::WordModel() : QAbstractItemModel(0)
{

}


int WordModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return pointToWordListData->size();
}

int WordModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return WordModel_COLUMN_COUNT;
}

QVariant WordModel::data(const QModelIndex &index, int role) const
{
    if(role == WordModel_Roles::WMR_ActiveVocabulary)
        return pointToWordListData->getVocabularyFilter();

    if(index.column() < 0 ||
            columnCount() <= index.column() ||
            index.row() < 0 ||
            rowCount() <= index.row())
    {
        //qDebug() << "Warning: " << index.row() << ", " << index.column();
        return QVariant();
    }

    // Nominal case
    //     qDebug() << "LearningDirectionModel::data: " << index.column() << "; " << index.row();
    if(role == Qt::DisplayRole){
        switch(index.column())
        {
        case WM_Word:/*qDebug() << *((*directionData)[index.row()].getWord());*/
            return *((*pointToWordListData)[index.row()].getWord());
        case WM_Transcription: /*qDebug() << *((*directionData)[index.row()].getIPATranscription());*/
            return *((*pointToWordListData)[index.row()].getIPATranscription());
        case WM_FastTranslation: /*qDebug() << ((*directionData)[index.row()].getFastTranslation())->join(", ");*/
            return (*(*pointToWordListData)[index.row()].getFastTranslation()).join(", ");
        case WM_ActiveInVocabularyIndexList:
            return *((*pointToWordListData)[index.row()].getActiveInVocabularyList());
        case WM_DeletedInVocabularyIndexList:
            return *((*pointToWordListData)[index.row()].getDeletedInVocabularyList());
        case WM_ID:
            return (*pointToWordListData)[index.row()].getID();
        case WM_CreationDate:
            return (*pointToWordListData)[index.row()].getCreationDate();

        }
    }
    switch (role){
    case WordModel_Roles::WMR_Word:
        return *((*pointToWordListData)[index.row()].getWord());
    case WordModel_Roles::WMR_Transcription:
        return *((*pointToWordListData)[index.row()].getIPATranscription());
    case WordModel_Roles::WMR_FastTranslation:
        return (*(*pointToWordListData)[index.row()].getFastTranslation()).join(", ");
    case WordModel_Roles::WMR_ID:
        (*pointToWordListData)[index.row()].getID();
    }
    return QVariant();
}

bool WordModel::setData(const QModelIndex &index, const QVariant &value, int role){
    if(role == WordModel_Roles::WMR_ActiveVocabulary){
        pointToWordListData->setVocabularyFilter(value.toInt());
    return true;
    }
    if(role == WordModel_Roles::WMR_Delete ){
        if (!index.isValid()) return false;

        int id = (*pointToWordListData)[index.row()].getID();
        //qDebug() << id << "for Deletion";
        //pointToWordListData->permanentDeletion(id);
        pointToWordListData->setTemporallyDeleted(id);
        return true;
    }
    return false;
//    if(!index.isValid()) return false;

//    switch(role){

//    case WordModel_Roles::WMR_Delete:
//        (*pointToWordListData)[index.row()].deleteFromVocabulary(value.toInt()); break;
////     case WordModel_Roles::WMR_NEW:
////        pointToWordListData->addFastWord(QString("testWord"),)
//    }
//    return true;
}

QHash<int, QByteArray> WordModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[WordModel_Roles::WMR_Word] = "word";
    roles[WordModel_Roles::WMR_Transcription] = "transcription";
    roles[WordModel_Roles::WMR_FastTranslation] = "translation";

    return roles;
}
void WordModel::theDataChanged()
{
    //TODO
}
//***************************************************************************************************************************************
QModelIndex WordModel::index(int row, int column, const QModelIndex &parent) const
{
    if( parent.isValid() ||
            column > WordModel_COLUMN_COUNT || column < 0 ||
            row >= pointToWordListData->size() || row < 0) return QModelIndex();
    return createIndex(row, column);
}
//***************************************************************************************************************************************
QModelIndex WordModel::parent(const QModelIndex &/*child*/) const
{
    return QModelIndex();
}

QVariantMap WordModel::get(int idx) const {
    QVariantMap map;
    foreach(int k, roleNames().keys()) {
        map[roleNames().value(k)] = data(index(idx, 0), k);
    }
    return map;
}
