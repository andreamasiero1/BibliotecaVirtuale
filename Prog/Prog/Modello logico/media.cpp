#include "media.h"
using std::string;

Media::Media(string title, string genere,int year, double price, string language, string image)
    : title(title), genere(genere), year(year), price(price), language(language), image(image) {
    // Constructor implementation
}

// Getters
string Media::getTitle() const {
    return title;
}
string Media::getGenere() const {
    return genere;
}
int Media::getYear() const {
    return year;
}
double Media::getPrice() const {
    return price;
}
string Media::getLanguage() const {
    return language;
}
string Media::getImage() const {
    return image;
}
// Setters
void Media::setTitle(const string& newtitle) {
    title = newtitle;
}
void Media::setGenere(const string& newgenere) {
    genere = newgenere;
}
void Media::setYear(int newyear) {
    year = newyear;
}
void Media::setPrice(double newprice) {
    price = newprice;
}
void Media::setLanguage(const string& newlanguage) {
    language = newlanguage;
}
void Media::setImage(const string& newimage) {
    image = newimage;
}
