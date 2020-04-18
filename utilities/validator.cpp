#include "utilities/validator.h"

Validator::Validator(string &expression, string pattern) :
    position(-1), whitespace(true),
    matched("")
{
    int patternSize = pattern.size()-1;
    int tempN;
    char tempC;
    stringstream stream(expression);
    while(position<patternSize) {
        incrementPosition();
        if (whitespace)
            while(stream.peek()==' ') stream.ignore();

        if (pattern[position] == '?') {
            incrementPosition();
            while(stream.peek()!=pattern[position]) stream.ignore();
        } else if (pattern[position] == '$') {
            if (!(stream >> tempN)) return;
        } else if (pattern[position] == '%') {
            incrementPosition();
            if (!(stream >> tempC) || pattern[position]!=tempC) return;
        } else {
            if (stream.peek()!=pattern[position]) return;
            stream.ignore();
        }
    }


    if (stream.tellg()<0) {
        matched = expression;
        expression = "";
    } else {
        matched = expression.substr(0, stream.tellg());
        expression = expression.substr(stream.tellg());
    }
}

void Validator::incrementPosition()
{
    ++position;
    if (pattern[position] == '"') {
        whitespace = !whitespace;
        ++position;
    }
}

string Validator::result()
{
    return matched;
}
