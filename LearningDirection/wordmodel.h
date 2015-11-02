#ifndef WORDSMODEL_H
#define WORDSMODEL_H


#include <QAbstractItemModel>
#include "wordlist.h"
//enum WordModel_Roles {
//    WM_Word = Qt::UserRole,
//    WM_Transcription,
//    WM_FastTranslation
//};
enum WordModel_Columns {
    WM_Word,
    WM_Transcription,
    WM_FastTranslation,
    WM_ActiveInVocabularyIndexList,
    WM_DeletedInVocabularyIndexList,
    WM_ID,
    WM_CreationDate

};
enum WordModel_Roles {
    WMR_Word = Qt::UserRole,
    WMR_Transcription,
    WMR_FastTranslation,
    WMR_ID,
    WMR_ActiveVocabulary,
    WMR_Delete,
    WMR_NEW,

};
class WordModel : public QAbstractItemModel
{
    Q_OBJECT
private:
    const int WordModel_COLUMN_COUNT = 7;
    WordList *pointToWordListData;
public:
    void setDataSource(WordList *newWordListData){pointToWordListData = newWordListData;}
    explicit WordModel();
    void getCurrentVocabID(int*ID);
    //Reimplement Model methods
    bool setData(const QModelIndex &index, const QVariant &value, int role);
    int rowCount(const QModelIndex & parent = QModelIndex()) const;
    int columnCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    QModelIndex index(int row, int column, const QModelIndex &parent = QModelIndex()) const;
    QModelIndex parent(const QModelIndex &) const;
    QHash<int, QByteArray> roleNames() const;
    //access data methods using qml view
    QVariantMap get(int idx) const;

public slots:
    void theDataChanged();
};

#endif // WORDSMODEL_H
