#ifndef MEDIACOLLECTORVISITOR_H
#define MEDIACOLLECTORVISITOR_H

#include "MediaVisitor.h"
#include "../model/Biblioteca.h"
#include <QList>
#include <QString>

class Media;
class Book;
class Film;
class MagazineArticle;

class MediaCollectorVisitor : public MediaVisitor
{
public:
    using FilterType = MediaFilter::FilterType;

private:
    QList<Media *> collectedMedia;
    FilterType filterType;

public:
    explicit MediaCollectorVisitor(FilterType type = FilterType::ALL);
    QWidget *visit(Book *book) override;
    QWidget *visit(Film *film) override;
    QWidget *visit(MagazineArticle *article) override;
    QList<Media *> getCollectedMedia() const;
    void clearCollection();
    void setFilterType(FilterType type);    

};

#endif // MEDIACOLLECTORVISITOR_H