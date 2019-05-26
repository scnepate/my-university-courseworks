#include"Scout.h"

/*
YOU MUST WRITE THE IMPLEMENTATIONS OF THE REQUESTED FUNCTIONS
IN THIS FILE. START YOUR IMPLEMENTATIONS BELOW THIS LINE
*/
 Scout::~Scout () {}

 Scout::Scout (uint id, int x, int y, Team team) : Player (id, x, y, team), attack_damage (25), heal_power (0), max_hp (125)
 {
    goals = {CHEST,TO_ALLY,ATTACK};
    HP = max_hp;
    abbrevation = (team==BARBARIANS?"SC":"sc");
 }


 int Scout::getAttackDamage () const
 {
    return attack_damage;
 }

 int Scout::getHealPower () const
 {
     return heal_power;
 }

 int Scout::getMaxHP () const
 {
     return max_hp;
 }

 std::vector <Goal> Scout::getGoalPriorityList ()
 {
     return goals;
 }

const std::string Scout::getClassAbbreviation () const
{
    return abbrevation;
}

std::vector <Coordinate> Scout::getAttackableCoordinates ()
{
    return getMoveableCoordinates ();
}

std::vector <Coordinate> Scout::getMoveableCoordinates ()
{
    std::vector <Coordinate> v;

    v.push_back (coordinate + Coordinate (1, 0));
    v.push_back (coordinate + Coordinate (-1, 0));
    v.push_back (coordinate + Coordinate (0, 1));
    v.push_back (coordinate + Coordinate (0, -1));
    v.push_back (coordinate + Coordinate (1, 1));
    v.push_back (coordinate + Coordinate (1, -1));
    v.push_back (coordinate + Coordinate (-1, 1));
    v.push_back (coordinate + Coordinate (-1, -1));

    return v;
}

std::vector <Coordinate> Scout::getHealableCoordinates ()
{
    return {};
}