#ifndef WORDDIALOG_H
#define WORDDIALOG_H

#include <QDialog>
#include "translators/yandexdictyonaryapi.h"

namespace Ui {
class WordDialog;
}

class WordDialog : public QDialog
{
    Q_OBJECT
YandexDictyonaryAPI *YAPI;
public:
    explicit WordDialog(QWidget *parent = 0);
    ~WordDialog();

private slots:
    void on_searchButton_clicked();

private:
    Ui::WordDialog *ui;
};

#endif // WORDDIALOG_H
