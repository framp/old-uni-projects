#ifndef CELL_H
#define CELL_H
#include "logic/vector.h"

class Cell : public Vector
{
protected:
    bool signal, traversed;
    Cell(int, int, bool=0);

public:
    virtual string getType() const = 0;
    virtual string toString() const;
    virtual string toPath() const;

    virtual void resetSignal() = 0;
    virtual void propagateSignal( vector< CISpointer<Cell> >&) const;
    virtual void receiveSignal(const Cell *) = 0;
    virtual bool isReady();

    virtual void reset();

    friend class Grid;
    friend class Clock;
    friend class FlipFlop;
    friend class Gate;
    friend class Inverter;
    friend class Output;
    friend class Wire;
};

#endif // CELL_H
