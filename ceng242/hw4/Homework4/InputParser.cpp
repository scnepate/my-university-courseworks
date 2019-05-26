#include"InputParser.h"

/*
YOU MUST WRITE THE IMPLEMENTATIONS OF THE REQUESTED FUNCTIONS
IN THIS FILE. START YOUR IMPLEMENTATIONS BELOW THIS LINE
*/

Game* InputParser::parseGame ()
{
    int size; std::cin >> size;
    int x, y; std::cin >> x >> y; Coordinate chest (x, y);
    int max_turn; std::cin >> max_turn;
    int num_player; std::cin >> num_player;
    
    Game* game = new Game (max_turn, size, chest);
    
    for (int i = 0; i < num_player; ++ i)
    {
        int id, x, y; std::string cl, te;
        std::cin >> id >> cl >> te >> x >> y;
        Team team = (te=="KNIGHT"?KNIGHTS:BARBARIANS);
        game->addPlayer (id, x, y, team, cl);
    }

    return game;
}