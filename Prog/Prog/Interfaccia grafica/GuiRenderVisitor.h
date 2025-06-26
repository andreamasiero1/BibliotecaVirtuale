#ifndef GUIRENDERVISITOR_H
#define GUIRENDERVISITOR_H

#include <QLabel>
#include <QGridLayout>
#include "visitor.h"

class Media;
class Lettura;

class GuiRenderVisitor : public Visitor{
private:
    QGridLayout* layout; // Layout per organizzare gli elementi grafici
    QLabel* label;
    QWidget* widget;
public:
    GuiRenderVisitor();
    QWidget* getWidget() const;
    void visit(Film* film) override;
    void visit(Libri*libri) override;
    void visit(Magazine* magazine) override;
    void visit(Lettura* lettura);
    void visit(Media* media);
    
};
#endif // GUIRENDERVISITOR_H
