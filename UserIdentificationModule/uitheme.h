#ifndef UITHEME_H
#define UITHEME_H

#include <QDataStream>
#include <QColor>

class UITheme
{
private:
    //standard theme colors (default)
  QColor mainColor = QColor("#2196F3");
  QColor higlightColor = QColor("#2196F3");
  QColor errorColor = QColor("#F44336");
  QColor backgroundColor = QColor("#f3f3f3");
  QColor nearBackgroundColor = QColor("#42A5F5");

public:
    UITheme();
    ~UITheme();

    friend QDataStream& operator<<(QDataStream& out, const UITheme& theme);
    friend QDataStream& operator>>(QDataStream& in, UITheme& theme);
};

#endif // UITHEME_H
