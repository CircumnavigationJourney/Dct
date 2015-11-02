#include "vocabularywidget.h"
#include "ui_vocabularywidget.h"

VocabularyWidget::VocabularyWidget(QSortFilterProxyModel *model, QWidget *parent) :
    vocProxy(model),
    QWidget(parent),
    ui(new Ui::VocabularyWidget)
{
    ui->setupUi(this);
    ui->listView->setModel(model);
    dialog = new VocabularyDialog;

    //    vocList = new VocabularyList;
    //    vocList->createNewVocabulary("Биология");
    //    vocList->createNewVocabulary("word");
    //    vocList->createNewVocabulary("new");
    //    vocList->setStatusDeleted(vocList->getID(vocList->size()-1));

    //    vocModel = new VocabularyModel;
    //    vocModel->setData(vocList);
    //    vocProxy = new VocabularyProxyModel;
    //    vocProxy->setSourceModel(vocModel);

    //    ui->listView->setModel(vocProxy);
    //    ui->tableView->setModel(vocModel);

}
void VocabularyWidget::connector(){
    connect(dialog, SIGNAL(setNewData(QString, int)), this, SLOT(setNewData(QString, int)));
    connect(ui->listView, SIGNAL(clicked(QModelIndex)), this, SLOT(getCurrentVocabID(QModelIndex)));
}
//void VocabularyWidget::setActiveVocabulary(int ID){
//    QModelIndex index = vocProxy->getModelIndex(ID);

//    if(ID != -1 && index.isValid()){
//        qDebug() << "Vocabulary Activation : " << index.row();
//        ui->listView->selectionModel()->select(index, QItemSelectionModel::Select);
//    }
//}

VocabularyWidget::~VocabularyWidget()
{
    delete ui;
}

void VocabularyWidget::on_checkBox_clicked()
{

    if(ui->checkBox->isChecked()){
       // vocProxy->setMode(static_cast<int>(VocabularyProxyModel::Mode::ShowAll));
        vocProxy->setData(QModelIndex(),static_cast<int>(VocabularyModel::Mode::ShowAll), static_cast<int>(VocabularyModel::Roles::Mode));
    }
    else vocProxy->setData(QModelIndex(),static_cast<int>(VocabularyModel::Mode::HideDeleted), static_cast<int>(VocabularyModel::Roles::Mode));
        //vocProxy->setMode(static_cast<int>(VocabularyProxyModel::Mode::HideDeleted));
    vocProxy->invalidate();

}

void VocabularyWidget::on_Delete_clicked()
{
    QModelIndex index = ui->listView->currentIndex();
    vocProxy->setData(index, static_cast<int> (Vocabulary::VocabularyStatus::DELETED), static_cast<int> (VocabularyModel::Roles::Status));
    vocProxy->invalidate();
}

void VocabularyWidget::on_Recover_clicked()
{
    QModelIndex index = ui->listView->currentIndex();
    vocProxy->setData(index, static_cast<int> (Vocabulary::VocabularyStatus::ACTIVE), static_cast<int> (VocabularyModel::Roles::Status));
    vocProxy->invalidate();
}
void VocabularyWidget::setModel(QSortFilterProxyModel *model){
    //TODO its total wtf

    vocProxy = model;
    vocProxy->invalidate();
}
void VocabularyWidget::getCurrentVocabID(QModelIndex index){
    //??????????????????????????????????????????????????????????
    int ID = (vocProxy->data(index, static_cast<int>(VocabularyModel::Roles::ID))).toInt();
    currentActiveVocabularyIndex = index;
    emit CurrentVocabID(ID);
}



void VocabularyWidget::on_addNew_clicked()
{
    dialog->setFlag(VocabularyDialog::NewVocabulary);
    dialog->show();
}

void VocabularyWidget::on_Rename_clicked()
{
    dialog->setDialogData(vocProxy->data(currentActiveVocabularyIndex).toString());
    dialog->show();

}

void VocabularyWidget::setNewData(QString name, int flag){

    //qDebug() << " curr INDEX : row = "<<  currentActiveVocabularyIndex.row() << "; column = " << currentActiveVocabularyIndex.column();
    int role;

    switch (flag){
    case VocabularyDialog::Flag::NewVocabulary:
        role = static_cast<int>(VocabularyModel::Roles::NewVocCreation); break;
    case VocabularyDialog::Flag::OldVocabulary:
        role = static_cast<int>(VocabularyModel::Roles::Name); break;
    }
    //qDebug() << "role : " << role << " flag : " << flag;
    vocProxy->setData(currentActiveVocabularyIndex, name, role);
    vocProxy->invalidate();
}
//QModelIndex VocabularyWidget::getModelIndex(int ID){
//    //возможно удаленные не будут отображаться

//    for (int i = 0; i < vocProxy->rowCount(); ++i){
//        qDebug() << "check Voc ID : " <<  vocProxy->data( vocProxy->index(i, 0), static_cast<int>(VocabularyModel::Roles::ID)).toInt()  << " == " << ID;
//        if( vocProxy->data( vocProxy->index(i, 0), static_cast<int>(VocabularyModel::Roles::ID)).toInt() == ID)

//            return  vocProxy->index(i, static_cast<int>(VocabularyModel::ColumnNames::Name));
//    }
//    return QModelIndex();

//}

