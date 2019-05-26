#include"Priest.h"

/*
YOU MUST WRITE THE IMPLEMENTATIONS OF THE REQUESTED FUNCTIONS
IN THIS FILE. START YOUR IMPLEMENTATIONS BELOW THIS LINE
*/

 Priest::~Priest () {}

 Priest::Priest (uint id, int x, int y, Team team) : Player (id, x, y, team), attack_damage (0), heal_power (50), max_hp (150)
 {
    goals = {HEAL,TO_ALLY,CHEST};
    HP = max_hp;
    abbrevation = (team==BARBARIANS?"PR":"pr");
 }


 int Priest::getAttackDamage () const
 {
    return attack_damage;
 }

 int Priest::getHealPower () const
 {
     return heal_power;
 }

 int Priest::getMaxHP () const
 {
     return max_hp;
 }

 std::vector <Goal> Priest::getGoalPriorityList ()
 {
     return goals;
 }

const std::string Priest::getClassAbbreviation () const
{
    return abbrevation;
}

std::vector <Coordinate> Priest::getAttackableCoordinates ()
{
    return {};
}

std::vector <Coordinate> Priest::getMoveableCoordinates ()
{
    std::vector <Coordinate> v;

    v.push_back (coordinate + Coordinate (-1, 0));
    v.push_back (coordinate + Coordinate (1, 0));
    v.push_back (coordinate + Coordinate (0, -1));
    v.push_back (coordinate + Coordinate (0, 1));
    v.push_back (coordinate + Coordinate (1, 1));
    v.push_back (coordinate + Coordinate (-1, -1));
    v.push_back (coordinate + Coordinate (1, -1));
    v.push_back (coordinate + Coordinate (-1, 1));

    return v;
}

std::vector <Coordinate> Priest::getHealableCoordinates ()
{
    return getMoveableCoordinates ();
}