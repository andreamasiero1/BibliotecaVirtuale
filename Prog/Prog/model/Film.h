#ifndef FILM_H
#define FILM_H

#include "Media.h"
#include "../view/MediaVisitor.h"

class Film : public Media
{
public:
    Film(const QString &title, int year, const QString &director, int duration, const QString &genere, const QString &coverImagePath = "");

    Film(const Film &other);

    QString getDirector() const;
    int getDuration() const;
    QString getGenere() const;
    void setDirector(const QString &director);
    void setDuration(int duration);
    void setGenere(const QString &genere);

    QString visualizzaDettagli() const override;
    QJsonObject serializza() const override;
    Media *clone() const override;
    static Film *deserializza(const QJsonObject &jsonObject);

    QWidget *accept(MediaVisitor &visitor) override;

private:
    QString director;
    int duration;
    QString genere;
};

#endif // FILM_H
