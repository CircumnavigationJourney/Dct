#ifndef VOCABULARYDIALOG_H
#define VOCABULARYDIALOG_H

#include <QWidget>
#include <QDebug>
#include <QDialog>

namespace Ui {
class VocabularyDialog;
}

class VocabularyDialog : public QDialog
{
    Q_OBJECT

public:
    enum Flag{
      NewVocabulary = 1,
        OldVocabulary
    };
    void setFlag(int newFlag);

    VocabularyDialog(QWidget *parent = 0);
    ~VocabularyDialog();
    void setDialogData(QString name);
signals:
    void setNewData(QString, int);
private slots:
    void on_okButton_clicked();

    void on_cancelButton_clicked();

private:
    int flag = Flag::OldVocabulary;
    Ui::VocabularyDialog *ui;
};

#endif // VOCABULARYDIALOG_H
