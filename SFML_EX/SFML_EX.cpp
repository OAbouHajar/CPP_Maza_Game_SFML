// Maze game. By Osama Abou Hajar Date : 26/11/2018
//


#include "pch.h"

//#include "stdafx.h"

#ifdef _DEBUG 
#pragma comment(lib,"sfml-graphics-d.lib") 
#pragma comment(lib,"sfml-audio-d.lib") 
#pragma comment(lib,"sfml-system-d.lib") 
#pragma comment(lib,"sfml-window-d.lib") 
#pragma comment(lib,"sfml-network-d.lib") 
#else 
#pragma comment(lib,"sfml-graphics.lib") 
#pragma comment(lib,"sfml-audio.lib") 
#pragma comment(lib,"sfml-system.lib") 
#pragma comment(lib,"sfml-window.lib") 
#pragma comment(lib,"sfml-network.lib") 
#endif 

#include <SFML/Graphics.hpp>
#include <iostream>
#include <stdlib.h> 
#include <time.h> 
//#include <Clock.hpp>
#include <iostream>
#include <fstream>
#include <SFML/Audio.hpp>

int const ARRAYSIZE = 16;
int dynamicArrraySizeRows;
int dynamicEnemyNumber;
int dynamicArrraySizeColumns;
int **mazeGraph;
int const DIMINTION = 35;
int SIDES = 525;
int randNum = 0;
sf::Music music;
sf::Music bombsound;
sf::Music firesound;
sf::Music LifeLostSound;
sf::Music StageCompleteSound;
sf::Music GameOverSound;

class Enemy : public sf::Sprite {
public:
	int randNumX;
	int randNumy; 
	int x;
	int y;
		
	Enemy()
	{	
		
		do
		{
			randNumX = (rand() % dynamicArrraySizeColumns-1) + 1;
			randNumy = (rand() % dynamicArrraySizeRows-1) + 1;
			x = randNumX;
			y = randNumy;
		} while (mazeGraph[randNumy][randNumX] == 1 );
			
		
	}
	bool moveEnemy(int direction) {
		this->x = (this->getPosition().x) / DIMINTION;
		this->y = (this->getPosition().y) / DIMINTION;

		std::cout << "ENEMY x" << x << std::endl;
		std::cout << "ENEMY y" << y << std::endl;

		if (direction == 1)
		{
			if (this->getPosition().x != 0 && mazeGraph[y][x - 1] != 1 && mazeGraph[y][x - 1] != 8)
			{
				this->move(-DIMINTION, 0);
			}
			else
				return false;
		}
		else if (direction == 2)
		{
			if (this->getPosition().x != SIDES && mazeGraph[y][x + 1] != 1 && mazeGraph[y][x + 1] != 8)
			{
				this->move(DIMINTION, 0);
			}
			else
				return false;
		}
		else if (direction == 3)
		{
			if (this->getPosition().y != 0 && mazeGraph[y - 1][x] != 1 && mazeGraph[y - 1][x] != 8)
			{
				this->move(0, -DIMINTION);
			}
			else
				return false;
		}
		else if (direction == 4)
		{
			if (this->getPosition().y != SIDES && mazeGraph[y + 1][x] != 1 && mazeGraph[y + 1][x] != 8)
			{
				this->move(0, DIMINTION);
			}
			else
				return false;
		}
	}
	
	
};

class Player : public sf::Sprite {
public:
	int randNumX;
	int randNumy; 
	int x;
	int y;
	Player()
	{
		do
		{
			randNumX = (rand() % dynamicArrraySizeColumns - 1) + 1;
			randNumy = (rand() % dynamicArrraySizeRows - 1) + 1;
			x = randNumX;
			y = randNumy;
		} while (mazeGraph[randNumy][randNumX] == 1);
	}

	bool movePlayer(int direction) {
		this -> x = (this -> getPosition().x) / DIMINTION;
		this-> y = (this -> getPosition().y) / DIMINTION;
			
		std::cout << "x" << x << std::endl;
		std::cout << "y" << y << std::endl;

		if (direction == 1)
		{
			if (this -> getPosition().x != 0 && mazeGraph[y][x - 1] != 1 && mazeGraph[y][x - 1] != 8)
			{//left
				this -> move(-DIMINTION, 0);
			}
			else
				return false;
		}
		else if (direction == 2)
		{
			if (this->getPosition().x != SIDES && mazeGraph[y][x + 1] != 1 && mazeGraph[y][x + 1] != 8)
			{//right
				this->move(DIMINTION, 0);
			}
			else
				return false;
		}
		else if (direction == 3)
		{
			if (this->getPosition().y != 0 && mazeGraph[y - 1][x] != 1 && mazeGraph[y - 1][x] != 8)
			{//up
				this->move(0, -DIMINTION);
			}
			else
				return false;
		}
		else if (direction == 4)
		{//down
			if (this->getPosition().y != SIDES && mazeGraph[y + 1][x] != 1 && mazeGraph[y + 1][x] != 8 )
			{
				this->move(0, DIMINTION);
			}
			else
				return false;
		}
	}
	void setRanPos()
	{
		do
		{
			randNumX = (rand() % dynamicArrraySizeColumns - 1) + 1;
			randNumy = (rand() % dynamicArrraySizeRows - 1) + 1;
			x = randNumX;
			y = randNumy;
		} while (mazeGraph[randNumy][randNumX] == 1);
	}
};

class Wall : public sf::Sprite {
public:
	int x;
	int y;
};

class Path : public sf::Sprite {
public:
	int x;
	int y;

};

class Bomb : public sf::Sprite {
public:
	int x;
	int y;
	Bomb()
	{
		x = 0;
		y = 0;
	}
	
};

class Fire : public sf::Sprite {

public:

	int x;
	int y;
	Fire()
	{
		x = -20;
		y = -20;
	}
};

void create_the_sound() {
	
	if (!music.openFromFile("gameStart.wav"))
	{
		std::cout << "Sound Not Found";
	}
	music.setVolume(35);
	music.play();

	if (!bombsound.openFromFile("bombsound.wav"))
	{
		std::cout << "Sound Not Found";
	}
	bombsound.setVolume(55);

	if (!firesound.openFromFile("Explosion.wav"))
	{
		std::cout << "Sound Not Found";
	}
	firesound.setVolume(65);

	if (!LifeLostSound.openFromFile("LifeLost.wav"))
	{
		std::cout << "Sound Not Found";
	}
	LifeLostSound.setVolume(65);
	
	if (!StageCompleteSound.openFromFile("StageComplete.wav"))
	{
		std::cout << "Sound Not Found";
	}
	StageCompleteSound.setVolume(65);

	if (!GameOverSound.openFromFile("GameOver.wav"))
	{
		std::cout << "Sound Not Found";
	}
	GameOverSound.setVolume(65);
}

bool player_touch_the_fire(Player player, Fire fireSprite[])
{
	for (int index = 0; index < 36; index++)
	{
		if (player.getPosition() == fireSprite[index].getPosition()) {
			
			return  true;
			std::cout << std::endl << "\n\n player touch the fire" << std::endl;
		}	
	}
	return false;
}

void setFirePos(Fire fireSprite[] ,int bombY,int bombX)
{
	
	std::cout << "mazeGraph[bombY][bombX]" << mazeGraph[bombY][bombX];
	int indexFortheArrayOfFire = 1;
	for (int totalFireToPrint = 0; totalFireToPrint < 36; totalFireToPrint ++ ) {
		fireSprite[totalFireToPrint].x = -20;
		fireSprite[totalFireToPrint].y = -20;
	}
	
	fireSprite[0].x = bombY;
	fireSprite[0].y = bombX;
	
	int left = 1;
	while (mazeGraph[bombY][bombX - left ] != 1 && left <= 4)
	{
		fireSprite[indexFortheArrayOfFire].x = bombY;
		fireSprite[indexFortheArrayOfFire].y = bombX - left;
		left++;
		indexFortheArrayOfFire++;
	}

	int right = 1;
	while (mazeGraph[bombY][bombX + right] != 1 && right <= 4)
	{
		fireSprite[indexFortheArrayOfFire].x = bombY;
		fireSprite[indexFortheArrayOfFire].y = bombX + right;
		right++;
		indexFortheArrayOfFire++;
	}
	
	int up = 1;
	while (bombY - up > -1 &&mazeGraph[bombY - up][bombX] != 1 && up <= 4)
	{
		fireSprite[indexFortheArrayOfFire].x = bombY - up;
		fireSprite[indexFortheArrayOfFire].y = bombX;
		up++;
		indexFortheArrayOfFire++;
	}
	int down = 1;
	
	while (bombY + down < dynamicArrraySizeRows && mazeGraph[bombY + down][bombX] != 1 && down <= 4)
	{
		fireSprite[indexFortheArrayOfFire].x = bombY + down;
		fireSprite[indexFortheArrayOfFire].y = bombX;
		down++;
		indexFortheArrayOfFire++;
	}

	int upleft = 1;
	while (bombY - upleft > -1 && mazeGraph[bombY - upleft][bombX + upleft] != 1 && upleft <= 4)
	{
		fireSprite[indexFortheArrayOfFire].x = bombY - upleft;
		fireSprite[indexFortheArrayOfFire].y = bombX + upleft;
		upleft++;
		indexFortheArrayOfFire++;
	}

	int upright = 1;
	while (bombY - upright > -1 && mazeGraph[bombY - upright][bombX - upright] != 1 && upright <= 4)
	{
		fireSprite[indexFortheArrayOfFire].x = bombY - upright;
		fireSprite[indexFortheArrayOfFire].y = bombX - upright;
		upright++;
		indexFortheArrayOfFire++;
	}

	int downleft = 1;
	
	while (bombY + downleft < dynamicArrraySizeRows && mazeGraph[bombY + downleft][bombX - downleft] != 1 && downleft <= 4)
	{
		fireSprite[indexFortheArrayOfFire].x = bombY + downleft;
		fireSprite[indexFortheArrayOfFire].y = bombX - downleft;
		downleft++;
		indexFortheArrayOfFire++;
	}
	int downright = 1;
	while (bombY + downright < dynamicArrraySizeRows && mazeGraph[bombY + downright][bombX + downright] != 1 && downright <= 4)
	{
		fireSprite[indexFortheArrayOfFire].x = bombY + downright;
		fireSprite[indexFortheArrayOfFire].y = bombX + downright;
		downright++;
		indexFortheArrayOfFire++;
	}


}

void read_the_Array_from_the_file()
{
	std::ifstream file{ "array2.txt" };

	if (!file.is_open())
		std::cout << "Array File not found";

	file >> dynamicArrraySizeColumns;
	file >> dynamicArrraySizeRows;
	file >> dynamicEnemyNumber;
	mazeGraph = new int*[dynamicArrraySizeRows];

	for (int row = 0; row < dynamicArrraySizeRows; row++) {
		mazeGraph[row] = new int[dynamicArrraySizeColumns];
	}


	for (int mazeCol = 0; mazeCol < dynamicArrraySizeRows; mazeCol++) {
		for (int mazeRow = 0; mazeRow < dynamicArrraySizeColumns; mazeRow++) {
			file >> mazeGraph[mazeCol][mazeRow];
		}
	}


}

int main() 
{
start:
	int score = 0;
	int lifeNumber = 3;
	int bombNumber = 6;
	bool playerKilled = false;
	bool enemyKilled = false;
	bool fireOn = false;
	create_the_sound();
	read_the_Array_from_the_file();
	int counter = 0;
	sf::RenderWindow window(sf::VideoMode(560, 635), "Maze Game in C++");
	srand(time(NULL));
	float randomNum;
	sf::Time timePerFrame = sf::seconds(1.0f / 60.0f); 
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	sf::Clock clock;
	clock.restart();

	double speed = 0.25;

	sf::Texture playerTexture;
	if (!playerTexture.loadFromFile("player.png"))
	{
		std::cout << "file not found";
	}
	Player player;
	player.setTexture(playerTexture);
	player.setPosition(player.x * player.getGlobalBounds().width, player.y * player.getGlobalBounds().height);
	sf::Texture enemyTexture;
	if (!enemyTexture.loadFromFile("enemy.png"))
	{
		std::cout << "file not found";
	}
	Enemy enemy1[100];
	int enemyCounter = 0;
	sf::Texture wallTexture;
	if (!wallTexture.loadFromFile("wall.png"))
	{
		std::cout << "file not found";
	}
	Wall wallSprite;
	wallSprite.setTexture(wallTexture);
	sf::Texture pathTexture;
	if (!pathTexture.loadFromFile("Path.png"))
	{
		std::cout << "file not found";
	}
	Path pathSprite;
	pathSprite.setTexture(pathTexture);
	sf::Texture bombTexture;
	if (!bombTexture.loadFromFile("Bomb.png"))
	{
		std::cout << "file not found";
	}
	Bomb bombSprite ;
	bombSprite.setTexture(bombTexture);
	sf::Clock clockBomb;
	sf::Time timeBomb;
	int bombX = 0;
	int bombY = 0;
	bool bombDropped = false;
	sf::Time TimePerFrame = sf::seconds(1.0f / 60.0f);
	sf::Texture fireTexture;
	if (!fireTexture.loadFromFile("fire.png"))
	{
		std::cout << "file not found";
	}
	Fire fireSpriteDraw;
	fireSpriteDraw.setTexture(fireTexture);
	Fire fireSprite[36];
	
	sf::Font font;
	if (!font.loadFromFile("arial.ttf"))
	{
		std::cout << "file not found";
	}

	sf::Text instractionsText;
	instractionsText.setFont(font);
	instractionsText.setString("User the arrows to move the player and Enter to Drob the Bomb ");
	instractionsText.setCharacterSize(18);
	instractionsText.setFillColor(sf::Color::Yellow);
	instractionsText.setPosition(25, 565);

	for (int indexForenemey = 0; indexForenemey < dynamicEnemyNumber; indexForenemey++) 
	{
		enemy1[indexForenemey].setTexture(enemyTexture);
		enemy1[indexForenemey].setPosition(enemy1[indexForenemey].x * enemy1[indexForenemey].getGlobalBounds().width, enemy1[indexForenemey].y * enemy1[indexForenemey].getGlobalBounds().height);
	}

	sf::Clock playercolc;

	bool instractionDisplayd = true;
	if (instractionDisplayd)
	{
		
		sf::RenderWindow windowhowToPlay(sf::VideoMode(560, 635), "You Win");
		while (windowhowToPlay.isOpen())
		{
			sf::Event event;
			while (windowhowToPlay.pollEvent(event))
			{
				if (event.type == sf::Event::Closed)
				{
					windowhowToPlay.close();
					window.close();
				}
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
			{
				windowhowToPlay.close();
				instractionDisplayd = false;
				window.display();
				
			}
			sf::Texture howToplayTexture;
			if (!howToplayTexture.loadFromFile("howToPlay.png"))
			{
				std::cout << std::endl << "\n\n Can't load GAME OVER";
			}
			sf::Sprite htpSprite;
			htpSprite.setTexture(howToplayTexture);
			windowhowToPlay.draw(htpSprite);
			windowhowToPlay.display();
		}
	}
	int counterForTime = 0;
	while (window.isOpen())
	{
		fireOn = false;
		randNum = (rand() % 4) + 1;
		sf::Text lifeText;
		lifeText.setFont(font);
		lifeText.setString("Life " + std::to_string(lifeNumber));
		lifeText.setCharacterSize(24);
		lifeText.setFillColor(sf::Color::White);
		lifeText.setPosition(370, 600);
		sf::Text bombText;
		bombText.setFont(font);
		bombText.setString("Bomb " + std::to_string(bombNumber));
		bombText.setCharacterSize(24);
		bombText.setFillColor(sf::Color::White);
		bombText.setPosition(250, 600);
		sf::Text scoreText;
		scoreText.setFont(font);
		scoreText.setString("score " + std::to_string(score));
		scoreText.setCharacterSize(24);
		scoreText.setFillColor(sf::Color::White);
		scoreText.setPosition(150, 600);
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}
		timeSinceLastUpdate += clock.restart();
		window.clear();
		for (int i = 0; i < dynamicArrraySizeRows; i++)
		{
			for (int j = 0; j < dynamicArrraySizeColumns; j++)
			{
				if (mazeGraph[i][j] == 0)
				{
					pathSprite.setPosition(j * pathSprite.getGlobalBounds().width, i * pathSprite.getGlobalBounds().height);
					window.draw(pathSprite);
				}
				if (mazeGraph[i][j] == 1)
				{
					wallSprite.setPosition(j * wallSprite.getGlobalBounds().width, i * wallSprite.getGlobalBounds().height);
					window.draw(wallSprite);
				}
				if (mazeGraph[i][j] == 8)
				{
					bombSprite.setPosition(j * wallSprite.getGlobalBounds().width, i * wallSprite.getGlobalBounds().height);
					window.draw(bombSprite);
				}
			}
		}

		for (int indexToDrawTheEnemy = 0; indexToDrawTheEnemy < dynamicEnemyNumber; indexToDrawTheEnemy++) {
			window.draw(enemy1[indexToDrawTheEnemy]);
		}
		window.draw(player);
		int dirctionMove = 0; 
		int xPlayer = (player.getPosition().x) / DIMINTION;
		int yPlayer = (player.getPosition().y) / DIMINTION;
		if (timeSinceLastUpdate > TimePerFrame)
		{
			sf::Time playerTimer = playercolc.getElapsedTime();
			if (playerTimer.asSeconds() > 0.20) {

				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
				{
					dirctionMove = 1;
					player.movePlayer(dirctionMove);
				}
				else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
				{
					dirctionMove = 2;
					player.movePlayer(dirctionMove);
				}
				else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
				{
					dirctionMove = 3;
					player.movePlayer(dirctionMove);
				}
				else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
				{
					dirctionMove = 4;
					player.movePlayer(dirctionMove);
				}
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter) && bombDropped == false && bombNumber > 0)
				{
					create_the_sound();
					bombsound.play();

					mazeGraph[yPlayer][xPlayer] = 8;
					bombY = yPlayer;
					bombX = xPlayer;
					bombSprite.y = yPlayer;
					bombSprite.x = xPlayer;
					bombNumber--;
					std::cout << "the Bomb Droped" << bombNumber;
					timeBomb = clockBomb.restart();
					bombDropped = true;
				}
				timeBomb = clockBomb.getElapsedTime();
				std::cout << "the Bomb Droped  " << int(timeBomb.asSeconds()) << std::endl;
				if (int(timeBomb.asSeconds()) == 3 && bombDropped)
				{
					create_the_sound();
					firesound.play();
					mazeGraph[bombY][bombX] = 0;
					setFirePos(fireSprite, bombY, bombX);
					int randNumX = (rand() % dynamicArrraySizeColumns - 1) + 1;
					int randNumy = (rand() % dynamicArrraySizeRows - 1) + 1;
					for (int ixd = 0; ixd < 32; ixd++)
					{
						fireSprite[ixd].setTexture(fireTexture);
						fireSprite[ixd].setPosition(fireSprite[ixd].y * fireSprite[ixd].getGlobalBounds().width, fireSprite[ixd].x * fireSprite[ixd].getGlobalBounds().height);
						window.draw(fireSprite[ixd]);

						for (int innerindex = 0; innerindex <= dynamicEnemyNumber; innerindex++) {
							if (fireSprite[ixd].getPosition() == enemy1[innerindex].getPosition())
							{
								enemyKilled = true;
								score++;
								do {
									randNumX = (rand() % dynamicArrraySizeColumns - 1) + 1;
									randNumy = (rand() % dynamicArrraySizeRows - 1) + 1;
									enemy1[innerindex].x = randNumX;
									enemy1[innerindex].y = randNumy;
									enemy1[innerindex].setPosition(randNumX*DIMINTION, randNumy*DIMINTION);
								} while (mazeGraph[randNumy][randNumX] == 1);
							}
						}
						if (player_touch_the_fire(player, fireSprite))
						{
							randNumX = (rand() % dynamicArrraySizeColumns - 1) + 1;
							randNumy = (rand() % dynamicArrraySizeRows - 1) + 1;
							player.x = randNumX;
							player.y = randNumy;
							player.setPosition(randNumX*DIMINTION, randNumy*DIMINTION);
							playerKilled = true;
							lifeNumber--;
						}
					}

					bombDropped = false;
					std::cout << "mazeGraph[bombX][bombY]  " << mazeGraph[bombY][bombX] << std::endl;
					fireOn = true;
				}
				for (int index = 0; index < dynamicEnemyNumber; index++)
				{
					if (player.getPosition() == enemy1[index].getPosition()) {
						lifeNumber--;
						create_the_sound();
						LifeLostSound.play();
						playerKilled = true;
						std::cout << std::endl << "\n\n GAME OVER" << std::endl;
					}

				}
				window.draw(instractionsText);
				window.draw(scoreText);
				window.draw(bombText);
				window.draw(lifeText);
				window.display();
				for (int indexMovingEnemies = 0; indexMovingEnemies < dynamicEnemyNumber; indexMovingEnemies++) {
					randNum = (rand() % 4) + 1;
					enemy1[indexMovingEnemies].moveEnemy(randNum);
				}
				timeSinceLastUpdate = sf::Time::Zero;
				if (score >= 3)
				{
					StageCompleteSound.play();
					sf::RenderWindow windowWin(sf::VideoMode(560, 635), "You Win");
					while (windowWin.isOpen())
					{

						sf::Event event;
						while (windowWin.pollEvent(event))
						{
							if (event.type == sf::Event::Closed)
							{
								windowWin.close();
								window.close();
							}
						}
						if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
						{
							windowWin.close();
							window.close();
						}
						if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
						{
							goto start;
						}

						sf::Texture gameOverTexture;
						if (!gameOverTexture.loadFromFile("win.png"))
						{
							std::cout << std::endl << "\n\n Can't load GAME OVER";
						}
						sf::Sprite goSprite;
						goSprite.setTexture(gameOverTexture);

						windowWin.draw(goSprite);
						windowWin.display();
					}
				}
				if (lifeNumber == 0 || (bombNumber == 0 && fireOn))
				{
					GameOverSound.play();
					sf::RenderWindow windowGameOver(sf::VideoMode(560, 635), "Game Over");
					while (windowGameOver.isOpen()) {
						sf::Event event;
						while (windowGameOver.pollEvent(event))
						{
							if (event.type == sf::Event::Closed)
							{
								windowGameOver.close();
								window.close();
							}
						}
						if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
						{
							windowGameOver.close();
							window.close();
						}
						if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
						{
							goto start;
						}

						sf::Texture gameOverTexture;
						if (!gameOverTexture.loadFromFile("gameover.png"))
						{
							std::cout << std::endl << "\n\n Can't load GAME OVER";
						}
						sf::Sprite goSprite;
						goSprite.setTexture(gameOverTexture);
						windowGameOver.draw(goSprite);
						windowGameOver.display();
					}
				}
				playercolc.restart();
			}
		}		
	}
	return 0;
}
