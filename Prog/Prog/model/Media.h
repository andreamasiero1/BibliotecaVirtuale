#ifndef MEDIA_H
#define MEDIA_H

#include <QString>
#include <QJsonObject>

class MediaVisitor;

class Media
{
public:
    Media(const QString &title, int year, const QString &coverImagePath = "");
    virtual ~Media() = default;

    QString getTitle() const;
    int getYear() const;
    QString getCoverImagePath() const;
    void setCoverImagePath(const QString &path);
    void setTitle(const QString &title);
    void setYear(int year);


    int getCopiesAvailable() const;
    void setCopiesAvailable(int copies);
    void addCopies(int delta);

    virtual QString visualizzaDettagli() const = 0;
    virtual QJsonObject serializza() const = 0;
    virtual Media *clone() const = 0;
    static Media *deserializza(const QJsonObject &jsonObject);

    virtual QWidget *accept(MediaVisitor &visitor) = 0;

protected:
    QString title;
    int year;
    QString coverImagePath;
    int copiesAvailable = 1; // di default almeno 1 copia
};

#endif // MEDIA_H
