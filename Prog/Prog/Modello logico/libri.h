#ifndef LIBRI_H
#define LIBRI_H
#include "lettura.h"
using std::string;
class Libri : public Media {
private:
    string editore;
    int pagine;
public:
    Libri(string title, string genere, int year, double price, string language, string image, string editore, int pagine);
    // Getters
    string getEditore() const;
    int getPagine() const;
    // Setters
    void setEditore(const string& neweditore);
    void setPagine(int newpagine);
    // Destructor
    virtual ~Libri() = default;
    // Visitor pattern
    void accept(Visitor* visitor) override;
};
#endif // LIBRI_H