#include "Book.h"
#include "../view/MediaVisitor.h"

Book::Book(const QString &title, int year, const QString &author, const QString &isbn, const QString &publisher, const QString &coverImagePath)
    : Media(title, year, coverImagePath), author(author), isbn(isbn), publisher(publisher)
{
}

Book::Book(const Book &other)
    : Media(other), author(other.author), isbn(other.isbn), publisher(other.publisher)
{
}

QString Book::getAuthor() const
{
    return author;
}

QString Book::getIsbn() const
{
    return isbn;
}

QString Book::getPublisher() const
{
    return publisher;
}

void Book::setAuthor(const QString &newAuthor)
{
    author = newAuthor;
}

void Book::setIsbn(const QString &newIsbn)
{
    isbn = newIsbn;
}

void Book::setPublisher(const QString &newPublisher)
{
    publisher = newPublisher;
}

QString Book::visualizzaDettagli() const
{
    return QString("Libro: %1 (%2)\nAutore: %3\nISBN: %4\nEditore: %5\nCopie disponibili: %7\nCopertina: %6")
        .arg(title)
        .arg(year)
        .arg(author)
        .arg(isbn)
        .arg(publisher)
        .arg(coverImagePath)
        .arg(getCopiesAvailable());
}

QJsonObject Book::serializza() const
{
    QJsonObject jsonObject;
    jsonObject["type"] = "Book";
    jsonObject["title"] = title;
    jsonObject["year"] = year;
    jsonObject["author"] = author;
    jsonObject["isbn"] = isbn;
    jsonObject["publisher"] = publisher;
    jsonObject["coverImagePath"] = coverImagePath;
    jsonObject["copiesAvailable"] = getCopiesAvailable();
    return jsonObject;
}

Media *Book::clone() const
{
    return new Book(*this);
}

Book *Book::deserializza(const QJsonObject &jsonObject)
{
    QString title = jsonObject["title"].toString();
    int year = jsonObject["year"].toInt();
    QString author = jsonObject["author"].toString();
    QString isbn = jsonObject["isbn"].toString();
    QString publisher = jsonObject["publisher"].toString();
    QString coverImagePath = jsonObject["coverImagePath"].toString();
    Book *b = new Book(title, year, author, isbn, publisher, coverImagePath);
    if (jsonObject.contains("copiesAvailable"))
        b->setCopiesAvailable(jsonObject["copiesAvailable"].toInt());
    return b;
}

QWidget *Book::accept(MediaVisitor &visitor)
{
    return visitor.visit(this);
}
