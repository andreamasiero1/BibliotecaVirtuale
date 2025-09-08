#ifndef BIBLIOTECA_H
#define BIBLIOTECA_H

#include <QList>
#include <QString>
#include "../model/Media.h"
#include "Container.h"
#include "Exceptions.h"

class MediaCollectorVisitor;

namespace MediaFilter
{
    enum class FilterType
    {
        ALL,
        BOOKS_ONLY,
        FILMS_ONLY,
        ARTICLES_ONLY
    };
}

class Biblioteca
{
public:
    Biblioteca();
    ~Biblioteca();

    Biblioteca(const Biblioteca &other);
    Biblioteca &operator=(const Biblioteca &other);

    void aggiungiMedia(Media *media);
    bool rimuoviMedia(Media *media);
    void rimuoviMediaAt(int index);
    Media *getMediaAt(int index) const;
    QList<Media *> cercaPerTitolo(const QString &titolo) const;
    QList<Media *> cercaPerAnno(int anno) const;
    QList<Media *> getTuttiMedia() const;

    QList<Media *> collectMediaByType(MediaFilter::FilterType filterType) const;

    void svuota();
    int dimensione() const;
    bool isEmpty() const;

private:
    Container<Media> mediaContainer;
};

#endif // BIBLIOTECA_H
