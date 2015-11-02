#ifndef VOCABULARYMODEL_H
#define VOCABULARYMODEL_H


#include <QAbstractItemModel>
//#include "vocabulary/vocabularylist.h"
#include "vocabularylist.h"
#define TEST_VOCABULARY_MODEL
#ifdef TEST_VOCABULARY_MODEL
#include <QBrush>
#endif
class VocabularyModel : public QAbstractItemModel
{
    Q_OBJECT
private:
    const int VocModel_COLUMN_COUNT = 1;
    int mode = static_cast<int>(Mode::HideDeleted);
    VocabularyList *PointToVocListData;
public:
    enum class Roles {
        ID = Qt::UserRole+1,
        Name,
        Status,
        NewVocCreation,
        LastActiveVocabularyID,
        GetModelIndex,
        Mode

    };
    enum class Mode{
        ShowAll,
        HideDeleted
    };
    enum class ColumnNames{
        Name
    };
    void setDataSource(VocabularyList *newVocListData);


    explicit VocabularyModel();
    //void setData(QList<Word> *newDirectionData){ directionData = newDirectionData;}

    //Reimplement Model methods
    //*******************************************************************
    int rowCount(const QModelIndex & parent = QModelIndex()) const;
    int columnCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    QModelIndex index(int row, int column, const QModelIndex &parent = QModelIndex()) const;
    QModelIndex parent(const QModelIndex &) const;
    QHash<int, QByteArray> roleNames() const;
    bool setData(const QModelIndex &index, const QVariant &value, int role);
//    Qt::ItemFlags flags(const QModelIndex &index) const;
//    QVariant headerData(int section, Qt::Orientation orientation, int role) const;
//    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole);
    //*******************************************************************
    //access data methods using qml view
    QVariantMap get(int idx) const;

public slots:
    void theDataChanged();
};
#endif // VOCABULARYMODEL_H
