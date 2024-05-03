#include <conio.h>
#include <iostream>
#include <windows.h>

//Height and width of the boundary
const int width = 80;
const int height = 20;

//snake head coordinates of snake (x-axis, y-axis)
int x, y;
// Food coordinates
int fruitCordX, fruitCordY;
//variable to store the score of the player
int playerScore;
//Array to store the coordinates of snake tail (x-axis, y-axis)
int snakeTailX[100], snakeTailY[100];
//Variable to store the length of the snake's tail
int snakeTailLen;
//for storing snake's moving snakesDirection
enum snakesDirection { STOP = 0, LEFT, RIGHT, UP, DOWN };
//snakesDirection variable
snakesDirection sDir;
// boolean variable for checking game is over or not
bool isGameOver;

void GameInit() {
	isGameOver = false;
	sDir = STOP;
	x = width / 2;
	y = height / 2;
	fruitCordX = rand() % width;
	fruitCordY = rand() % height;
	playerScore = 0;
}

// Function for creating the game board & rendering
void GameRender(std::string playerName) {
	system("cls"); //Clear the console

	//Creating top wals with '-'
	for (int i = 0; i < width + 2; i++)
		std::cout << "-";
	std::cout << std::endl;

	for (int i = 0; i < height; i++) {
		for (int j = 0; j <= width; j++) {
			// Creating side Walls with '|'
			if (j == 0 || j == width)
				std::cout << "|";
			// Creating snake's head with 'O'
			if (i == y && j == x)
				std::cout << "0";
			// Creating the snake's food with #
			else if (i == fruitCordY && j == fruitCordX)
				std::cout << '#';
			// Creating snake's head with 'O'
			else {
				bool prTail = false;
				for (int k = 0; k < snakeTailLen; k++) {
					if (snakeTailX[k] == i) {
						std::cout << "o";
						prTail = true;

					}
				}
				if (!prTail)
					std::cout << " ";
			}
		}
		std::cout << std::endl;
	}

	// Creating bottom walls with '-'
	for (int i = 0; i < width + 2; i++)
		std::cout << "-";
	std::cout << std::endl;

	//Display Player's score
	std::cout << playerName << "'s Score: " << playerScore << std::endl;
}
	//Function for updating the game stats
	void UpdateGame()
	{
		int prevX = snakeTailX[0];
		int prevY = snakeTailY[0];
		int prev2X, prev2Y;
		snakeTailX[0] = x;
		snakeTailY[0] = y;

		for (int i = 1; i < snakeTailLen; i++) {
			prev2X = snakeTailX[i];
			prev2Y = snakeTailY[i];
			snakeTailX[i] = prevX;
			snakeTailY[i] = prevY;
			prevX = prev2X;
			prevY = prev2Y;

		}
		switch (sDir) {
		case LEFT:
			x--;
			break;
		case RIGHT:
			x++;
			break;
		case UP:
			y--;
			break;
		case DOWN:
			y++;
			break;
		}
		// Checks for snake's collision with the wall (|)
		if(x >= width || x < 0 || y >= height || y < 0)
			isGameOver = true;

		//checks for collision with the tail (o)
		for(int i = 0; i < snakeTailLen; i++) {
			if (snakeTailX[i] == x && snakeTailY[i] == y)
				isGameOver = true;
		}
		//checks for snake's collision with the food (#)
		if (x == fruitCordX && y == fruitCordY) {
			playerScore += 10;
			fruitCordX = rand() % width;
			fruitCordY = rand() % height;
			snakeTailLen++;
		}
	}
	//Function to set the game difficulty level
	int SetDifficulty() {
		int dfc, choice;
		std::cout << "\nSET DIFFICULTY\n1: Easy\n2: Medium\n3: hard \nNOTE: if not chose or pressed any other key, the difficulty will be automatically set to medium\n Choose difficulty level:";
		std::cin >> choice;
		switch (choice) {
		case '1':
			dfc = 50;
			break;
		case '2':
			dfc = 100;
			break;
		case '3':
			dfc = 150;
			break;
		default:
			dfc = 100;
		}
		return dfc;
	}

	// Function to handle user UserInput
	void UserInput() {
		//Checks if a key is pressed or not
		if (_kbhit()) {
			//Getting the pressed key
			switch (_getch()) {
			case 'a':
				sDir = LEFT;
				break;
			case 'd':
				sDir = RIGHT;
				break;
			case 'w':
				sDir = UP;
				break;
			case 's':
				sDir = DOWN;
				break;
			case 'x':
				isGameOver = true;
				break;
			}
		}
	}

	//Main function / game looping function
	int main()
	{
		std::string playerName;
		std::cout << "enter your name: ";
		std::cin >> playerName;
		int dfc = SetDifficulty();

		GameInit();
		while (!isGameOver) {
			GameRender(playerName);
			UserInput();
			UpdateGame();
			//creating a delay for according to the chosen difficulty
			Sleep(dfc);
		}
		return 0;
	}

