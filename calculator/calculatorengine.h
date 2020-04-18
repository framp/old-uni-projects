#ifndef CALCULATORENGINE_H
#define CALCULATORENGINE_H
#include "logic/grid.h"
#include "utilities/validator.h"

class CalculatorEngine
{
private:
    string op;
    int numbers;
    vector<CISpointer<Base> > results;

public:
    CalculatorEngine();
    CISpointer<Base> computeResult(string &);
    string addObject(string, string&);
    bool setOperator(string, int);
    void clear();
    bool isReady();

    bool validateGrid(string &, vector<CISpointer<Base> >* = 0);
    bool validateVector(string &, vector<CISpointer<Base> >* = 0);
    bool validateClock(string &, vector<CISpointer<Base> >* = 0);
    bool validateFlipFlop(string &, vector<CISpointer<Base> >* = 0);
    bool validateGate(string &, vector<CISpointer<Base> >* = 0);
    bool validateInverter(string &, vector<CISpointer<Base> >* = 0);
    bool validateInput(string &, vector<CISpointer<Base> >* = 0);
    bool validateOutput(string &, vector<CISpointer<Base> >* = 0);
    bool validateWire(string &, vector<CISpointer<Base> >* = 0);

    bool validateObjects(string, vector<CISpointer<Base> >* = 0);
    string getType(string);
};

#endif // CALCULATORENGINE_H
