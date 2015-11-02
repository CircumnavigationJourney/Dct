#include "learningdirection.h"
//#define TEST_LD
LearningDirection::LearningDirection(QString learningLang, QString knownLang):
    learningLanguageISOCode(learningLang),
    knownLanguageISOCode(knownLang)
{

    vocabListData = new VocabularyList;
    wordListData = new WordList;
    LoadLearningDirectionData();

    vocabModel = new VocabularyModel;
    vocabModel->setDataSource(vocabListData);
    vocabProxyModel = new VocabularyProxyModel;
    vocabProxyModel->setSourceModel(vocabModel);


    wordModel = new WordModel;
    wordModel->setDataSource(wordListData);
    wordProxyModel = new WordProxyModel;
    wordProxyModel->setSourceModel(wordModel);
}

LearningDirection::~LearningDirection()
{

}
QString LearningDirection::getName(){
    //TODO check if iso code is not correct
    QString name(GTLangCode::langName(knownLanguageISOCode) + "-" + GTLangCode::langName(learningLanguageISOCode));

    qDebug() << knownLanguageISOCode << "-" << learningLanguageISOCode <<"\n" << name;
    return name;
}
bool LearningDirection::LoadLearningDirectionData(){
    //TODO loading from file
    vocabListData->createNewVocabulary("Word Dicty");
    vocabListData->createNewVocabulary("Pretty Dicty");
    vocabListData->createNewVocabulary("Job Dicty");
    vocabListData->createNewVocabulary("Unknown Dicty");
    vocabListData->createNewVocabulary("Deleted Dicty");
    vocabListData->setStatusDeleted(vocabListData->getMaxID()-1);
    vocabListData->createNewVocabulary("Word Dicty");

    QStringList trans = {"слово", "слову"};
    QStringList trans1 = {"красавчик", "красивая"};
    QStringList trans3 = {"работа", "занятие"};

    for (int i = 0; i < 1000000; i += 3){
        wordListData->addFastWord(1, "word" + QString::number(i), trans, "wɜːd");
        wordListData->addFastWord(2, "pretty" + QString::number(i+1) , trans1, "ˈprɪti");
        wordListData->addFastWord(3, "job" + QString::number(i+2), trans3, "[ʤɑb]");
    }
    return true;
}
#ifdef TEST_LD

void LearningDirection::oldDicty(){
//Для корректной работы строки словаря нужно сохранить в UTF-8
  QString *oldadress = new QString("C:\\Users\\4294967295\\Desktop\\english\\english\\Dictionary\\Files\\");
  QString *Dyctpath = new QString("Dct");
  QStringList *DyctList;
  QString *L1 = new QString("L1.txt");
  QString *L2 = new QString("L2.txt");
  QString *TL1 = new QString("TL1.txt");
  QStringList *List_L1 ;
  QStringList *List_L2 ;
  QList<QStringList> *List_list_TL1;
  QTextCodec *codec (QTextCodec::codecForName("UTF-8"));

  QFile *infile = new QFile(*oldadress + *Dyctpath + QString(".txt"));
  QTextStream in(infile);
  in.setCodec(codec);
  //имена словарей
  if (infile->open(QIODevice::ReadOnly)){
    QString temp = in.readAll();
    DyctList = new QStringList(temp.split("\r\n"));
    }

  //DyctList->replaceInStrings(QRegExp("\n|\r\n|\r"), "");
  infile->close();
  for (int i = 0; i < DyctList->size(); ++i){
    qDebug() << DyctList->at(i);

    }

  //загрузка слов из словарей
  words << Word();
  for (int i = 0; i < DyctList->size(); ++i){
      QString path;
      if (DyctList->at(i).isEmpty()) break;
      qDebug() << QString("DICTY NAME ==============") << DyctList->at(i);
//L1
      path = QString(*oldadress + *Dyctpath + QString("\\")  + DyctList->at(i) + QString("\\") + *L1);
      infile->setFileName(path);
      if (infile->open(QIODevice::ReadOnly)){
          in.setDevice(infile);
          QString temp = in.readAll();
          infile->close();
          List_L1 = new QStringList(temp.split("\r\n"));
        }
      qDebug() <<"problem not L1";
//L2
      path = QString(*oldadress + *Dyctpath + QString("\\")  + DyctList->at(i) + QString("\\") + *L2);
      infile->setFileName(path);
      if (infile->open(QIODevice::ReadOnly)){
          in.setDevice(infile);
          QString temp = in.readAll();
          infile->close();
          List_L2 = new QStringList(temp.split("\r\n"));
        }
      qDebug() <<"problem not L2";
//TL1 привести к списку из стринглистов
      path = QString(*oldadress + *Dyctpath + QString("\\")  + DyctList->at(i) + QString("\\") + *TL1);
      infile->setFileName(path);
      if (infile->open(QIODevice::ReadOnly)){
          in.setDevice(infile);
          List_list_TL1 = new QList<QStringList>;
          while(!in.atEnd()){
              QString temp = in.readLine();
              temp.replace(QRegExp("\n|\r\n|\r"), "");
              temp = temp.toUtf8();
              QStringList templist = temp.split(QString("※").toUtf8());
              List_list_TL1->append(templist);
              in.readLine();
            }
          infile->close();
          for (int i = 0; i < List_list_TL1->size(); ++i)
            qDebug() << List_list_TL1->at(i);
        }
      qDebug() <<"problem not TL1";


      //создаем слово и добавляем

      for (int k = 0; k < List_L1->size()-1; ++k){

          QStringList translations;
          if (!List_L1->at(k).isEmpty())
            for (int j = 0; j < List_list_TL1->at(k).size(); ++j)
              {
                if (!List_list_TL1->at(k).at(j).isEmpty())
                  translations.append(List_L2->at(List_list_TL1->at(k).at(j).toInt() - 1));
              }
          qDebug() << List_L1->at(k) << QString("\t\t") << translations;

          setWord(List_L1->at(k), translations, DyctList->at(i), QString(""), QString(""), false);
        }

      //очистка временных переменных
      delete List_L1;
      delete List_L2;
      delete List_list_TL1;
    }
  delete DyctList;
  delete oldadress;
  delete Dyctpath;
  delete L1;
  delete L2;
  delete TL1;
  delete infile;
}
}
#endif
