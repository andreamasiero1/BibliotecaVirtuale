#include "Film.h"
#include "../view/MediaVisitor.h"

Film::Film(const QString &title, int year, const QString &director, int duration, const QString &genere, const QString &coverImagePath) : Media(title, year, coverImagePath), director(director), duration(duration), genere(genere) {}

Film::Film(const Film &other) : Media(other), director(other.director), duration(other.duration), genere(other.genere) {}

QString Film::getDirector() const
{
    return director;
}

int Film::getDuration() const
{
    return duration;
}

QString Film::getGenere() const
{
    return genere;
}

void Film::setDirector(const QString &newDirector)
{
    director = newDirector;
}

void Film::setDuration(int newDuration)
{
    duration = newDuration;
}

void Film::setGenere(const QString &newGenere)
{
    genere = newGenere;
}

QString Film::visualizzaDettagli() const
{
    return QString("Film: %1 (%2)\nRegista: %3\nDurata: %4 min\nGenere: %5\nCopie disponibili: %6")
        .arg(getTitle())
        .arg(getYear())
        .arg(director)
        .arg(duration)
        .arg(genere)
        .arg(getCopiesAvailable());
}

QJsonObject Film::serializza() const
{
    QJsonObject jsonObject;
    jsonObject["type"] = "Film";
    jsonObject["title"] = title;
    jsonObject["year"] = year;
    jsonObject["director"] = director;
    jsonObject["duration"] = duration;
    jsonObject["genre"] = genere;
    jsonObject["coverImagePath"] = coverImagePath;
    jsonObject["copiesAvailable"] = getCopiesAvailable();
    return jsonObject;
}

Media *Film::clone() const
{
    return new Film(*this);
}

Film *Film::deserializza(const QJsonObject &jsonObject)
{
    QString title = jsonObject["title"].toString();
    int year = jsonObject["year"].toInt();
    QString director = jsonObject["director"].toString();
    int duration = jsonObject["duration"].toInt();
    QString genre = jsonObject["genre"].toString();
    QString coverImagePath = jsonObject["coverImagePath"].toString();
    Film *f = new Film(title, year, director, duration, genre, coverImagePath);
    if (jsonObject.contains("copiesAvailable"))
        f->setCopiesAvailable(jsonObject["copiesAvailable"].toInt());
    return f;
}

QWidget *Film::accept(MediaVisitor &visitor)
{
    return visitor.visit(this);
}
