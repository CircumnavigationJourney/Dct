#ifndef ABSTRACTTRANSLATOR_H
#define ABSTRACTTRANSLATOR_H

#include <QString>
class AbstractTranslator
{
private:
    int ID;

public:
    enum class Provider{
        YandexDictionary,
        GoogleTranslator,
        OfflineDictionary
    };

    AbstractTranslator(int id);
    ~AbstractTranslator();

    virtual bool learningDirectionIsSupported(const QString& learningLang, const QString& knownLang) = 0;

};

#endif // ABSTRACTTRANSLATOR_H
