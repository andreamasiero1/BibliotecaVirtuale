#ifndef BIBLIOTECA_H
#define BIBLIOTECA_H

#include <QList>
#include <QString>
#include "Media.h"
#include "../view/Container.h"
#include "../view/Exception.h"

class MediaCollectorVisitor;

// Filtro per i media
namespace MediaFilter
{
    enum class FilterType
    {
        ALL,
        BOOKS_ONLY,
        FILMS_ONLY,
        MAGAZINES_ONLY
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
    void rimuoviMedia(Media *media);
    void *rimuoviMediaAt(int index);
    Media *getMediaAt(int index) const;
    QList<Media *>cercaPerTitolo(const QString &titolo) const;
    QList<Media *>cercaPerAnno(int anno)const;
    QList<Media *> getTuttiMedia() const;

    void svuota();
    int dimensione () const;
    bool isEmpty() const;
private:
    Container<Media*> mediaContainer;
};

#endif // BIBLIOTECA_H