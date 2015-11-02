#ifndef WORDSORTFILTERMODEL_H
#define WORDSORTFILTERMODEL_H

#include <QSortFilterProxyModel>
#include <QVariant>
#include <QStringList>
#include "wordmodel.h"
class WordProxyModel: public QSortFilterProxyModel
{
public:
    QList<int> StringToIntList(QString& sourceString) const;
//    QHash<int, QByteArray> roleNames() const;
    WordProxyModel();
    ~WordProxyModel();

    enum class WordProxyModelMode{
        ShowDeleted = 0,
        HideDeleted = 1
    };
protected:

    bool filterAcceptsRow ( int source_row, const QModelIndex & source_parent ) const;
    bool filterAcceptsColumn(int source_column, const QModelIndex &source_parent) const;
   // QVariant headerData(int section, Qt::Orientation orientation, int role) const;
private:
    WordProxyModelMode mode = WordProxyModelMode::HideDeleted;
    //int vocabFilter = -1;
    //int getVocabFilter() const;
public slots:
    void setVocabularyIDFilter(int keyID);
    void setMode(WordProxyModelMode m){mode = m;}
};
#endif // WORDSORTFILTERMODEL_H
