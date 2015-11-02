#include "applicationwindow_test.h"
#include "ui_applicationwindow_test.h"

ApplicationWindow_test::ApplicationWindow_test(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ApplicationWindow_test)
{

    ui->setupUi(this);
    LD = new LearningDirection("en", "ru");
    LDWidget = new LearningDirectionWidget(LD->wordProxyModel, LD->vocabProxyModel);
    //LDWidget->setLastActiveVocabularyFromSavedData(LD->getLastActiveVocabulary());
    LDWidget->connector();
    ui->tabWidget->addTab(LDWidget, tr("VocabList"));
    ui->tabWidget->removeTab(0);
    ui->tabWidget->removeTab(0);
    ui->tabWidget->removeTab(0);
    ui->label->setText(LD->getName());
    //ui->tabWidget->addTab(new GeneralTab(fileInfo), tr("General"));
//    tabWidget->addTab(new PermissionsTab(fileInfo), tr("Permissions"));
//    tabWidget->addTab(new ApplicationsTab(fileInfo), tr("Applications"));
}

ApplicationWindow_test::~ApplicationWindow_test()
{
    delete ui;
}
