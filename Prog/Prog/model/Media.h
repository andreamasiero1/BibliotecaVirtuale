#ifndef MEDIA_H
#define MEDIA_H

#include <QString>
#include <QJsonObject>

class Media
{
public:
    Media(const QString &title, int year, const QString &coverImagePath);

    QString getTitle() const;
    int getYear() const;
    QString getCoverImagePath() const;

    void setTitle(const QString &newTitle);
    void setYear(int newYear);
    void setCoverImagePath(const QString &newPath);

    int getCopiesAvailable() const;
    void setCopiesAvailable(int copies);
    void addCopies(int copies);

    virtual QString visualizzaDettagli() const = 0;
    virtual QJsonObject serializza() const = 0;
    virtual Media *clone() const = 0;
    static Media *deserializza(const QJsonObject &json);
    virtual QWidget *accept(MediaVisitor *visitor) = 0;
private:
    QString title;
    int year;
    QString coverImagePath;
    int copiesAvailable = 1; //di default 1 perche un media deve avere almeno una copia disponibile
};

#endif // MEDIA_H
