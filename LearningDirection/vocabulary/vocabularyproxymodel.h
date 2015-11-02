#ifndef VOCABULARYPROXYMODEL_H
#define VOCABULARYPROXYMODEL_H
//#include "vocabulary/vocabularymodel.h"
#include "vocabularymodel.h"
#include <QSortFilterProxyModel>
#include <QVariant>
class VocabularyProxyModel: public QSortFilterProxyModel
{
private:
   QModelIndex getModelIndex(int ID);

public:  
  VocabularyProxyModel();
  ~VocabularyProxyModel();

protected:
  bool filterAcceptsRow ( int source_row, const QModelIndex & source_parent ) const;
  bool filterAcceptsColumn(int source_column, const QModelIndex &source_parent) const;
  //QVariant headerData(int section, Qt::Orientation orientation, int role) const;
};

#endif // VOCABULARYPROXYMODEL_H
