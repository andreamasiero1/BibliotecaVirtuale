#include "JsonSerializer.h"
#include <QFile>
#include <QJsonParseError>
#include <QDebug>

bool JsonSerializer::salvaBiblioteca(const Biblioteca &biblioteca, const QString &filePath)
{
    try
    {
        QJsonObject jsonObject;
        jsonObject["biblioteca"] = serializeMediaList(biblioteca.getTuttiMedia());

        QJsonDocument jsonDoc(jsonObject);

        QFile file(filePath);
        if (!file.open(QIODevice::WriteOnly))
        {
            return false;
        }

        file.write(jsonDoc.toJson());
        if (file.error() != QFile::NoError)
        {
            file.close();
            return false;
        }
        file.close();
        return true;
    }
    catch (const BibliotecaException &)
    {
        return false;
    }
}

bool JsonSerializer::caricaBiblioteca(Biblioteca &biblioteca, const QString &filePath)
{
    try
    {
        QFile file(filePath);
        if (!file.open(QIODevice::ReadOnly))
        {
            return false;
        }

        QByteArray data = file.readAll();
        file.close();

        QJsonParseError parseError;
        QJsonDocument jsonDoc = QJsonDocument::fromJson(data, &parseError);

        if (parseError.error != QJsonParseError::NoError)
        {
            return false;
        }

        QJsonObject jsonObject = jsonDoc.object();
        if (!jsonObject.contains("biblioteca"))
        {
            return false;
        }

        QJsonArray mediaArray = jsonObject["biblioteca"].toArray();

        biblioteca.svuota();

        QList<Media *> mediaList = deserializeMediaList(mediaArray);
        for (Media *media : mediaList)
        {
            biblioteca.aggiungiMedia(media);
        }
        return true;
    }
    catch (const BibliotecaException &)
    {
        return false;
    }
}



QJsonArray JsonSerializer::serializeMediaList(const QList<Media *> &mediaList)
{
    QJsonArray jsonArray;
    for (const Media *media : mediaList)
    {
        if (media)
        {
            jsonArray.append(media->serializza());
        }
    }
    return jsonArray;
}

QList<Media *> JsonSerializer::deserializeMediaList(const QJsonArray &jsonArray)
{
    QList<Media *> mediaList;
    for (const QJsonValue &value : jsonArray)
    {
        if (value.isObject())
        {
            try
            {
                Media *media = MediaFactory::createFromJson(value.toObject());
                if (media)
                {
                    mediaList.append(media);
                }
            }
            catch (const BibliotecaException &e)
            {
                qDebug() << "Errore nella deserializzazione di un media:" << e.what();
            }
        }
    }
    return mediaList;
}
