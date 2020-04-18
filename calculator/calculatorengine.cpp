#include "calculator/calculatorengine.h"

CalculatorEngine::CalculatorEngine():
    op(""), numbers(0)
{}

string CalculatorEngine::addObject(string expression, string &error)
{
    try {
        if (validateObjects(expression, &results)) {
            return results.back()->toString();
        }
        error = "Not recognized object";
    } catch(const char * e) {
        error = e;
    }

    return "";
}

bool CalculatorEngine::setOperator(string o, int n)
{
    if (op=="") {
        op = o;
        numbers = n;
        return true;
    } else {
        return false;
    }
}

CISpointer<Base> CalculatorEngine::computeResult(string & error)
{
    CISpointer<Base> result;
    try {
        switch (numbers) {
        case 1:
            if(op=="TICK") {
                results[0]->tick();
            } else if (op=="!") {
                !*results[0];
            } else if(op=="RESET") {
                results[0]->reset();
            }
            break;
        case 2:
            if (op=="<<") {
                *results[0] << &*results[1];
            } else if(op==">>") {
                *results[0] >> &*results[1];
            } else if (op=="+") {
                *results[0] + &*results[1];
            } else if (op=="-") {
                *results[0] - &*results[1];
            } else if (op=="&") {
                *results[0] & &*results[1];
            } else if (op=="|") {
                *results[0] | &*results[1];
            }
            break;
        }
    } catch(const char * e) {
        error = e;
    }

    return results[0];
}

void CalculatorEngine::clear()
{
    results.clear();
    op = "";
    numbers = 0;
}

bool CalculatorEngine::isReady()
{
    return results.size()==(unsigned)numbers && numbers!=0;
}

bool CalculatorEngine::validateGrid(string &expression, vector<CISpointer<Base> > *add)
{

    string result = expression;
    if (Validator(expression, "[$,$,$,[").result()=="") return false;

    int size = expression.size(), counter = 0;
    while(expression.size()>0 && counter<2) {
        if ((unsigned)size==expression.size()) {
            counter++;
        } else {
            size = expression.size();
        }
        while(expression[0]==' ') expression = expression.substr(1);
        if (expression[0]==',') expression = expression.substr(1);
        if (expression[0]==']') break;
        if (!validateClock(expression) &&
                !validateFlipFlop(expression) &&
                !validateGate(expression) &&
                !validateInverter(expression) &&
                !validateInput(expression) &&
                !validateOutput(expression) &&
                !validateWire(expression)) return false;
    }
    if (Validator(expression, "]]").result()=="") return false;

    if (add!=0)
        add->push_back(new Grid(result));
    return true;
}

bool CalculatorEngine::validateVector(string &expression, vector<CISpointer<Base> > *add)
{
    string result = Validator(expression, """Vector""($,$)").result();
    if (result=="") return false;
    if (add!=0)
        add->push_back(new Vector(result));
    return true;

}

bool CalculatorEngine::validateClock(string &expression, vector<CISpointer<Base> > *add)
{
    string result = Validator(expression, """Clock""($,$,$,$,$)").result();
    if (result=="") return false;
    if (add!=0)
        add->push_back(new Clock(result));
    return true;

}

bool CalculatorEngine::validateFlipFlop(string &expression, vector<CISpointer<Base> > *add)
{
    string result = Validator(expression, """FlipFlop""($,$,$)").result();
    if (result=="") return false;
    if (add!=0)
        add->push_back(new FlipFlop(result));
    return true;
}

bool CalculatorEngine::validateGate(string &expression, vector<CISpointer<Base> > *add)
{
    string result = Validator(expression, """Gate""($,$,$,%&)").result();
    if (result=="")
        result = Validator(expression, """Gate""($,$,$,%|)").result();
    if (result=="")
        result = Validator(expression, """Gate""?(($,$,$,$)").result();
    if (result=="") return false;
    if (add!=0)
        add->push_back(new Gate(result));
    return true;
}

bool CalculatorEngine::validateInverter(string &expression, vector<CISpointer<Base> > *add)
{
    string result = Validator(expression, """Inverter""($,$,$)").result();
    if (result=="") return false;
    if (add!=0)
        add->push_back(new Inverter(result));
    return true;

}

bool CalculatorEngine::validateInput(string &expression, vector<CISpointer<Base> > *add)
{
    string result = Validator(expression, """Input""($,$,$)").result();
    if (result=="") return false;
    if (add!=0)
        add->push_back(new Input(result));
    return true;

}

bool CalculatorEngine::validateOutput(string &expression, vector<CISpointer<Base> > *add)
{
    string result = Validator(expression, """Output""($,$,$)").result();
    if (result=="") return false;
    if (add!=0)
        add->push_back(new Output(result));
    return true;
}

bool CalculatorEngine::validateWire(string &expression, vector<CISpointer<Base> > *add)
{
    string result = Validator(expression, """Wire""($,$,$)").result();
    if (result=="") return false;
    if (add!=0)
        add->push_back(new Wire(result));
    return true;
}

bool CalculatorEngine::validateObjects(string expression, vector<CISpointer<Base> > *add)
{
    return validateGrid(expression, add) ||
           validateVector(expression, add) ||
           validateClock(expression, add) ||
           validateFlipFlop(expression, add) ||
           validateGate(expression, add) ||
           validateInverter(expression, add) ||
           validateInput(expression, add) ||
           validateOutput(expression, add) ||
           validateWire(expression, add);
}

string CalculatorEngine::getType(string expression)
{
    if (expression=="")
        return "Empty";
    vector<CISpointer<Base> > v(1);
    string result = "Undefined";
    try {
        if (validateObjects(expression, &v)) {
            result = v.back()->getType();
        }
    } catch(const char * e) {
        stringstream stream("Error(");
        stream << e << ")";
        result = stream.str();
    }
    return result;
}
