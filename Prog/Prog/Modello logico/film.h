#ifndef FILM_H
#define FILM_H
#include "media.h"
using std::string;

class Film : public Media{
public:
    enum Supporto { DVD, BLURAY, STREAMING };
private:
    string regista;
    int durata;
    Supporto formato;
    string produzione;
public:
    Film(string title, string genere, int year, double price,string language,string image, string regista, int durata, Supporto formato, string produzione);
    // Getters
    string getRegista() const;
    int getDurata() const;
    Supporto getFormato() const;
    string getProduzione() const;
    // Setters
    void setRegista(const string& newregista);
    void setDurata(int newdurata);
    void setFormato(Supporto newformato);
    void setProduzione(const string& newproduzione);
    // Destructor
    virtual ~Film() = default;
    // Visitor pattern
    void accept(Visitor* visitor) override;
};

#endif // FILM_H