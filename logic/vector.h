#ifndef VECTOR_H
#define VECTOR_H
#include "logic/base.h"

class Vector: public Base
{
protected:
    int x, y;

public:
    Vector(int, int);
    Vector(string);

    string getType() const;
    string toString() const;

    void operator+(const Base*);
    void operator-(const Base*);

    friend class Grid;
};

#endif // VECTOR_H
