#include "vocabularyproxymodel.h"

VocabularyProxyModel::VocabularyProxyModel()
{

}

VocabularyProxyModel::~VocabularyProxyModel()
{

}
bool VocabularyProxyModel::filterAcceptsColumn(int source_column, const QModelIndex &source_parent) const{
    Q_UNUSED(source_parent);
    //if(source_column == 0)
    return true;
}
bool VocabularyProxyModel::filterAcceptsRow ( int source_row, const QModelIndex & source_parent ) const{
    int mode = sourceModel()->data(QModelIndex(), static_cast<int>(VocabularyModel::Roles::Mode)).toInt();
    if(mode == static_cast<int>(VocabularyModel::Mode::HideDeleted)){

        //qDebug() << source_row << " " << static_cast<int>(sourceModel()->data(sourceModel()->index(source_row, 2, source_parent),static_cast<int>(VocabularyModel::Roles::Status)).toInt());
        return  static_cast<int>(sourceModel()->data(sourceModel()->index(source_row, 0, source_parent),static_cast<int>(VocabularyModel::Roles::Status)).toInt()) == static_cast<int>(Vocabulary::VocabularyStatus::ACTIVE) ? true : false;
    }
    //if mode == show deleted
    else return true;
}
//QVariant VocabularyProxyModel::headerData(int section, Qt::Orientation orientation, int role) const {
//    return QVariant(); //for test
//}

//qDebug() << "status report : " << sourceModel()->data(sourceModel()->index(source_row, 0, source_parent)),
//                                static_cast<int>(VocabularyModel::VocabularyModel_Roles::VocStatus);
//bool stat = static_cast<int>(sourceModel()->data(sourceModel()->index(source_row, 0, source_parent)),
//                       static_cast<int>(VocabularyModel::VocabularyModel_Roles::VocStatus)) == static_cast<int>(Vocabulary::VocabularyStatus::ACTIVE)
//        ? true : false;
//qDebug() << stat;
//return stat;
QModelIndex VocabularyProxyModel::getModelIndex(int ID){

    for (int i = 0; i < sourceModel()->rowCount(); ++i){
       // qDebug() << "check Voc ID : " << sourceModel()->data(sourceModel()->index(i, 0), static_cast<int>(VocabularyModel::Roles::ID)).toInt()  << " == " << ID;
        if(sourceModel()->data(sourceModel()->index(i, 0), static_cast<int>(VocabularyModel::Roles::ID)).toInt() == ID)

            return sourceModel()->index(i, static_cast<int>(VocabularyModel::ColumnNames::Name));
    }
    return QModelIndex();
}
