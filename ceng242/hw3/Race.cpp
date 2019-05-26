#include "Race.h"

#include "Utilizer.h"

#include <vector>
#include <algorithm>
#include <iomanip>
#include <iostream>

/*
YOU MUST WRITE THE IMPLEMENTATIONS OF THE REQUESTED FUNCTIONS
IN THIS FILE. START YOUR IMPLEMENTATIONS BELOW THIS LINE 
*/

Race::Race (std::string race_name) : race_name (race_name), average_laptime (Laptime (Utilizer::generateAverageLaptime()))
{
    // std::cout << average_laptime.getLaptime () << "\n";
    head = nullptr;
}

Race::Race (const Race& rhs) : average_laptime (rhs.average_laptime)
{
    race_name = rhs.race_name;


    if (rhs.head != nullptr)
    {
        head = new Car (*rhs.head);
        while (head->getNumberOfLaps ()) head->popLaptime ();

        Car *prev = head;
        for (Car *t = rhs.head->getNext (); t != nullptr; t = t->getNext ())
        {
            Car *temp = new Car (*t);
            while (temp->getNumberOfLaps ()) temp->popLaptime ();
            prev->addCar (temp);
            prev = prev->getNext ();
        }
    }
}

Race::~Race () // pay attention
{
    // std::cerr << "Race Destructor: " << race_name << "\n";
    Car *t;
    for (t = head; t != nullptr;)
    {
        Car *temp = t;
        t = t->getNext ();
        delete temp;
    }
    // std::cerr << "End Race Destructor\n";
}

std::string Race::getRaceName () const
{
    return race_name;
}

void Race::addCartoRace ()
{
    std::default_random_engine generator;
    std::uniform_int_distribution <int> distribution ('a', 'z');

    // distribution (generator);

    std::string driver_name = "aaa bbb";

    driver_name[0] = distribution (generator) + 'A'-'a';
    driver_name[1] = distribution (generator); driver_name[2] = distribution (generator);

    driver_name[5] = distribution (generator) + 'A'-'a';
    driver_name[6] = distribution (generator); driver_name[7] = distribution (generator);

    Car *added = new Car (driver_name);

    if (head == nullptr)
    {
        head = added;
    }
    else
    {
        for (Car *temp = head; temp != nullptr; temp = temp->getNext ())
        {
            if (temp->getNext () == nullptr)
            {
                temp->addCar (added);
                break;
            }
        }
    }
}

void Race::addCartoRace (Car& car) // problem here, add directly without of a copy
{
    // std::cerr << "addCartoRace: " << car << std::endl;
    Car *added = new Car (car);
    if (head == nullptr)
    {
        head = added;
    }
    else if (car < *head)
    {
        head = added;
    }
    else for (Car *temp = head; temp != nullptr; temp = temp->getNext ())
    {
        if (temp->getNext () == nullptr)
        {
            temp->addCar (added);
            break;
        }
        else if (car < *(temp->getNext ()))
        {
            car.addCar (temp->getNext ());
            temp->addCar (added);
            break;
        }
    }
}

int Race::getNumberOfCarsinRace () const
{
    int ans = 0;
    for (Car *temp = head; temp != nullptr; temp = temp->getNext (), ++ ans);
    return ans;
}

void Race::goBacktoLap (int lap)
{
    for (Car *t = head; t != nullptr; t = t->getNext ())
    {
        while (t->getNumberOfLaps () > lap+1) t->popLaptime ();
    }

    sortCars ();
}

void Race::operator++ ()
{
    if (head == nullptr) return;

    for (Car *temp = head; temp != nullptr; temp = temp->getNext ())
    {
        temp->Lap (average_laptime);
    }

    sortCars ();
}

void Race::operator-- ()
{
    if (head == nullptr) return;

    for (Car *temp = head; temp != nullptr; temp = temp->getNext ())
    {
        temp->popLaptime ();
    }

    sortCars ();
}


Car Race::operator[] (const int car_in_position)
{
    Car *temp = head;
    for (int i = 0; i < car_in_position; ++ i) temp = temp->getNext ();
    return *temp;
}

Car Race::operator[] (std::string driver_name)
{
    for (Car *t = head; t != nullptr; t = t->getNext ())
    {
        if (t->getDriverName () == driver_name)
        {
            return *t;
        }
    }
}

Race& Race::operator= (const Race& rhs)
{
    race_name = rhs.race_name;
    average_laptime = rhs.average_laptime;

    for (Car *t = head; t != nullptr;)
    {
        Car *temp = t;
        t = t->getNext ();
        delete temp;
    }
    if (rhs.head == nullptr) return *this;

    head = new Car (*rhs.head);
    Car *prev = head;
    for (Car *t = rhs.head->getNext (); t != nullptr; t = t->getNext ())
    {
        Car *temp = new Car (*t);
        prev->addCar (temp);
        prev = prev->getNext ();
    }
}


std::ostream& operator<<(std::ostream& os, const Race& race)
{
    std::vector <int> scores {25, 18, 15, 12, 10, 8, 6, 4, 2, 1};
    int n = race.getNumberOfCarsinRace (), i = 0;
    int d = n; n=0; while (d) {d/=10; ++ n;}

    Laptime bst (2020202020);

    for (Car *t = race.head; t != nullptr; t = t->getNext ())
    {
        Laptime temp = t->getBestLaptime ();
        if (temp < bst)
        {
            bst = temp;
        }
    }

    for (Car *t = race.head; t != nullptr; t = t->getNext (), ++ i)
    {
        os << std::setfill ('0') << std::setw (n) << i+1 << "--";
        os << t->getDriverNameShort () << "--";
        os << t->getLatestLaptime () << "--" << t->getBestLaptime () << "--" << t->getTotalLaptime ();
        if (i < 10)
        {
            os << "--" << scores[i];
            // std::cerr << "((" << t->getBestLaptime ().getLaptime () << " " << bst.getLaptime () << "))\n";
            if (t->getBestLaptime ().getLaptime () == bst.getLaptime () && t->getBestLaptime ().getLaptime () > 0)
            {
                os << "--1";
            }
        }
        else os << "--0";
        os << "\n";
    }
    return os;
}

void Race::sortCars ()
{
    if (head == nullptr) return;

    std::vector <Car*> v;

    for (Car *temp = head; temp != nullptr; temp = temp->getNext ())
    {
        v.push_back (temp);
    }

    std::sort (v.begin (), v.end (), [](Car* a, Car* b) {return *a < *b;});

    head = v[0];
    for (int i = 0; i < v.size ()-1; ++ i)
    {
        v[i]->addCar (v[i+1]);
    }
    (*v.rbegin ())->addCar (nullptr);
}

std::string Race::getFastestDriver ()
{
    // std::cout << "getFastestDriver() : " << race_name << "\n";
    Laptime bst (2020202020);
    std::string ans;

    for (Car *t = head; t != nullptr; t = t->getNext ())
    {
        Laptime cur (t->getBestLaptime ());
        // std::cout << " " << t->getDriverNameShort () << " : " << cur << "\n";
        if (cur < bst)
        {
            bst = cur;
            ans = t->getDriverNameShort ();
        }
    }

    return ans;
}