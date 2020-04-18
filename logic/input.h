#ifndef INPUT_H
#define INPUT_H
#include "logic/cell.h"

class Input : public Cell
{
public:
    Input(int, int, bool = 1);
    Input(string);

    string getType() const;

    virtual void resetSignal();
    virtual void receiveSignal(const Cell *);
    virtual bool isReady();

};

#endif // INPUT_H
