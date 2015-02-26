#include <iostream>
#include <string>

#include "debug.hpp"

using namespace std;

Debug::Debug(bool on)
{
    this->on = on;
}

Debug::~Debug()
{
}

void Debug::print(string text)
{
    if(on)
    {
        cout << "[DEBUG]: " << text << endl;
    }
}

void Debug::swap()
{
    on = !on;
}
