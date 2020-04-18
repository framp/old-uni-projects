#include "logic/input.h"

Input::Input(int x, int y, bool signal) :
    Cell(x, y, signal)
{}
Input::Input(string expression) :
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


string Input::getType() const
{
    return "Input";
}

void Input::resetSignal()
{
    signal = 1;
}

void Input::receiveSignal(const Cell *)
{
}

bool Input::isReady()
{
    if (!Cell::isReady())
        return false;
    signal = 1;
    return true;
}
