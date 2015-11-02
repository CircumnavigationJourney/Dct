#ifndef YANDEXDICTYONARYAPI_H
#define YANDEXDICTYONARYAPI_H

#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QSslSocket>
#include <QUrl>
#include <QUrlQuery>
#include <QDebug>
#include <QObject>
#include <QEventLoop>
//Временно для тестирования

class YandexDictyonaryAPI : public QObject
{
    Q_OBJECT

    QNetworkAccessManager *net;
public:
    QString translate(const QString& text, const QString& sourceLang, const QString& targetLand);
    YandexDictyonaryAPI(QObject *parent = 0);
    ~YandexDictyonaryAPI();
private slots:

};

#endif // YANDEXDICTYONARYAPI_H
