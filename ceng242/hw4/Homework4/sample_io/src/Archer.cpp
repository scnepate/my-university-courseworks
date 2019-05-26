#include"Archer.h"

/*
YOU MUST WRITE THE IMPLEMENTATIONS OF THE REQUESTED FUNCTIONS
IN THIS FILE. START YOUR IMPLEMENTATIONS BELOW THIS LINE
*/

 Archer::~Archer () {}

 Archer::Archer (uint id, int x, int y, Team team) : Player (id, x, y, team), attack_damage (50), heal_power (0), max_hp (200)
 {
     goals = {ATTACK};
     HP = max_hp;
     abbrevation = (team==BARBARIANS?"AR":"ar");
 }

 int Archer::getAttackDamage () const
 {
     return attack_damage;
 }

 int Archer::getHealPower () const
 {
     return heal_power;
 }

 int Archer::getMaxHP () const
 {
     return max_hp;
 }

 std::vector <Goal> Archer::getGoalPriorityList ()
 {
     return goals;
 }

const std::string Archer::getClassAbbreviation () const
{
    return abbrevation;
}

std::vector <Coordinate> Archer::getAttackableCoordinates ()
{
    std::vector <Coordinate> v;

    for (int i = 1; i <= 2; ++ i)
    {
        v.push_back (coordinate + Coordinate (i, 0));
        v.push_back (coordinate + Coordinate (-i, 0));
        v.push_back (coordinate + Coordinate (0, i));
        v.push_back (coordinate + Coordinate (0, -i));
    }

    return v;
}

std::vector <Coordinate> Archer::getMoveableCoordinates ()
{
    return {};
}

std::vector <Coordinate> Archer::getHealableCoordinates ()
{
    return {};
}