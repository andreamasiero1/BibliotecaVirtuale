#include "Media.h"
#include "Book.h"
#include "Film.h"
#include "MagazineArticle.h"

Media::Media(const QString &title, int year, const QString &coverImagePath) : title(title), year(year), coverImagePath(coverImagePath) {}

QString Media::getTitle() const
{
    return title;
}

int Media::getYear() const
{
    return year;
}

QString Media::getCoverImagePath() const
{
    return coverImagePath;
}
void Media::setTitle(const QString &newTitle)
{
    title = newTitle;
}

void Media::setYear(int newYear)
{
    year = newYear;
}

void Media::setCoverImagePath(const QString &newPath)
{
    coverImagePath = newPath;
}
int Media::getCopiesAvailable() const
{
    return copiesAvailable;
}

void Media::setCopiesAvailable(int copies)
{
    if (copies < 0)
        copies = 0;
    copiesAvailable = copies;
}
void Media::addCopies(int copies)
{
    if (copies < 0)
        copies = 0;
    copiesAvailable += copies;
}

Media *Media::deserializza(const QJsonObject &json)
{
    QString type = json["type"].toString();
    if (type == "Book")
    {
        return Book::deserializza(json);
    }
    else if (type == "Film")
    {
        return Film::deserializza(json);
    }
    else if (type == "MagazineArticle")
    {
        return MagazineArticle::deserializza(json);
    }
    return nullptr;
}
