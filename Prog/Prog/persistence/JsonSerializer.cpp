#include "JsonSerializer.h"
#include <QFile>
#include <QJsonParseError>
#include <QDebug>
#include <QFileInfo>
#include <QDir>
#include <QCoreApplication>

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
            QJsonObject obj = media->serializza();
            QString path = obj.value("coverImagePath").toString();
            obj["coverImagePath"] = toStoredImagePath(path);
            jsonArray.append(obj);
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
                QJsonObject obj = value.toObject();
                if (obj.contains("coverImagePath"))
                {
                    obj["coverImagePath"] = resolveImagePath(obj.value("coverImagePath").toString());
                }
                Media *media = MediaFactory::createFromJson(obj);
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

QString JsonSerializer::imagesBaseDir()
{
    QDir base(QCoreApplication::applicationDirPath());
// Ho dovuto aggiungere questa parte perchè lavorando su MacOS l'app veniva eseguita in una sottocartella "MacOS" dentro Contents
#ifdef Q_OS_MAC
    if (base.dirName() == "MacOS")
    {
        base.cdUp();
        base.cdUp();
        base.cdUp();
    }
#endif
    return base.filePath("data/images");
}

QString JsonSerializer::toStoredImagePath(const QString &absolutePath)
{
    if (absolutePath.isEmpty())
        return absolutePath;
    QFileInfo fi(absolutePath);
    if (!fi.exists())
        return fi.fileName().isEmpty() ? absolutePath : fi.fileName();

    QString base = imagesBaseDir();
    QString absBase = QDir(base).absolutePath();
    QString absFile = fi.absoluteFilePath();
    if (absFile.startsWith(absBase))
    {
        return fi.fileName();
    }
    return absolutePath;
}

QString JsonSerializer::resolveImagePath(const QString &storedPath)
{
    if (storedPath.isEmpty())
        return storedPath;

    QFileInfo fi(storedPath);
    if (fi.exists() && fi.isFile())
    {
        return fi.absoluteFilePath();
    }

    QString candidate = QDir(imagesBaseDir()).filePath(fi.fileName());
    QFileInfo cInfo(candidate);
    if (cInfo.exists() && cInfo.isFile())
        return cInfo.absoluteFilePath();

    return storedPath;
}
