#include "MagazineArticle.h"
#include "../view/MediaVisitor.h"

MagazineArticle::MagazineArticle(const QString &title, int year, const QString &author, const QString &magazine, const QString &doi, const QString &coverImagePath)
    : Media(title, year, coverImagePath), author(author), magazine(magazine), doi(doi) {}

MagazineArticle::MagazineArticle(const MagazineArticle &other)
    : Media(other), author(other.author), magazine(other.magazine), doi(other.doi) {}

QString MagazineArticle::getAuthor() const
{
    return author;
}

QString MagazineArticle::getMagazine() const
{
    return magazine;
}

QString MagazineArticle::getDoi() const
{
    return doi;
}

void MagazineArticle::setAuthor(const QString &newAuthor)
{
    author = newAuthor;
}

void MagazineArticle::setMagazine(const QString &newMagazine)
{
    magazine = newMagazine;
}

void MagazineArticle::setDoi(const QString &newDoi)
{
    doi = newDoi;
}

QString MagazineArticle::visualizzaDettagli() const
{
    return QString("Articolo: %1 (%2)\nAutore: %3\nRivista: %4\nDOI: %5\nCopie disponibili: %6")
        .arg(title)
        .arg(year)
        .arg(author)
        .arg(magazine)
        .arg(doi)
        .arg(getCopiesAvailable());
}

QJsonObject MagazineArticle::serializza() const
{
    QJsonObject jsonObject;
    jsonObject["type"] = "MagazineArticle";
    jsonObject["title"] = title;
    jsonObject["year"] = year;
    jsonObject["author"] = author;
    jsonObject["magazine"] = magazine;
    jsonObject["doi"] = doi;
    jsonObject["coverImagePath"] = coverImagePath;
    jsonObject["copiesAvailable"] = getCopiesAvailable();
    return jsonObject;
}

Media *MagazineArticle::clone() const
{
    return new MagazineArticle(*this);
}

MagazineArticle *MagazineArticle::deserializza(const QJsonObject &jsonObject)
{
    QString title = jsonObject["title"].toString();
    int year = jsonObject["year"].toInt();
    QString author = jsonObject["author"].toString();
    QString magazine = jsonObject["magazine"].toString();
    QString doi = jsonObject["doi"].toString();
    QString coverImagePath = jsonObject["coverImagePath"].toString();
    MagazineArticle *a = new MagazineArticle(title, year, author, magazine, doi, coverImagePath);
    if (jsonObject.contains("copiesAvailable"))
        a->setCopiesAvailable(jsonObject["copiesAvailable"].toInt());
    return a;
}

QWidget *MagazineArticle::accept(MediaVisitor &visitor)
{
    return visitor.visit(this);
}
