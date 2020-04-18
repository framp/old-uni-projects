#ifndef VALIDATOR_H
#define VALIDATOR_H

#include <sstream>
using namespace std;

class Validator
{
private:
    string pattern;
    int position;
    bool whitespace;

    string matched;

    void incrementPosition();
public:
    Validator(string&, string);
    string result();
};

#endif // VALIDATOR_H
