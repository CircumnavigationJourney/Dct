#ifndef VOCABULARYDELEGATE_H
#define VOCABULARYDELEGATE_H

#include <QItemDelegate>
#include <QObject>
#include <QModelIndex>
#include "vocabularydialog.h"
class VocabularyDelegate : public QItemDelegate
{
    Q_OBJECT
private:

public:
    explicit VocabularyDelegate(QObject *parent = 0);
    ~VocabularyDelegate();
    QWidget * createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const;
    void setEditorData(QWidget *editor, const QModelIndex &index) const;
    void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const;
    void updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const;
};

#endif // VOCABULARYDELEGATE_H
