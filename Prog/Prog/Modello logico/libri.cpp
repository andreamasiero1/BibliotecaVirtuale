#include "libri.h"
using std::string;

Libri::Libri(string title, string genere, int year, double price, string language, string image, string editore, int pagine)
    : Media(title, genere, year, price, language, image), editore(editore), pagine(pagine) {
    // Constructor implementation
}
// Getters
string Libri::getEditore() const {
    return editore;
}           
int Libri::getPagine() const {
    return pagine;
}
// Setters
void Libri::setEditore(const string& neweditore) {
    editore = neweditore;
}
void Libri::setPagine(int newpagine) {
    pagine = newpagine;
}
// Visitor pattern
void Libri::accept(Visitor* visitor){
    visitor->visit(this);
}