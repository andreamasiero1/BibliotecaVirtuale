#include "MediaCollectorVisitor.h"
#include "../model/Media.h"
#include "../model/Book.h"
#include "../model/Film.h"
#include "../model/MagazineArticle.h"

MediaCollectorVisitor::MediaCollectorVisitor(FilterType type) : filterType(type) {}

QWidget *MediaCollectorVisitor::visit(Book *book)
{
    if (book && (filterType == FilterType::ALL || filterType == FilterType::BOOKS_ONLY))
    {
        collectedMedia.append(book);
    }
    return nullptr;
}

QWidget *MediaCollectorVisitor::visit(Film *film)
{
    if (film && (filterType == FilterType::ALL || filterType == FilterType::FILMS_ONLY))
    {
        collectedMedia.append(film);
    }
    return nullptr;
}

QWidget *MediaCollectorVisitor::visit(MagazineArticle *article)
{
    if (article && (filterType == FilterType::ALL || filterType == FilterType::ARTICLES_ONLY))
    {
        collectedMedia.append(article);
    }
    return nullptr;
}

QList<Media *> MediaCollectorVisitor::getCollectedMedia() const
{
    return collectedMedia;
}


void MediaCollectorVisitor::setFilterType(FilterType type)
{
    filterType = type;
}