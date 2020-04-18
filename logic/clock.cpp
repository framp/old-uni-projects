#include "logic/clock.h"

Clock::Clock(int x, int y, bool signal, int c) :
    Cell(x, y, signal), frequency(c), ticks(c)
{}

Clock::Clock(string expression) :
    Cell(0,0,0), frequency(0), ticks(0)
{
    stringstream stream(expression);

    while(!stream.eof() && stream.peek()!='(') {
        stream.ignore();
    }
    stream.ignore();

    int n[5];
    for (int i=0; i<5; i++) {
        stream >> n[i];
        while(stream.peek()==' ') stream.ignore();
        stream.ignore();
    }
    x = n[0];
    y = n[1];
    signal = n[2];
    frequency = n[3];
    ticks = n[4];
}

string Clock::getType() const
{
    return "Clock";
}

string Clock::toString() const
{
    stringstream stream;
    stream << getType() << "(" << x << "," << y << "," << signal << "," << frequency << "," << ticks << ")";
    return stream.str();
}


void Clock::resetSignal()
{
    signal = 0;
    ticks = frequency;
}

void Clock::receiveSignal(const Cell *)
{
}

bool Clock::isReady()
{
    signal = 0;
    if (!Cell::isReady())
        return false;
    tick();
    return true;
}

void Clock::tick()
{
    ticks--;
    if (ticks<=0) {
        signal = 1;
        ticks = frequency;
    }else{
        signal = 0;
    }
}
