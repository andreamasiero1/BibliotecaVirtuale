#include "magazine.h"
using std::string;

Magazine::Magazine(string title, string genere, int year,double price, string language,string image,string autore,int ISBN, int edition)
    : Lettura(title, genere, year, price, language, image, autore, ISBN), edition(edition){
    // Constructor implementation
    }
// Getters
int Magazine::getEdition() const{
    return edition;
}
// Setters
void Magazine::setEdition(int newedition){
    edition=newedition;
}
// Visitor pattern
void Magazine::accept(Visitor* visitor){
    visitor->visit(this);
}