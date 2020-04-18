#ifndef CLOCK_H
#define CLOCK_H
#include "logic/cell.h"

class Clock : public Cell
{
private:
    int frequency, ticks;
public:
    Clock(int, int, bool, int);
    Clock(string);

    virtual string getType() const;
    virtual string toString() const;

    virtual void resetSignal();
    virtual void receiveSignal(const Cell *);
    virtual bool isReady();

    virtual void tick();
};

#endif // CLOCK_H
