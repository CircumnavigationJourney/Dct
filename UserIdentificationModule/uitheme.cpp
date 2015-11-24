#include "uitheme.h"

UITheme::UITheme()
{

}

UITheme::~UITheme()
{

}

QDataStream& operator<<(QDataStream& out, const UITheme& theme){

    return out << theme.backgroundColor
               << theme.errorColor
               << theme.higlightColor
               << theme.mainColor
               << theme.nearBackgroundColor;
}
QDataStream& operator>>(QDataStream& in, UITheme& theme){

    return in >> theme.backgroundColor
              >> theme.errorColor
              >> theme.higlightColor
              >> theme.mainColor
              >> theme.nearBackgroundColor;
}
