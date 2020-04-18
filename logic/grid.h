#ifndef GRID_H
#define GRID_H

#include "logic/cell.h"

#include "logic/clock.h"
#include "logic/flipflop.h"
#include "logic/gate.h"
#include "logic/input.h"
#include "logic/inverter.h"
#include "logic/output.h"
#include "logic/wire.h"

#include "utilities/validator.h"

class Grid : public Base
{
private:
    int width, height, time;
    vector< CISpointer<Cell> > cells;

    void insert(Cell *);
    void remove(Cell *);
    void shift(int, int);
    void merge(const Grid *);
    void propagateToNeighbours(Cell &, int = -1, int = -1);

public:
    virtual void tick();
    virtual void reset();

public:
    Grid(int, int, int = 0);
    Grid(string);

    virtual string getType() const;
    virtual string toString() const;

    virtual void operator<<(Base *);
    virtual void operator>>(Base *);
    virtual void operator+(const Base * b);
    virtual void operator-(const Base * b);

    friend class CalculatorGridView;

};

#endif // GRID_H
