#include"Player.h"

/*
YOU MUST WRITE THE IMPLEMENTATIONS OF THE REQUESTED FUNCTIONS
IN THIS FILE. START YOUR IMPLEMENTATIONS BELOW THIS LINE
*/

Player::Player (uint id, int x, int y, Team team) : coordinate(Coordinate(x, y)), id (id), team(team) {}

uint Player::getID () const {return id;}

const Coordinate& Player::getCoord () const {return coordinate;}

int Player::getHP () const {return HP;}

Team Player::getTeam () const {return team;}

std::string Player::getBoardID ()
{
    if (id < 10) return std::string ("0") + std::to_string (id);
    else return std::to_string (id);
}

bool Player::attack (Player *enemy)
{
    std::cout << "Player " << getBoardID () << " attacked Player " << enemy->getBoardID () << " ";
    enemy->HP -= getAttackDamage ();
    std::cout << "(" << getAttackDamage () << ")\n";
    return enemy->isDead ();
}

void Player::heal (Player *ally)
{
    std::cout << "Player " << getBoardID () << " healed Player " << ally->getBoardID () << "\n";
    ally->HP = std::min (ally->getMaxHP (), ally->getHP () + getHealPower ());
}

void Player::movePlayerToCoordinate (Coordinate c)
{
    std::cout << "Player " << getBoardID () << " moved from " << coordinate << " to " << c << std::endl;
    coordinate = c;
}

bool Player::isDead () const
{
    return (HP <= 0);
}