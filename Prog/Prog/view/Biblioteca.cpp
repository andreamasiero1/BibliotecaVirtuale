#include "Biblioteca.h"
#include "../model/Book.h"
#include "../model/Film.h"
#include "../model/MagazineArticle.h"
#include "MediaCollectorVisitor.h"

Biblioteca::Biblioteca() {}

Biblioteca::~Biblioteca()
{
    svuota();
}

Biblioteca::Biblioteca(const Biblioteca &other) : mediaContainer(other.mediaContainer)
{
}

Biblioteca &Biblioteca::operator=(const Biblioteca &other)
{
    if (this != &other)
    {
        mediaContainer = other.mediaContainer;
    }
    return *this;
}

void Biblioteca::aggiungiMedia(Media *media)
{
    try
    {
        mediaContainer.add(media);
    }
    catch (const BibliotecaException &)
    {
        throw;
    }
}

bool Biblioteca::rimuoviMedia(Media *media)
{
    try
    {
        mediaContainer.remove(media);
        return true;
    }
    catch (const MediaNotFoundException &)
    {
        return false;
    }
}

void Biblioteca::rimuoviMediaAt(int index)
{
    mediaContainer.removeAt(index);
}

Media *Biblioteca::getMediaAt(int index) const
{
    return mediaContainer.at(index);
}

QList<Media *> Biblioteca::cercaPerTitolo(const QString &titolo) const
{
    return mediaContainer.find([&titolo](Media *media)
                               { return media->getTitle().contains(titolo, Qt::CaseInsensitive); });
}

QList<Media *> Biblioteca::cercaPerAnno(int anno) const
{
    return mediaContainer.find([anno](Media *media)
                               { return media->getYear() == anno; });
}

QList<Media *> Biblioteca::getTuttiMedia() const
{
    return mediaContainer.getAll();
}

QList<Media *> Biblioteca::collectMediaByType(MediaFilter::FilterType filterType) const
{
    MediaCollectorVisitor collector(filterType);

    QList<Media *> allMedia = getTuttiMedia();
    for (Media *media : allMedia)
    {
        if (media)
        {
            media->accept(collector);
        }
    }

    return collector.getCollectedMedia();
}

void Biblioteca::svuota()
{
    mediaContainer.clear();
}

int Biblioteca::dimensione() const
{
    return mediaContainer.size();
}

bool Biblioteca::isEmpty() const
{
    return mediaContainer.isEmpty();
}
