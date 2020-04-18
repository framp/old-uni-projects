#ifndef FLIPFLOP_H
#define FLIPFLOP_H
#include "logic/cell.h"

class FlipFlop : public Cell
{
public:
    FlipFlop(int, int, bool = 0);
    FlipFlop(string);

    virtual string getType() const;

    virtual void resetSignal();
    virtual void receiveSignal(const Cell *);
    virtual bool isReady();
};

#endif // FLIPFLOP_H
