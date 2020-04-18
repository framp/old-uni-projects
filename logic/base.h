#ifndef BASE_H
#define BASE_H
#include "utilities/cispointer.h"
#include <vector>
#include <sstream>
using namespace std;

class Cell;
class Base
{
protected:
    void undefined() const;
    int references;
    Base();

public:
    virtual string getType() const = 0;
    virtual string toString() const = 0;

    virtual void operator<<(Base *);
    virtual void operator>>(Base *);
    virtual void operator+(const Base*);
    virtual void operator-(const Base*);
    virtual void operator&(const Base*);
    virtual void operator|(const Base*);
    virtual void operator!();
    virtual void tick();
    virtual void reset();

    virtual ~Base();

    friend class CISpointer<Base>;
    friend class CISpointer<Cell>;
};

#endif // BASE_H
