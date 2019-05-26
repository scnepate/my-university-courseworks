#include "Laptime.h"

#include <iomanip>

/*
YOU MUST WRITE THE IMPLEMENTATIONS OF THE REQUESTED FUNCTIONS
IN THIS FILE. START YOUR IMPLEMENTATIONS BELOW THIS LINE 
*/

Laptime::Laptime (int laptime) : laptime (laptime)
{
    next = nullptr;
}

Laptime::Laptime (const Laptime& rhs)
{
    laptime = rhs.laptime;
    next = rhs.next;
}

Laptime::~Laptime () {}

void Laptime::addLaptime (Laptime *next)
{
    this->next = next;
}

Laptime* Laptime::getNext () const
{
    return next;
}

int Laptime::getLaptime () const
{
    return laptime;
}

bool Laptime::operator< (const Laptime& rhs) const
{
    return laptime < rhs.laptime;
}

bool Laptime::operator> (const Laptime& rhs) const
{
    return laptime > rhs.laptime;
}

Laptime& Laptime::operator+ (const Laptime& rhs)
{
    laptime += rhs.laptime;
    return *this;
}

std::ostream& operator<< (std::ostream& os, const Laptime& laptime)
{
    os << laptime.laptime/60000 << ":";
    os << std::setfill ('0') << std::setw(2) << laptime.laptime%60000/1000 << ".";
    os << std::setfill ('0') << std::setw(3) << laptime.laptime%1000;
    return os;
}