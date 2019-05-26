#include "Championship.h"

#include <map>
#include <algorithm>
#include <iomanip>
#include <iostream>

/*
YOU MUST WRITE THE IMPLEMENTATIONS OF THE REQUESTED FUNCTIONS
IN THIS FILE. START YOUR IMPLEMENTATIONS BELOW THIS LINE 
*/

Championship::Championship () {}

Championship::Championship (const Championship& rhs) 
{
    races.resize (rhs.races.size ());
    for (int i = 0; i < rhs.races.size (); ++ i)
    {
        Race *temp = new Race (*rhs.races[i]);
        races[i] = temp;
    }
}

Championship::~Championship ()
{
    for (int i = 1; i < races.size (); ++ i)
    {
        delete races[i];
    }
}

void Championship::addNewRace (Race& race)
{
    races.push_back (&race);
}

void Championship::addNewRace (std::string race_name)
{
    Race *temp = new Race (*races[0]);
    temp->setRaceName (race_name);
    temp->setAverageLaptime (Utilizer::generateAverageLaptime ());
    races.push_back (temp);
}

void Championship::removeRace (std::string race_name)
{
    for (auto it = races.begin (); it != races.end (); ++ it)
    {
        if ((*it)->getRaceName () == race_name)
        {
            if (it != races.begin ()) delete (*it);
            races.erase (it);
            return;
        }
    }
}

void Championship::addLap (std::string race_name)
{
    for (auto it = races.begin (); it != races.end (); ++ it)
    {
        if ((*it)->getRaceName () == race_name)
        {
            ++ (**it);
            return;
        }
    }
}

Race& Championship::operator[] (std::string race_name)
{
    for (auto it = races.begin (); it != races.end (); ++ it)
    {
        if ((*it)->getRaceName () == race_name)
        {
            return **it;
        }
    }
}

std::ostream& operator<< (std::ostream& os, const Championship& championship)
{
    if (championship.races.size () == 0) return os;
    std::vector <int> scores {25, 18, 15, 12, 10, 8, 6, 4, 2, 1};

    std::map <std::string, int> mp;

    for (int i = 0; i < championship.races.size (); ++ i)
    {
        // std::cerr << "i: " << i << "\n";
        for (int j = 0; j < championship.races[i]->getNumberOfCarsinRace (); ++ j)
        {
            // std::cerr << "   j: " << j << "\n";
            int score = (j<10?scores[j]:0);
            Race *temp = championship.races[i];
            // std::cerr << "   driver_name: " << temp[j].getDriverNameShort () << "\n";
            mp[(*temp)[j].getDriverNameShort ()] += score;

            if ((*temp)[j].getDriverNameShort () == temp->getFastestDriver ())
            {
                ++ mp[(*temp)[j].getDriverNameShort ()];
            }
        }
    }

    std::vector <std::pair <int, std::string> > v;
    for (auto it: mp)
    {
        v.push_back ({it.second, it.first});
    }

    std::sort (v.begin (), v.end ());
    std::reverse (v.begin (), v.end ());

    int n = championship.races[0]->getNumberOfCarsinRace ();
    int d = n; n = 0; while (d) {d/=10; ++ n;}

    for (int i = 0; i < v.size (); ++ i)
    {
        os << std::setfill ('0') << std::setw (n) << i+1 << "--";
        os << v[i].second << "--" << v[i].first << std::endl;
    }

    return os;
}
