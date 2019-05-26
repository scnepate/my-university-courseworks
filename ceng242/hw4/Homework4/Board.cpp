#include"Board.h"

/*
YOU MUST WRITE THE IMPLEMENTATIONS OF THE REQUESTED FUNCTIONS
IN THIS FILE. START YOUR IMPLEMENTATIONS BELOW THIS LINE
*/

Board::Board (uint _size, std::vector <Player*>* _players, Coordinate chest) : size (_size), chest (chest), players (_players) {}

Board::~Board () {}

bool Board::isCoordinateInBoard (const Coordinate &c)
{
    return c.x >= 0 && c.y >= 0 && c.x < (int)(size) && c.y < (int)(size);
}

bool Board::isPlayerOnCoordinate (const Coordinate& c)
{
    for (auto i: *players)
    {
        if (i->getCoord () == c)
            return true;
    }
    return false;
}

Player* Board::operator[] (const Coordinate& c)
{
    for (auto i: *players)
    {
        if (i->getCoord () == c)
            return i;
    }
    return nullptr;
}

Coordinate Board::getChestCoordinates ()
{
    return chest;
}

void Board::printBoardwithID ()
{
    for (int j = 0; j < size; ++ j)
    {
        for (int i = 0; i < size; ++ i)
        {
            Player *p = (*this)[Coordinate (i, j)];

            if (p != nullptr)
            {
                std::cout << p->getBoardID () << " ";
            }
            else if (Coordinate (i, j) == chest)
            {
                std::cout << "Ch ";
            }
            else
            {
                std::cout << "__ ";
            }
        }
        std::cout << std::endl;
    }
}

void Board::printBoardwithClass ()
{
    for (int j = 0; j < size; ++ j)
    {
        for (int i = 0; i < size; ++ i)
        {
            Player *p = (*this)[Coordinate (i, j)];

            if (p != nullptr)
            {
                std::cout << p->getClassAbbreviation () << " ";
            }
            else if (Coordinate (i, j) == chest)
            {
                std::cout << "Ch ";
            }
            else
            {
                std::cout << "__ ";
            }
        }
        std::cout << std::endl;
    }
}