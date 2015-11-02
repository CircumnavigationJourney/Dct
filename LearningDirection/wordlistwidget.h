#ifndef WORDLISTWIDGET_H
#define WORDLISTWIDGET_H

#include <QWidget>
#include <QAbstractItemModel>
#include "wordsortfiltermodel.h"
#include "worddialog.h"
namespace Ui {
class WordListWidget;
}

class WordListWidget : public QWidget
{
    Q_OBJECT

public:
    explicit WordListWidget(QSortFilterProxyModel *model, QWidget *parent = 0);
    ~WordListWidget();
    void setModel(QSortFilterProxyModel *model);
private slots:
    void on_Add_New_clicked();
    void on_deleteWord_clicked();

private:
    QSortFilterProxyModel *wordListModel;
    WordDialog *dialog;
    Ui::WordListWidget *ui;
};

#endif // WORDLISTWIDGET_H
