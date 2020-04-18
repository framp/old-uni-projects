#include "logic/base.h"

Base::Base() :
    references(0)
{
}

void Base::undefined() const
{
    throw "Undefined operation";
}

void Base::operator<<(Base *)
{
    undefined();
}

void Base::operator>>(Base *)
{
    undefined();
}

void Base::operator+(const Base*)
{
    undefined();
}

void Base::operator-(const Base*)
{
    undefined();
}

void Base::operator&(const Base*)
{
    undefined();
}

void Base::operator|(const Base*)
{
    undefined();
}

void Base::operator!()
{
    undefined();
}

void Base::tick()
{
    undefined();
}

void Base::reset()
{
    undefined();
}

Base::~Base()
{
}
