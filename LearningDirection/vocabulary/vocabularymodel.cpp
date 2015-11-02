#include "vocabularymodel.h"


VocabularyModel::VocabularyModel() : QAbstractItemModel(0)
{

}
void VocabularyModel::setDataSource(VocabularyList *newVocListData){
    //qDebug() << "vocabulary set Data source";
    PointToVocListData = newVocListData;
}

int VocabularyModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return PointToVocListData->size();
}

int VocabularyModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return VocModel_COLUMN_COUNT;
}

QVariant VocabularyModel::data(const QModelIndex &index, int role) const
{
    if(role == static_cast<int>(VocabularyModel::Roles::Mode))
        return mode;
    if(role == static_cast<int>(VocabularyModel::Roles::LastActiveVocabularyID))
        return PointToVocListData->getLastActiveVocabularyID();
    //    if(role == static_cast<int>(VocabularyModel::Roles::GetModelIndex)){
    //        for (int i = 0; i < sourceModel()->rowCount(); ++i){
    //            qDebug() << "check Voc ID : " << sourceModel()->data(sourceModel()->index(i, 0), static_cast<int>(VocabularyModel::Roles::ID)).toInt()  << " == " << ID;
    //            if(sourceModel()->data(sourceModel()->index(i, 0), static_cast<int>(VocabularyModel::Roles::ID)).toInt() == ID)

    //                return sourceModel()->index(i, static_cast<int>(VocabularyModel::ColumnNames::Name));
    //        }
    //        return QModelIndex();

    //    }

    if((index.column() < 0 ||
            columnCount() <= index.column() ||
            index.row() < 0 ||
            rowCount() <= index.row()) && (role != static_cast<int>(VocabularyModel::Roles::Mode) ||
                                                                    role != static_cast<int>(VocabularyModel::Roles::LastActiveVocabularyID)))
    {
        qDebug() << "Warning: " << index.row() << ", " << index.column();
        return QVariant();
    }
    switch (role){
    case Qt::DisplayRole:
        return *((*PointToVocListData)[index.row()].getName());
    case static_cast<int>(Roles::ID):
        return (*PointToVocListData)[index.row()].getID();
    case static_cast<int>(Roles::Status):
        return (*PointToVocListData)[index.row()].getStatus();
    }
#ifdef TEST_VOCABULARY_MODEL
    if(role == Qt::ForegroundRole){

        if((*PointToVocListData)[index.row()].getStatus() == static_cast<int>(Vocabulary::VocabularyStatus::DELETED))
            return QBrush(Qt::red);
    }
#endif
    return QVariant();
}

QHash<int, QByteArray> VocabularyModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[static_cast<int>(VocabularyModel::ColumnNames::Name)] = "name";
    return roles;
}
void VocabularyModel::theDataChanged()
{
    //TODO
}
//***************************************************************************************************************************************
QModelIndex VocabularyModel::index(int row, int column, const QModelIndex &parent) const
{
    if( parent.isValid() ||
            column > VocModel_COLUMN_COUNT || column < 0 ||
            row >= PointToVocListData->size() || row < 0) return QModelIndex();
    return createIndex(row, column);
}
//***************************************************************************************************************************************
QModelIndex VocabularyModel::parent(const QModelIndex &/*child*/) const
{
    return QModelIndex();
}

QVariantMap VocabularyModel::get(int idx) const {
    QVariantMap map;
    foreach(int k, roleNames().keys()) {
        map[roleNames().value(k)] = data(index(idx, 0), k);
    }
    return map;
}
bool VocabularyModel::setData(const QModelIndex &index,
                              const QVariant &value, int role)
{
    if(role == static_cast<int>(VocabularyModel::Roles::Mode))
        mode = value.toInt();
    if (index.isValid() && !value.toString().isEmpty()) {
        switch (role){
        case static_cast<int> (VocabularyModel::Roles::Status):
            (*PointToVocListData)[index.row()].setStatus(value.toInt()); emit dataChanged(index, index); return true;
        case static_cast<int> (VocabularyModel::Roles::Name):
            (*PointToVocListData)[index.row()].setName(value.toString()); emit dataChanged(index, index); return true;
        case static_cast<int> (VocabularyModel::Roles::LastActiveVocabularyID):
            PointToVocListData->setLastActiveVocabularyID((*PointToVocListData)[index.row()].getID());
            emit dataChanged(index, index); return true;
        }
    }
    //add new item
    //index can be invalid
    if (role == static_cast<int> (VocabularyModel::Roles::NewVocCreation)){
        PointToVocListData->createNewVocabulary(value.toString());
        emit dataChanged(index, index);
        return true;
    }

    return false;
}
//Qt::ItemFlags VocabularyModel::flags(const QModelIndex &index){

//}
//QVariant VocabularyModel::headerData(int section, Qt::Orientation orientation, int role) {

//}
//bool VocabularyModel::setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole){

//}
