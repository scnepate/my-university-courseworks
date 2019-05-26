#include"Game.h"
#define MAXX 20202020
/*
YOU MUST WRITE THE IMPLEMENTATIONS OF THE REQUESTED FUNCTIONS
IN THIS FILE. START YOUR IMPLEMENTATIONS BELOW THIS LINE
*/

Game::Game (uint maxTurnNumber, uint boardSize, Coordinate chest) : maxTurnNumber (maxTurnNumber), board (boardSize, &players, chest)
{
    turnNumber = 1;
}

Game::~Game ()
{
    for (int i = 0; i < players.size (); ++ i)
    {
        delete players[i];
    }
}

void Game::addPlayer (int id, int x, int y, Team team, std::string cls)
{
    if (cls == "ARCHER")
    {
        players.push_back (new Archer (id, x, y, team));
    }
    else if (cls == "FIGHTER")
    {
        players.push_back (new Fighter (id, x, y, team));
    }
    else if (cls == "PRIEST")
    {
        players.push_back (new Priest (id, x, y, team));
    }
    else if (cls == "SCOUT")
    {
        players.push_back (new Scout (id, x, y, team));
    }
    else if (cls == "TANK")
    {
        players.push_back (new Tank (id, x, y, team));
    }
}

bool Game::isGameEnded ()
{
    int turn = std::max (0, (int)(turnNumber)-1);

    if (turn == maxTurnNumber)
    {
        std::cout << "Game ended at turn " << turn << ". Maximum turn number reached. Knight victory.\n";
        return true;
    }
    else if (board[board.getChestCoordinates()] != nullptr && board[board.getChestCoordinates()]->getTeam () == BARBARIANS) 
    {
        std::cout << "Game ended at turn " << turn << ". Chest captured. Barbarian victory.\n";
        return true;
    }
    else // use find_if and lambda functions
    {
        int k = 0, b = 0;
        for (auto i: players)
        {
            if (i->getTeam () == BARBARIANS) ++ b;
            else ++ k;
        }
        if (b == 0)
        {
            std::cout << "Game ended at turn " << turn << ". All barbarians dead. Knight victory.\n";
            return true;
        }
        else if (k == 0)
        {
            std::cout << "Game ended at turn " << turn << ". All knights dead. Barbarian victory.\n";
            return true;
        }
    }

    return false;
}

void Game::playTurn ()
{
    std::cout << "Turn " << turnNumber ++ << " has started.\n";
    std::sort (players.begin (), players.end (), [](Player *a, Player *b){return (a->getID () < b->getID ());});

    for (auto i = players.begin (); i != players.end (); ++ i)
    {
        // std::cout << (*i)->getBoardID () << " ";
        if ((*i)->isDead ())
        {
            std::cout << "Player " << (*i)->getBoardID () << " has died.\n";
            Player *temp = *i;
            players.erase (i);
            delete temp;
            -- i;
        }
        else playTurnForPlayer (*i);
    }
}

Goal Game::playTurnForPlayer (Player* player)
{
    std::vector <Goal> goals = player->getGoalPriorityList ();
    for (auto i: goals)
    {
        if (i == ATTACK)
        {
            // std::cout << "ATTACK\n";
            std::vector <Coordinate> v = player->getAttackableCoordinates ();
            Player *toAttack = nullptr;
            int minID = MAXX;
            for (auto j: v)
            {
                if (board.isCoordinateInBoard (j) && board[j] != nullptr && board[j]->getTeam () != player->getTeam () && board[j]->getID () < minID)
                {
                    minID =  board[j]->getID ();
                    toAttack = board[j];
                }
            }
            if (toAttack != nullptr)
            {
                player->attack (toAttack);
                // std::cout << "aTTACK\n";
                return ATTACK;
            }
        }
        else if (i == CHEST)
        {
            // std::cout << "CHEST\n";
            Coordinate c = player->getCoord ();
            std::vector <Coordinate> movable = player->getMoveableCoordinates ();
            int best = MAXX;
            for (auto i: movable)
            {
                if (i-board.getChestCoordinates () < best && board.isCoordinateInBoard (i) && !board.isPlayerOnCoordinate (i))
                {
                    best = i-board.getChestCoordinates ();
                    c = i;
                }
            }
            if (player->getCoord ()-board.getChestCoordinates () <= c-board.getChestCoordinates ())
            {
                continue;
            }
            // std::cout << player->getBoardID () << "CHEST: " << c << " " << (best < MAXX) << "\n";
            if (best < MAXX)
            {
                player->movePlayerToCoordinate (c);
                // std::cout << "cHEST\n";
                return CHEST;
            }
        }
        else if (i == TO_ENEMY)
        {
            // std::cout << "TO_ENEMY\n";
            std::vector <Coordinate> movable = player->getMoveableCoordinates ();
            Coordinate coord (MAXX, MAXX);
            
            for (auto i: players)
            {
                if (i->getTeam () != player->getTeam () && i->getCoord ()-player->getCoord () < coord-player->getCoord ())
                {
                    coord = i->getCoord ();
                }
            }
            if (coord == Coordinate (MAXX, MAXX)) continue;
            
            Coordinate c = player->getCoord ();
            for (auto i: movable)
            {
                if (board.isCoordinateInBoard (i) && i-coord < c-coord && !board.isPlayerOnCoordinate (i))
                {
                    c = i;
                }
            }

            if (player->getCoord ()-board.getChestCoordinates () <= c-board.getChestCoordinates ())
            {
                continue;
            }

            if (c != player->getCoord ())
            {
                player->movePlayerToCoordinate (c);
                // std::cout << "tO_ENEMY\n";
                return TO_ENEMY;
            }
        }
        else if (i == TO_ALLY)
        {
            // std::cout << "TO_ALLY\n";
            std::vector <Coordinate> movable = player->getMoveableCoordinates ();
            Coordinate coord (MAXX, MAXX);
            
            for (auto i: players)
            {
                if (i != player && i->getTeam () == player->getTeam () && i->getCoord ()-player->getCoord () < coord-player->getCoord ())
                {
                    coord = i->getCoord ();
                }
            }

            if (coord == Coordinate (MAXX, MAXX)) continue;
            // std::cout << "coord: " << coord << "\n";
            Coordinate c = player->getCoord ();
            for (auto i: movable)
            {
                if (board.isCoordinateInBoard (i) && i-coord < c-coord && !board.isPlayerOnCoordinate (i))
                {
                    c = i;
                }
            }

            if (player->getCoord ()-board.getChestCoordinates () <= c-board.getChestCoordinates () && !board.isPlayerOnCoordinate (c))
            {
                continue;
            }

            // std::cout << "c: " << c << "\n";
            if (c != player->getCoord ())
            {
                player->movePlayerToCoordinate (c);
                // std::cout << "tO_ALLY\n";
                return TO_ALLY;
            }
        }
        else if (i == HEAL)
        {
            // std::cout << "HEAL\n";
            std::vector <Coordinate> healable = player->getHealableCoordinates ();
            bool healed = false;
            for (auto i: healable)
            {
                if (board.isCoordinateInBoard (i))
                {
                    Player *toHeal = board[i];
                    if (toHeal && toHeal->getTeam () == player->getTeam ())
                    {
                        player->heal (toHeal);
                        healed = true;
                    }
                }
            }
            if (healed)
            {
                // std::cout << "hEAL\n";
                return HEAL;
            }
        }
    }

    // std::cout << "NO_GOAL\n";
    return NO_GOAL;
}