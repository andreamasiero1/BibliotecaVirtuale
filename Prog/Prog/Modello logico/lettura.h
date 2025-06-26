#ifndef LETTURA_H
#define LETTURA_H
#include "media.h"
using std::string;
class Lettura : public Media {
private:
    string autore;
    int ISBN;
public:
    Lettura(string title, string genere, int year, double price, string language, string image, string autore, int ISBN);
    // Getters
    string getAutore() const;
    int getISBN() const;
    // Setters
    void setAutore(const string& newautore);
    void setISBN(int newISBN);
    // Destructor
    virtual ~Lettura() = default;
    // Visitor pattern
    virtual void accept(Visitor* visitor) override = 0;

};
#endif // LETTURA_H
