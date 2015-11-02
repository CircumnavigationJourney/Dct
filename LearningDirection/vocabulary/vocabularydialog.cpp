#include "vocabularydialog.h"
#include "ui_vocabularydialog.h"

VocabularyDialog::VocabularyDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::VocabularyDialog)
{
    ui->setupUi(this);
    qDebug() << "Dialog Created";
   // setWindowModality(Qt::WindowModal);
    setModal(true);
}

VocabularyDialog::~VocabularyDialog()
{
    delete ui;
}
void VocabularyDialog::setDialogData(QString name){

    ui->nameLine->setText(name);
}

void VocabularyDialog::on_okButton_clicked()
{
    emit setNewData(ui->nameLine->text(), flag);
    flag = Flag::OldVocabulary;
    this->close();
}

void VocabularyDialog::on_cancelButton_clicked()
{
    this->close();
}
void VocabularyDialog::setFlag(int newFlag){
    flag = newFlag;
    ui->nameLine->clear();

}
