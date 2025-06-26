#ifndef VISITOR_H
#define VISITOR_H

class Film;
class Libri;
class Magazine;

class Visitor{
public:
    virtual ~Visitor()=default;
    virtual void visit(Film* film)=0;
    virtual void visit(Libri* libri)=0;
    virtual void visit(Magazine* magazine)=0;
};

#endif // VISITOR_H
