#include "logic/wire.h"

Wire::Wire(int x, int y, bool signal) :
    Cell(x, y, signal)
{}

Wire::Wire(string expression) :
    Cell(0,0,0)
{
    stringstream stream(expression);

    while(!stream.eof() && stream.peek()!='(') {
        stream.ignore();
    }
    stream.ignore();

    int n[3];
    for (int i=0; i<3; i++) {
        stream >> n[i];
        while(stream.peek()==' ') stream.ignore();
        stream.ignore();
    }
    x = n[0];
    y = n[1];
    signal = n[2];
}

string Wire::getType() const
{
    return "Wire";
}

void Wire::resetSignal()
{
    signal = 0;
}

void Wire::receiveSignal(const Cell *c)
{
    signal = c->signal;
}

bool Wire::isReady()
{
    if (!Cell::isReady())
        return false;
    return true;
}
