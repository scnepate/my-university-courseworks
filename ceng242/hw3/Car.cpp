#include "Car.h"
#include "Utilizer.h"

#include <iostream>
#include <cctype>

const int MAX_LAPTIME = 2020202020;

/*
YOU MUST WRITE THE IMPLEMENTATIONS OF THE REQUESTED FUNCTIONS
IN THIS FILE. START YOUR IMPLEMENTATIONS BELOW THIS LINE 
*/

Car::Car (std::string driver_name) : driver_name (driver_name)
{
    head = nullptr;
    next = nullptr;
    performance = Utilizer::generatePerformance ();

    int pos = driver_name.find (' ');
    for (int i = pos+1; i <= pos+3; ++ i)
        driver_name_short += toupper (driver_name[i]);
    
    // std::cerr << "Car Constructor: " << driver_name << " " << performance << " " << driver_name_short << std::endl;
}

Car::Car (const Car& rhs) // deep copy: v
{
    driver_name = rhs.driver_name;
    driver_name_short = rhs.driver_name_short;
    performance = rhs.performance;
    next = rhs.next;

    if (rhs.head == nullptr) head = nullptr;
    else
    {
        head = new Laptime (*rhs.head);
        Laptime *prev = head;
        for (Laptime *t = rhs.head->getNext (); t != nullptr; t = t->getNext ())
        {
            Laptime *temp = new Laptime (*t);
            prev->addLaptime (temp);
            prev = prev->getNext ();
        }
    }
    // std::cerr << "Car Copy Constructor: " << driver_name << " " << performance << " " << driver_name_short << std::endl;
}

Car::~Car ()
{
    // std::cerr << "Car Destructor: " << driver_name << std::endl;
    for (Laptime *temp = head; temp != nullptr;)
    {
        Laptime *t = temp;
        temp = temp->getNext ();
        delete t;
    }
}

std::string Car::getDriverName () const
{
    return driver_name;
}

double Car::getPerformance () const
{
    return performance;
}

void Car::addCar (Car *next)
{
    this->next = next;
}

bool Car::operator< (const Car& rhs) const
{
    return getTotalLaptime () < rhs.getTotalLaptime ();
}

bool Car::operator> (const Car& rhs) const
{
    return getTotalLaptime () > rhs.getTotalLaptime ();
}

Laptime Car::operator[](const int lap) const
{
    int i = 0;
    for (Laptime *temp = head; temp != nullptr; temp = temp->getNext (), ++ i)
    {
        if (i == lap)
        {
            return *temp;
        }
    }

    return Laptime (0);
}

 void Car::Lap (const Laptime& average_laptime)
 {
    Laptime *added = new Laptime (Utilizer::generateLaptimeVariance(performance));
    *added + average_laptime;

    if (head == nullptr)
    {
        head = added;
    }
    else
    {
        Laptime *temp;
        for (temp = head; temp->getNext () != nullptr; temp = temp->getNext ());
        temp->addLaptime (added);
    }
 }

std::ostream& operator<<(std::ostream& os, const Car& car)
{
    os << car.driver_name_short << "--" << car.getLatestLaptime () << "--" << car.getBestLaptime () << "--" << car.getTotalLaptime ();
    return os;
}


Laptime Car::getTotalLaptime () const
{
    Laptime t (0);
    for (Laptime *temp = head; temp != nullptr; temp = temp->getNext ())
    {
        t + *temp;
    }

    return t;
}
Laptime Car::getBestLaptime () const
{
    if (head == nullptr) return Laptime (0);
    Laptime t (MAX_LAPTIME);
    for (Laptime *temp = head; temp != nullptr; temp = temp->getNext ())
    {
        if (*temp < t)
        {
            t = *temp;
        }
    }
    return t;
}
Laptime Car::getLatestLaptime () const
{
    Laptime *t;
    for (Laptime *t = head; t != nullptr; t = t->getNext ())
    {
        if (t->getNext () == nullptr)
        {
            return *t;
        }
    }
    return Laptime (0);
}

int Car::getNumberOfLaps () const
{
    int ans = 0;
    for (Laptime *temp = head; temp != nullptr; temp = temp->getNext (), ++ ans);
    return ans;
}

void Car::popLaptime ()
{
    if (head == nullptr) return;
    if (head->getNext () == nullptr)
    {
        delete head;
        head = nullptr;
        return;
    }
    Laptime *temp;
    for (temp = head; temp->getNext ()->getNext () != nullptr; temp = temp->getNext ());
    delete temp->getNext ();
    temp->addLaptime (nullptr);
}