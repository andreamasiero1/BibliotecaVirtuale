#include "film.h"
using std::string;

Film::Film(string title, string genere, int year, double price,string language,string image, string regista, int durata, Supporto formato, string produzione)
    : Media(title, genere, year, price, language, image), regista(regista), durata(durata), formato(formato), produzione(produzione) {
    // Constructor implementation
}
// Getters
string Film::getRegista() const {
    return regista;
}
int Film::getDurata() const {
    return durata;
}
Film::Supporto Film::getFormato() const {
    return formato;
}
string Film::getProduzione() const {
    return produzione;
}
// Setters
void Film::setRegista(const string& newregista) {
    regista = newregista;
}
void Film::setDurata(int newdurata) {
    durata = newdurata;
}
void Film::setFormato(Supporto newformato) {
    formato = newformato;
}
void Film::setProduzione(const string& newproduzione) {
    produzione = newproduzione;
}
// Visitor pattern
void Film::accept(Visitor* visitor){
    visitor->visit(this);
}