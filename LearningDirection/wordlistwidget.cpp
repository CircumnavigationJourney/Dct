#include "wordlistwidget.h"
#include "ui_wordlistwidget.h"

WordListWidget::WordListWidget(QSortFilterProxyModel *model, QWidget *parent) :
    wordListModel(model),
    QWidget(parent),
    ui(new Ui::WordListWidget)
{
    ui->setupUi(this);
    ui->tableView->setModel(wordListModel);
    dialog = new WordDialog;
}

WordListWidget::~WordListWidget()
{
    delete ui;
}

void WordListWidget::setModel(QSortFilterProxyModel *model){
    wordListModel = model;
    ui->tableView->setModel(wordListModel);
}

void WordListWidget::on_Add_New_clicked()
{
    dialog->show();
}

void WordListWidget::on_deleteWord_clicked()
{
    QModelIndex index = ui->tableView->currentIndex();
    qDebug() << index.row() << " column : " << index.column();
    wordListModel->setData(index, int(),  WordModel_Roles::WMR_Delete);
    wordListModel->invalidate();

}
