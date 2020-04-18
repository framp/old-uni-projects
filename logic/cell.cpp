#include "logic/cell.h"

Cell::Cell(int x, int y, bool signal) :
    Vector(x, y), signal(signal), traversed(0)
{ }

string Cell::toString() const
{
    stringstream stream;
    stream << getType() << "(" << x << "," << y << "," << signal << ")";
    return stream.str();
}

string Cell::toPath() const
{
    stringstream stream;
    stream << getType() << "-" << signal;
    return stream.str();
}

void Cell::propagateSignal( vector< CISpointer<Cell> >& cells) const
{
    vector< CISpointer<Cell> >::iterator it;
    for (it=cells.begin(); it!=cells.end(); ++it) {
        if (*it!=0) {
            (*it)->receiveSignal(this);
        }
    }
}

bool Cell::isReady()
{
    if (!traversed) {
        traversed = true;
    } else {
        return false;
    }
    return true;
}

void Cell::reset()
{
    resetSignal();
}
