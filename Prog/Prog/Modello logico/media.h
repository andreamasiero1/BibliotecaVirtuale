#ifndef MEDIA_H
#define MEDIA_H
#include <string>
using std::string;
#include "../Interfaccia grafica/GuiRenderVisitor.h"

// Forward declaration of Visitor class

class Media {
private:
    string title;
    string genere;
    int year;
    double price;
    string language;
    string image;
public:
    Media(string title, string genere, int year, double price, string language, string image);
    virtual ~Media() = default;
    // Getters
    string getTitle() const;
    string getGenere() const;
    int getYear() const;
    double getPrice() const;
    string getLanguage() const;
    string getImage() const;
    // Setters
    void setTitle(const string& newtitle);
    void setGenere(const string& newgenere);
    void setYear(int newyear);
    void setPrice(double newprice);
    void setLanguage(const string& newlanguage);
    void setImage(const string& newimage);
    virtual void accept(Visitor* visitor) = 0;
};
#endif // BIBLIOTECA_H
