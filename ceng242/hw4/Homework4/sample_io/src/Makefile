LDFLAGS=-std=c++11

testPlayer: testPlayer.cpp Archer.cpp Fighter.cpp Priest.cpp Scout.cpp Tank.cpp;  g++ $(LDFLAGS) Archer.cpp Board.cpp Fighter.cpp Game.cpp InputParser.cpp Player.cpp Priest.cpp Scout.cpp Tank.cpp testPlayer.cpp -o testPlayer
testBoard: testBoard.cpp; g++ $(LDFLAGS) Archer.cpp Board.cpp Fighter.cpp Game.cpp InputParser.cpp Player.cpp Priest.cpp Scout.cpp Tank.cpp testBoard.cpp -o testBoard
testGame: *.cpp;g++ $(LDFLAGS) Archer.cpp Board.cpp Fighter.cpp Game.cpp InputParser.cpp Player.cpp Priest.cpp Scout.cpp Tank.cpp testGame.cpp -o testGame
