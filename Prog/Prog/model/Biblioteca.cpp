#include "Biblioteca.h"
#include "Book.h"
#include "Film.h"
#include "MagazineArticle.h"
#include "../view/MediaCollectorVisitor.h"

// Costruttore di default di Biblioteca
Biblioteca::Biblioteca() {}

// Distruttore di Biblioteca
Biblioteca::~Biblioteca()
{
    svuota();
}

// Costruttore di copia di Biblioteca gestito dal container
Biblioteca::Biblioteca(const Biblioteca &other) : mediaContainer(other.mediaContainer) {}

// Operatore di assegnazione di Biblioteca gestito dal container
Biblioteca &Biblioteca::operator=(const Biblioteca &other)
{
    if (this != &other)
    {
        mediaContainer = other.mediaContainer;
    }
    return *this;
}

// Aggiunge nuovo Media alla Biblioteca
void Biblioteca::aggiungiMedia(Media *media)
{
    try
    {
        mediaContainer.add(media);
    }
    catch (const std::exception &e)
    {
        throw;
    }
}

// Rimuove un Media specifico dalla Biblioteca
bool Biblioteca::rimuoviMedia(Media *media)
{
    try
    {
        mediaContainer.remove(media);
        return true;
    }
    catch (const MediaNotFoundException &e)
    {
        return false;
    }
}
// Rimuove un Media dalla biblioteca tramite il suo indice posizionale.
void Biblioteca::rimuoviMediaAt(int index)
{
    mediaContainer.removeAt(index);
}

// Ottiene un Media dalla biblioteca tramite il suo indice posizionale.
Media *Biblioteca::getMediaAt(int index) const
{
    return mediaContainer.at(index);
}

// Ricerca Media per titolo nella Biblioteca
QList<Media *> Biblioteca::cercaPerTitolo(const QString &titolo) const
{
    return mediaContainer.find([&titolo](Media *media)
                               { return media->getTitle().contains(titolo, Qt::CaseInsensitive); });
}

// Ricerca Media per anno di pubblicazione nella Biblioteca
QList<Media *> Biblioteca::cercaPerAnno(int anno) const
{
    return mediaContainer.find([&anno](Media *media)
                               { return media->getYear() == anno; });
}

// Ottiene tutti i Media presenti nella Biblioteca
QList<Media *> Biblioteca::getTuttiMedia() const
{
    return mediaContainer.getAll();
}

// Raccoglie Media per tipo utilizzando il Pattern Visitor
QList<Media *> Biblioteca::collectMediaByType(MediaFilter::FilterType filterType) const
{
    MediaCollectorVisitor collector(filterType);
    // Applica il visitor ad ogni Media
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

// Svuota completamente la Biblioteca
void Biblioteca::svuota()
{
    mediaContainer.clear();
}

// Ottiene il numero di Media presenti nella Biblioteca
int Biblioteca::dimensione() const
{
    return mediaContainer.size();
}

// Verifica se la biblioteca è vuota
bool Biblioteca::isEmpty() const
{
    return mediaContainer.isEmpty();
}