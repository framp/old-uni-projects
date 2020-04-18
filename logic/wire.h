#ifndef WIRE_H
#define WIRE_H
#include "logic/cell.h"

class Wire : public Cell
{
public:
    Wire(int, int, bool = 0);
    Wire(string);

    virtual string getType() const;

    virtual void resetSignal();
    virtual void receiveSignal(const Cell *);
    virtual bool isReady();

};

#endif // WIRE_H
