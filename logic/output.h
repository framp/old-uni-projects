#ifndef OUTPUT_H
#define OUTPUT_H
#include "logic/cell.h"

class Output : public Cell
{
public:
    Output(int, int, bool = 0);
    Output(string);
    virtual string getType() const;

    virtual void resetSignal();
    virtual void receiveSignal(const Cell *);
    virtual bool isReady();

};

#endif // OUTPUT_H
