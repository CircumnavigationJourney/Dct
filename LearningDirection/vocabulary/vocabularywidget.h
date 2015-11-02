#ifndef VOCABULARYWIDGET_H
#define VOCABULARYWIDGET_H

#include <QWidget>
//#include "vocabulary/vocabularyproxymodel.h"
#include "vocabularyproxymodel.h"
#include "vocabularydialog.h"

namespace Ui {
class VocabularyWidget;
}

class VocabularyWidget : public QWidget
{
    Q_OBJECT
    QSortFilterProxyModel *vocProxy;

public:
    //void setActiveVocabulary(int ID);
    void connector();
    void setModel(QSortFilterProxyModel *model);

    explicit VocabularyWidget(QSortFilterProxyModel *model, QWidget *parent = 0);
    ~VocabularyWidget();
signals:
    void CurrentVocabID(int);
public slots:
    void getCurrentVocabID(QModelIndex index);
private slots:

    void on_checkBox_clicked();
    void on_Delete_clicked();
    void on_Recover_clicked();
    void on_addNew_clicked();
    void setNewData(QString , int);
    void on_Rename_clicked();

private:
    QModelIndex currentActiveVocabularyIndex;
    VocabularyDialog *dialog;
    Ui::VocabularyWidget *ui;

    //QModelIndex getModelIndex(int ID);




};

#endif // VOCABULARYWIDGET_H
