#ifndef LANGLISTISO
#define LANGLISTISO

#include <QString>
#include <QMap>
#include <QObject>

////////////////////////////////////////////////////////////////////////////////
// Impliments a table of ISO 639-1 language codes supported by Google Translate

namespace GTLangCode {

    static const QMap<QString, QString>& langMap();

    inline QString langName(const QString & iso639_1) {
        if (langMap().contains(iso639_1))
            return langMap()[iso639_1];
        return QString();
    }

    inline QString isoCode(const QString& languageName) {
        foreach(const QString& key, langMap().keys()){
            if (langMap()[key].compare(languageName, Qt::CaseInsensitive) == 0)
                return key;
        }
        return QString();
    }

    //////////////////////////////////////////////
    // Inizializes the langugages-code map
    // returns a reference to an initialized static map
    // created 2014/11/22

    static const QMap<QString, QString>& langMap() {

        static bool alreadyInitialized = false;
        static QMap<QString, QString> langMap;

        if (alreadyInitialized)
            return langMap;

        langMap["auto"]= QObject::tr("Auto");
        langMap["af"]=   QObject::tr("Afrikaans");
        langMap["sq"]=   QObject::tr("Albanian");
        langMap["ar"]=   QObject::tr("Arabic");
        langMap["az"]=   QObject::tr("Azerbaijani");
        langMap["eu"]=   QObject::tr("Basque");
        langMap["bn"]=   QObject::tr("Bengali");
        langMap["be"]=   QObject::tr("Belarusian");
        langMap["bg"]=   QObject::tr("Bulgarian");
        langMap["ca"]=   QObject::tr("Catalan");
        langMap["zh-CN"]=QObject::tr("Chinese Simplified");
        langMap["zh-TW"]=QObject::tr("Chinese Traditional");
        langMap["hr"]=   QObject::tr("Croatian");
        langMap["cs"]=   QObject::tr("Czech");
        langMap["da"]=   QObject::tr("Danish");
        langMap["nl"]=   QObject::tr("Dutch");
        langMap["en"]=   QObject::tr("English");
        langMap["eo"]=   QObject::tr("Esperanto");
        langMap["et"]=   QObject::tr("Estonian");
        langMap["tl"]=   QObject::tr("Filipino");
        langMap["fi"]=   QObject::tr("Finnish");
        langMap["fr"]=   QObject::tr("French");
        langMap["gl"]=   QObject::tr("Galician");
        langMap["ka"]=   QObject::tr("Georgian");
        langMap["de"]=   QObject::tr("German");
        langMap["el"]=   QObject::tr("Greek");
        langMap["gu"]=   QObject::tr("Gujarati");
        langMap["ht"]=   QObject::tr("Haitian Creole");
        langMap["iw"]=   QObject::tr("Hebrew");
        langMap["hi"]=   QObject::tr("Hindi");
        langMap["hu"]=   QObject::tr("Hungarian");
        langMap["is"]=   QObject::tr("Icelandic");
        langMap["id"]=   QObject::tr("Indonesian");
        langMap["ga"]=   QObject::tr("Irish");
        langMap["it"]=   QObject::tr("Italian");
        langMap["ja"]=   QObject::tr("Japanese");
        langMap["kn"]=   QObject::tr("Kannada");
        langMap["ko"]=   QObject::tr("Korean");
        langMap["la"]=   QObject::tr("Latin");
        langMap["lv"]=   QObject::tr("Latvian");
        langMap["lt"]=   QObject::tr("Lithuanian");
        langMap["mk"]=   QObject::tr("Macedonian");
        langMap["ms"]=   QObject::tr("Malay");
        langMap["mt"]=   QObject::tr("Maltese");
        langMap["no"]=   QObject::tr("Norwegian");
        langMap["fa"]=   QObject::tr("Persian");
        langMap["pl"]=   QObject::tr("Polish");
        langMap["pt"]=   QObject::tr("Portuguese");
        langMap["ro"]=   QObject::tr("Romanian");
        langMap["ru"]=   QObject::tr("Russian");
        langMap["sr"]=   QObject::tr("Serbian");
        langMap["sk"]=   QObject::tr("Slovak");
        langMap["sl"]=   QObject::tr("Slovenian");
        langMap["es"]=   QObject::tr("Spanish");
        langMap["sw"]=   QObject::tr("Swahili");
        langMap["sv"]=   QObject::tr("Swedish");
        langMap["ta"]=   QObject::tr("Tamil");
        langMap["te"]=   QObject::tr("Telugu");
        langMap["th"]=   QObject::tr("Thai");
        langMap["tr"]=   QObject::tr("Turkish");
        langMap["uk"]=   QObject::tr("Ukrainian");
        langMap["ur"]=   QObject::tr("Urdu");
        langMap["vi"]=   QObject::tr("Vietnamese");
        langMap["cy"]=   QObject::tr("Welsh");
        langMap["yi"]=   QObject::tr("Yiddish");

        alreadyInitialized = true;
        return langMap;
    }
}


#endif // LANGLISTISO
