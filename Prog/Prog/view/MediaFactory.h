#ifndef MEDIAFACTORY_H
#define MEDIAFACTORY_H

#include <QString>
#include <QJsonObject>
#include "../model/Media.h"
#include "../model/Book.h"
#include "../model/Film.h"
#include "../model/MagazineArticle.h"
#include "Exceptions.h"

class MediaFactory
{
public:
    static Media *createBook(const QString &title, int year, const QString &author,
                             const QString &isbn, const QString &publisher,
                             const QString &coverImagePath = "");

    static Media *createFilm(const QString &title, int year, const QString &director,
                             int duration, const QString &genre,
                             const QString &coverImagePath = "");

    static Media *createMagazineArticle(const QString &title, int year, const QString &author,
                                        const QString &magazine, const QString &doi,
                                        const QString &coverImagePath = "");

    static Media *createFromJson(const QJsonObject &jsonObject);
    static Media *createMedia(const QString &type, const QString &title, int year);
    static bool isValidType(const QString &type);
    static QStringList getSupportedTypes();

private:
    MediaFactory() = default;
    static void validateBookData(const QString &title, int year, const QString &author,
                                 const QString &isbn, const QString &publisher);
    static void validateFilmData(const QString &title, int year, const QString &director,
                                 int duration, const QString &genre);
    static void validateMagazineData(const QString &title, int year, const QString &author,
                                     const QString &magazine, const QString &doi);
    static void validateCommonData(const QString &title, int year);
};

#endif // MEDIAFACTORY_H
