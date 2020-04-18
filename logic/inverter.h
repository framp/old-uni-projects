#ifndef INVERTER_H
#define INVERTER_H
#include "logic/cell.h"

class Inverter : public Cell
{
public:
    Inverter(int, int, bool = 0);
    Inverter(string);

    virtual string getType() const;

    virtual void resetSignal();
    virtual void receiveSignal(const Cell *);
    virtual bool isReady();

};

#endif // INVERTER_H
