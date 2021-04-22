CC=g++ -std=c++11
CFLAGS = -g -Wall

snake-revisited: main.o GameEngine.o Snake.o Coordinates.o Player.o Pellet.o GameMap.o Obstacle.o MainMenu.o
	$(CC) $(CFLAGS) -o snake-revisited main.o GameEngine.o Snake.o Coordinates.o Player.o Pellet.o GameMap.o Obstacle.o MainMenu.o -lncurses

main.o: main.cpp
	$(CC) $(CFLAGS) -c main.cpp

GameEngine.o: GameEngine.cpp
	$(CC) $(CFLAGS) -c GameEngine.cpp

Snake.o: Snake.cpp
	$(CC) $(CFLAGS) -c Snake.cpp

Coordinates.o: Coordinates.cpp
	$(CC) $(CFLAGS) -c Coordinates.cpp

Player.o: Player.cpp
	$(CC) $(CFLAGS) -c Player.cpp

Pellet.o: Pellet.cpp
	$(CC) $(CFLAGS) -c Pellet.cpp

GameMap.o: GameMap.cpp
	$(CC) $(CFLAGS) -c GameMap.cpp

Obstacle.o: Obstacle.cpp
	$(CC) $(CFLAGS) -c Obstacle.cpp

MainMenu.o: MainMenu.cpp
	$(CC) $(CFLAGS) -c MainMenu.cpp

clean: 
	rm *.o
