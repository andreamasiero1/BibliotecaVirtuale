#ifndef MAGAZINE_H
#define MAGAZINE_H
#include "lettura.h"
using std::string;

class Magazine : public Lettura{
private:
    int edition;
public:
    Magazine(string title, string genere, int year, double price, string language, string image, string autore, int ISBN, int edition);
    // Getters
    int getEdition() const;
    // Setters
    void setEdition(int newedition);
    // Destructor
    virtual ~Magazine() = default;
    // Visitor pattern
    void accept(Visitor* visitor) override;
};

#endif // MAGAZINE_H
