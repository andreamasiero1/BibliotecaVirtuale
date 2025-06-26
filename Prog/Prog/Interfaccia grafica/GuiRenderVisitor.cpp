#include "GuiRenderVisitor.h"
#include "../Modello logico/film.h"
#include "../Modello logico/libri.h"
#include "../Modello logico/magazine.h"

GuiRenderVisitor::GuiRenderVisitor(): widget(new QWidget()),layout(new QGridLayout(widget)), label(new QLabel(widget)) {
    widget->setLayout(layout);
}

QWidget* GuiRenderVisitor::getWidget() const{
    return widget;
}

void GuiRenderVisitor::visit(Film* film){
    label->setText("Film: " + QString::fromStdString(film->getTitle()) + "\n" +
                   "Genere: " +QString::fromStdString(film->getGenere()) + "\n" +
                   "Anno: " + QString::number(film->getYear()) + "\n" +
                    "Prezzo: " + QString::number(film->getPrice()) + "\n" +
                    "Lingua: " + QString::fromStdString(film->getLanguage()) + "\n" +
                    "Regista: " + QString::fromStdString(film->getRegista()) + "\n" +
                    "Durata (min): " + QString::number(film->getDurata()) + "\n" +
                    "Formato: " + QString::fromStdString(film->getProduzione()) + "\n" +
                   "Produzione: " + QString::fromStdString(film->getProduzione()) + "\n");
    layout->addWidget(label, 0, 0);
    widget->setWindowTitle("Film");
    widget->show();
}

void GuiRenderVisitor::visit(Libri*libri){
    label->setText("Libri: " + QString::fromStdString(libri->getTitle()) + "\n" +
                   "Genere: " +QString::fromStdString(libri->getGenere()) + "\n" +
                   "Anno: " + QString::number(libri->getYear()) + "\n" +
                    "Prezzo: " + QString::number(libri->getPrice()) + "\n" +
                    "Lingua: " + QString::fromStdString(libri->getLanguage()) + "\n" +
                    "Editore: " + QString::fromStdString(libri->getEditore()) + "\n" +
                   "Pagine: " + QString::number(libri->getPagine()) + "\n");
    layout->addWidget(label, 0, 0);
    widget->setWindowTitle("Libri");
    widget->show();
}

void GuiRenderVisitor::visit(Magazine* magazine){
    label->setText("Magazine: " + QString::fromStdString(magazine->getTitle()) + "\n" +
                   "Genere: " +QString::fromStdString(magazine->getGenere()) + "\n" +
                   "Anno: " + QString::number(magazine->getYear()) + "\n" +
                    "Prezzo: " + QString::number(magazine->getPrice()) + "\n" +
                    "Lingua: " + QString::fromStdString(magazine->getLanguage()) + "\n" +
                    "Autore: " + QString::fromStdString(magazine->getAutore()) + "\n" +
                    "ISBN: " + QString::number(magazine->getISBN()) + "\n" +
                   "Edizione: " + QString::number(magazine->getEdition()) + "\n");
    layout->addWidget(label, 0, 0);
    widget->setWindowTitle("Magazine");
    widget->show();
}

