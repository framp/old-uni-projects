#ifndef GATE_H
#define GATE_H
#include "logic/cell.h"

// Using the first 4 bits of truth as a truth table
// A | B | T
// 0   0   x
// 1   0   x
// 0   1   x
// 1   1   x
//
// 8 = 1000, 4 = 0100, 2 = 0010, 1 = 0001

#define AND 8
#define OR (2|4|8)
#define NAND (1|2|4)
#define NOR 1
#define XOR (2|4)
#define XNOR (1|8)
#define FULL (1|2|4|8)


class Gate : public Cell
{
private:
    int truth;
    string name;
    vector<CISpointer<Cell> > received;
    bool compute() const;

public:
    Gate(int, int, bool = 0, int = 8);
    Gate(int, int, bool = 0, char = '&');
    Gate(string);

    virtual string getType() const;
    virtual string toString() const;
    virtual string toPath() const;
    string getName() const;

    virtual void resetSignal();
    virtual void receiveSignal(const Cell *);
    virtual void propagateSignal( vector< CISpointer<Cell> >&) const;
    virtual bool isReady();

    virtual void operator&(const Base*);
    virtual void operator|(const Base*);
    virtual void operator!();

};

#endif // GATE_H
