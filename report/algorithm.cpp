

/////Classes
class Enemy : public sf::Sprite {
};
class Player : public sf::Sprite {
public:
	int randNumX;
	int randNumy; 
	int x;
	int y;
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
};
class Fire : public sf::Sprite {

public:

	int x;
	int y;
};



/////functions

//to import the sound and assigne the buffer
void create_the_sound() { 
	
	
}
//to check if the player touch the fire and return True or False
bool player_touch_the_fire(Player player, Fire fireSprite[]) 
{
	
}
// to set the fire postitions within their classes and draw them
void setFirePos(Fire fireSprite[] ,int bombY,int bombX) 
{
	
}
//to read the Array file and asign the Row, Columns and the enemies number
void read_the_Array_from_the_file()  
{

}


read Rows and columns from the file;

while(window.isOpen()){
	for row in 2DArray {
		for Col in 2DArray{
			if 2DArray[Row][Col] = 1
				Draw Wall;
			if 2DArray[Row][Col] = 1
				Draw Path;
			if 2DArray[Row][Col] = 8
				Draw Bomb;
	if (user press UP)
		move player UP;
	if (user press Down)
		move player Down;	
	if (user press Left)
		move player Left;
	if (user press Right)
		move player Right;
	if (user press Enter)
		Bomb Drop;
		draw bomb;
	//draw enemies with for loop
	for i in enemies 
		draw enemy[i]
	if player.Position == Enemy.Position
		playerKiller = True ;
		show Game Over Window; 
	if Player.Position == Fire.Position	 	
		playerKiller = True ;
		show Game Over Window
	if Fire.Position == Enemy.Position;
		score ++ ;
		if (score == 3)
			show Win the Game Window;
	//moving the enemies randomly 
	randNum = (rand() % 4) + 1;
	enemy1[0].moveEnemy(randNum);
	}
