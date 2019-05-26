#include"Fighter.h"

/*
YOU MUST WRITE THE IMPLEMENTATIONS OF THE REQUESTED FUNCTIONS
IN THIS FILE. START YOUR IMPLEMENTATIONS BELOW THIS LINE
*/

 Fighter::~Fighter () {}

 Fighter::Fighter (uint id, int x, int y, Team team) : Player (id, x, y, team), attack_damage (100), heal_power (0), max_hp (400)
 {
     goals = {ATTACK, TO_ENEMY, CHEST};
     HP = max_hp;
     abbrevation = (team==BARBARIANS?"FI":"fi");
 }


 int Fighter::getAttackDamage () const
 {
     return attack_damage;
 }

 int Fighter::getHealPower () const
 {
     return heal_power;
 }

 int Fighter::getMaxHP () const
 {
     return max_hp;
 }

 std::vector <Goal> Fighter::getGoalPriorityList ()
 {
     return goals;
 }

const std::string Fighter::getClassAbbreviation () const
{
    return abbrevation;
}

std::vector <Coordinate> Fighter::getAttackableCoordinates ()
{
    std::vector <Coordinate> v;

    v.push_back (coordinate + Coordinate (1, 0));
    v.push_back (coordinate + Coordinate (-1, 0));
    v.push_back (coordinate + Coordinate (0, 1));
    v.push_back (coordinate + Coordinate (0, -1));

    return v;
}

std::vector <Coordinate> Fighter::getMoveableCoordinates ()
{
    return getAttackableCoordinates ();
}

std::vector <Coordinate> Fighter::getHealableCoordinates ()
{
    return {};
}