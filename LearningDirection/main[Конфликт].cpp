#include <QApplication>
#include <QtQml>
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQuickWindow>

#include "applicationwindow_test.h"
//Ice-Ice Dicty

//#define QML_VIEW
int main(int argc, char *argv[])
{

    QApplication a(argc, argv);
#ifndef QML_VIEW
    ApplicationWindow_test w;
    w.show();
#endif
#ifdef QML_VIEW
    // Data :
    WordList *wordList;
    WordModel *wordModel;
    WordProxyModel *wordProxy;

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
    //wordProxy->setVocabularyIDFilter(1);
    wordProxy->setSourceModel(wordModel);



 // UI :
    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty("LearningDirectionModel", wordProxy);

    engine.load(QUrl("qrc:/main.qml"));
    QList<QObject*> temp = engine.rootObjects();
    QObject *topLevel = temp.value(0);
    QQuickWindow *window = qobject_cast<QQuickWindow *>(topLevel);
    if ( !window ) {
        qWarning("Error: Your root item has to be a Window.");
        return -1;


 }

    // Display the main.qml, which show the model:
    //topLevel->setProperty("learningDirectionName", experimental.getName());
    window->show();
#endif
    return a.exec();
}
