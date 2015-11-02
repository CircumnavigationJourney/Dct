#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    wordList = new WordList;
    QStringList trans = {"слово", "слову"};
    QStringList trans1 = {"красавчик", "красивая"};
    for (int i = 0; i < 1000; ++i)
    wordList->addFastWord(1, "word", trans, "wɜːd");
    for (int i = 0; i < 1000; ++i)
    wordList->addFastWord(2, "pretty", trans1, "ˈprɪti");


    wordModel = new WordModel;
    wordModel->setDataSource(wordList);
    wordProxy = new WordProxyModel;
     wordProxy->setVocabularyIDFilter(1);
    wordProxy->setSourceModel(wordModel);
    ui->tableView_2->setModel(wordProxy);
    ui->tableView->setModel(wordModel);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    wordProxy->setVocabularyIDFilter(2);
    wordProxy->setSourceModel(wordModel);

}
