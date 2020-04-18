#include "logic/gate.h"

Gate::Gate(int x, int y, bool signal, int truth) :
    Cell(x, y, signal), truth(truth), name(getName())
{}
Gate::Gate(int x, int y, bool signal, char t) :
    Cell(x, y, signal), truth((t=='|') ? OR : AND), name(getName())
{
    if (t!='&' && t!='|')
        throw "Cannot create a Gate with this symbol";
}

Gate::Gate(string expression) :
    Cell(0,0,0), truth(8), name("")
{
    stringstream stream(expression);

    while(!stream.eof() && stream.peek()!='(') {
        stream.ignore();
    }
    stream.ignore();

    int n[4];
    char c=' ';
    for (int i=0; i<4; i++) {
        if (stream.peek()=='&' || stream.peek()=='|')
            stream >> c;
        else
            stream >> n[i];
        while(stream.peek()==' ') stream.ignore();
        stream.ignore();
    }
    x = n[0];
    y = n[1];
    signal = n[2];
    if (c==' ') {
        truth = n[3];
    } else {
        truth = (c=='|') ? OR : AND;
    }
    name = getName();
}

bool Gate::compute() const
{
    bool a = received[0]->signal, b = received[1]->signal;
    if (a&b) {
        return (truth & 8) >> 3;
    } else if (a) {
        return (truth & 2) >> 1;
    } else if (b) {
        return (truth & 4) >> 2;
    } else {
        return truth & 1;
    }
}

string Gate::getType() const
{
    return "Gate";
}

string Gate::toString() const
{
    stringstream stream;
    stream << getType() << "<" << getName() << ">(" << x << "," << y << "," << signal << "," << truth << ")";
    return stream.str();
}

string Gate::toPath() const
{
    stringstream stream;
    stream << getType() << "-" << getName() << "-" << signal;
    return stream.str();
}

string Gate::getName() const
{
    switch(truth) {
    case AND:
        return "AND";
        break;
    case OR:
        return "OR";
        break;
    case NAND:
        return "NAND";
        break;
    case NOR:
        return "NOR";
        break;
    case XOR:
        return "XOR";
        break;
    case XNOR:
        return "XNOR";
        break;
    default:
        return "???";
        break;
    }
}

void Gate::resetSignal()
{
    received.clear();
    signal = 0;
}

void Gate::receiveSignal(const Cell *c)
{
    if (received.size()>=2)
        throw "Too many inputs for a gate";
    received.push_back(const_cast<Cell *>(c));
    if (received.size()==2)
        signal = compute();
}

void Gate::propagateSignal( vector< CISpointer<Cell> >& cells) const
{
    vector< CISpointer<Cell> >::iterator it;
    for (it=cells.begin(); it!=cells.end(); ++it) {
        if (*it!=0 && !(&**it==&*received[0] || &**it==&*received[1]) ) {
            (*it)->receiveSignal(this);
        }
    }
}

bool Gate::isReady()
{
    if (received.size()>2)
        received.clear();
    return received.size()==2;
}

void Gate::operator&(const Base* b)
{
    if (b->getType()!="Gate")
        undefined();
    const Gate *g = static_cast<const Gate*>(b);
    truth = truth & g->truth; // &g.truth^FULL
}

void Gate::operator|(const Base* b)
{
    if (b->getType()!="Gate")
        undefined();
    const Gate *g = static_cast<const Gate*>(b);
    truth = truth | g->truth;
}

void Gate::operator!()
{
    truth = truth^FULL;
}
