#include "logic/vector.h"

Vector::Vector(int x, int y) :
    x(x), y(y)
{}
Vector::Vector(string expression) :
    x(0), y(0)
{
    int size = expression.size();
    stringstream stream(expression);
    stream.ignore(size,'(');
    stream >> x;
    stream.ignore(size,',');
    stream >> y;
}

string Vector::getType() const
{
    return "Vector";
}

string Vector::toString() const
{
    stringstream os;
    os << getType() << "(" << x << "," << y << ")";
    return os.str();
}

void Vector::operator+(const Base* b)
{
    if (b->getType()=="Grid")
        undefined();
    const Vector *v = static_cast<const Vector*>(b);
    if (getType()!=v->getType()) throw "Can't operate on different objects";
    x+=v->x;
    y+=v->y;
}

void Vector::operator-(const Base* b)
{
    if (b->getType()=="Grid")
        undefined();
    const Vector *v = static_cast<const Vector*>(b);
    if (getType()!=v->getType()) throw "Can't operate on different objects";
    x-=v->x;
    y-=v->y;
}
