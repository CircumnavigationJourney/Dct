#include "worddialog.h"
#include "ui_worddialog.h"

WordDialog::WordDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::WordDialog)
{
    ui->setupUi(this);
    setModal(true);
    YAPI = new YandexDictyonaryAPI;

}

WordDialog::~WordDialog()
{
    delete ui;
}

void WordDialog::on_searchButton_clicked()
{
QString reply = YAPI->translate(ui->word->text(), "en", "ru");
    ui->textBrowser->setText(reply);
}
