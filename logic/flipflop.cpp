#include "logic/flipflop.h"

FlipFlop::FlipFlop(int x, int y, bool signal) :
    Cell(x, y, signal)
{}

FlipFlop::FlipFlop(string expression) :
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

string FlipFlop::getType() const
{
    return "FlipFlop";
}

void FlipFlop::resetSignal()
{
    signal = 0;
}

void FlipFlop::receiveSignal(const Cell *c)
{
    if (c->signal==1)
        signal = !signal;
}

bool FlipFlop::isReady()
{
    if (!Cell::isReady())
        return false;
    return true;
}

