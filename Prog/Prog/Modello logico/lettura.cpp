#include "lettura.h"
using std::string;

Lettura::Lettura(string title, string genere, int year, double price, string language, string image, string autore, int ISBN)
    : Media(title, genere, year, price, language, image), autore(autore), ISBN(ISBN) {
    // Constructor implementation
}
// Getters
string Lettura::getAutore() const {
    return autore;
}
int Lettura::getISBN() const {
    return ISBN;
}
// Setters
void Lettura::setAutore(const string& newautore) {
    autore = newautore;
}
void Lettura::setISBN(int newISBN) {
    ISBN = newISBN;
}