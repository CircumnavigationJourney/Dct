#include "vocabularydelegate.h"

VocabularyDelegate::VocabularyDelegate(QObject *parent)
{
    Q_UNUSED(parent);
    qDebug() << "Voc Delegate Created";

}

VocabularyDelegate::~VocabularyDelegate()
{

}

QWidget * VocabularyDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const{
    //Q_UNUSED(parent);
    Q_UNUSED(option);
    Q_UNUSED(index);
   VocabularyDialog *dialog = new VocabularyDialog;
    return dialog;
}
void VocabularyDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const{
    VocabularyDialog * vocDialog = reinterpret_cast<VocabularyDialog*>(editor);
    vocDialog->setDialogData(index.data().toString());

}
void VocabularyDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const{


}
void VocabularyDelegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const{


}
