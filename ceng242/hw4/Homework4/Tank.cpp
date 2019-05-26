#include"Tank.h"

/*
YOU MUST WRITE THE IMPLEMENTATIONS OF THE REQUESTED FUNCTIONS
IN THIS FILE. START YOUR IMPLEMENTATIONS BELOW THIS LINE
*/
Tank::~Tank () {}

Tank::Tank (uint id, int x, int y, Team team) : Player (id, x, y, team), attack_damage (25), heal_power (0), max_hp (1000)
 {
    goals = {TO_ENEMY,ATTACK,CHEST};
    HP = max_hp;
    abbrevation = (team==BARBARIANS?"TA":"ta");
 }


 int Tank::getAttackDamage () const
 {
    return attack_damage;
 }

 int Tank::getHealPower () const
 {
     return heal_power;
 }

 int Tank::getMaxHP () const
 {
     return max_hp;
 }

 std::vector <Goal> Tank::getGoalPriorityList ()
 {
     return goals;
 }

const std::string Tank::getClassAbbreviation () const
{
    return abbrevation;
}

std::vector <Coordinate> Tank::getAttackableCoordinates ()
{
    return getMoveableCoordinates ();
}

std::vector <Coordinate> Tank::getMoveableCoordinates ()
{
    std::vector <Coordinate> v;

    v.push_back (coordinate + Coordinate (-1, 0));
    v.push_back (coordinate + Coordinate (1, 0));
    v.push_back (coordinate + Coordinate (0, -1));
    v.push_back (coordinate + Coordinate (0, 1));

    return v;
}

std::vector <Coordinate> Tank::getHealableCoordinates ()
{
    return {};
}