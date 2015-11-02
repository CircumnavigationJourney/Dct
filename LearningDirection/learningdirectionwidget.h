#ifndef LEARNINGDIRECTIONWIDGET_H
#define LEARNINGDIRECTIONWIDGET_H

#include <QWidget>
#include "learningdirection.h"
#include "wordlistwidget.h"
#include "vocabulary/vocabularywidget.h"

namespace Ui {
class LearningDirectionWidget;
}

class LearningDirectionWidget : public QWidget
{
    Q_OBJECT
private:
    QSortFilterProxyModel *wordProxy;
    QSortFilterProxyModel *vocabProxy;
    Ui::LearningDirectionWidget *ui;

public:
    WordListWidget *wordListWidget;
    VocabularyWidget *vocabListWidget;
    void connector();
    explicit LearningDirectionWidget(QSortFilterProxyModel *wordModel, QSortFilterProxyModel *vocabModel, QWidget *parent = 0);
    ~LearningDirectionWidget();

private slots:
    void setVocFilter(int ID);
};

#endif // LEARNINGDIRECTIONWIDGET_H
