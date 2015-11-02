#include "yandexdictyonaryapi.h"

YandexDictyonaryAPI::YandexDictyonaryAPI(QObject *parent):
    QObject(parent), net(new QNetworkAccessManager(this))
{

}

YandexDictyonaryAPI::~YandexDictyonaryAPI()
{

}

QString YandexDictyonaryAPI::translate(const QString& text, const QString& sourceLang, const QString& targetLand){


    QUrl translateUrl(QString("https://dictionary.yandex.net/api/v1/dicservice.json/lookup?"));

    QUrlQuery query;
    QString langDirection = sourceLang + "-" + targetLand;
    query.addQueryItem("key", "dict.1.1.20150827T100942Z.27ea306dbe0d023c.cda16631f519de66fa670d5ea4a848f2076dda4a");
    query.addQueryItem("lang", langDirection);
    query.addQueryItem("text", text);
    query.addQueryItem("ui", "en");
    query.addQueryItem("callback", "Muja");
    translateUrl.setQuery(query);
    qDebug() << translateUrl;
    QNetworkRequest request(translateUrl);
    QNetworkReply *reply = net->get(request);
    QEventLoop waitForReply;
    connect(reply, SIGNAL(finished()), &waitForReply, SLOT(quit()));
    waitForReply.exec();
    QString replyStr = QString::fromUtf8(reply->readAll());
    qDebug() << replyStr;
    if (reply->error()) {
        qDebug() << Q_FUNC_INFO << "Network Error: " << reply->errorString();
        return QString("ERROR");
    }
    else return replyStr;
}
