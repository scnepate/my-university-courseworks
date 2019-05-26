#include"Game.h"
#include"InputParser.h"
#include<iostream>


int main(){

  Game *game = InputParser::parseGame();
  Board *board = game->getBoard();
  std::cout << "Board with ID" << std::endl;
  board->printBoardwithClass();
  std::cout << "Board with ID" << std::endl;
  board->printBoardwithID();
  
  // int i = 1;
  
  while(!game->isGameEnded())
  {
    // if (i == 11) break;
    game->playTurn();
    board->printBoardwithClass();
    std::cout << "--------------" << std::endl;
    board->printBoardwithID();
  
    // ++ i;
  }

  delete game;
}
