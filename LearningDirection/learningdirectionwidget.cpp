#include "learningdirectionwidget.h"
#include "ui_learningdirectionwidget.h"

LearningDirectionWidget::LearningDirectionWidget(QSortFilterProxyModel *wordModel, QSortFilterProxyModel *vocabModel, QWidget *parent) :
    QWidget(parent),
    wordProxy(wordModel),
    vocabProxy(vocabModel),
    ui(new Ui::LearningDirectionWidget)
{
    ui->setupUi(this);
    wordListWidget = new WordListWidget(wordProxy);
    vocabListWidget = new VocabularyWidget (vocabProxy);
    ui->horizontalLayout->addWidget(vocabListWidget);
    ui->horizontalLayout->addWidget(wordListWidget);
    vocabListWidget->connector();
}

LearningDirectionWidget::~LearningDirectionWidget()
{
    delete ui;
}

void LearningDirectionWidget::connector(){
    connect(vocabListWidget, SIGNAL(CurrentVocabID(int)), this, SLOT(setVocFilter(int)));
}

void LearningDirectionWidget::setVocFilter(int ID){

    wordProxy->setData(QModelIndex(), ID, static_cast<int>(WordModel_Roles::WMR_ActiveVocabulary));
    wordProxy->invalidate();
}
