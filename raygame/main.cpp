#include <iostream>
#include "raylib.h"

#define NUMBER_OF_BUTTON_FRAMES 4
 
//Struct for the button so that I could have two without too much hard coding.
struct Button
{
	Texture2D ButtonTexture;
	Vector2 Location;
	int buttonTextureNumber;
	Rectangle buttonBooundingBox;
};

//Makes a random color
Color randomColor()
{
	Color SeizureMaker = { rand() % 256,rand() % 256 ,rand() % 256 ,rand() % 256 };
	return SeizureMaker;
}


int checkIfWon(int gameBoard[3][3])
{
	if (gameBoard[0][0] == 1 && gameBoard[0][1] == 1 && gameBoard[0][2] == 1) {
		return 1;
	}
	else if (gameBoard[1][0] == 1 && gameBoard[1][1] == 1 && gameBoard[1][2] == 1) {
		return 1;
	}
	else if (gameBoard[2][0] == 1 && gameBoard[2][1] == 1 && gameBoard[2][2] == 1) {
		return 1;
	}
	else if (gameBoard[0][0] == 1 && gameBoard[1][0] == 1 && gameBoard[2][0] == 1) {
		return 1;
	}
	else if (gameBoard[0][1] == 1 && gameBoard[1][1] == 1 && gameBoard[2][1] == 1) {
		return 1;
	}
	else if (gameBoard[0][2] == 1 && gameBoard[1][2] == 1 && gameBoard[2][2] == 1) {
		return 1;
	}
	else if (gameBoard[0][0] == 1 && gameBoard[1][1] == 1 && gameBoard[2][2] == 1) {
		return 1;
	}
	else if (gameBoard[0][2] == 1 && gameBoard[1][1] == 1 && gameBoard[2][0] == 1) {
		return 1;
	}

	if (gameBoard[0][0] == 2 && gameBoard[0][1] == 2 && gameBoard[0][2] == 2) {
		return 2;
	}
	else if (gameBoard[1][0] == 2 && gameBoard[1][1] == 2 && gameBoard[1][2] == 2) {
		return 2;
	}
	else if (gameBoard[2][0] == 2 && gameBoard[2][1] == 2 && gameBoard[2][2] == 2) {
		return 2;
	}
	else if (gameBoard[0][0] == 2 && gameBoard[1][0] == 2 && gameBoard[2][0] == 2) {
		return 2;
	}
	else if (gameBoard[0][1] == 2 && gameBoard[1][1] == 2 && gameBoard[2][1] == 2) {
		return 2;
	}
	else if (gameBoard[0][2] == 2 && gameBoard[1][2] == 2 && gameBoard[2][2] == 2) {
		return 2;
	}
	else if (gameBoard[0][0] == 2 && gameBoard[1][1] == 2 && gameBoard[2][2] == 2) {
		return 2;
	}
	else if (gameBoard[0][2] == 2 && gameBoard[1][1] == 2 && gameBoard[2][0] == 2) {
		return 2;
	}
	if(gameBoard[0][0] != 0 && gameBoard[0][1] != 0 && gameBoard[0][2] != 0 && gameBoard[1][0] != 0 && gameBoard[1][1] != 0 && gameBoard[1][2] != 0 && gameBoard[2][0] != 0 && gameBoard[2][1] != 0 && gameBoard[2][2] != 0)
	{
		return 3;
	}
	return 0;
}

	


int main()
{
	//variables for the game to work.
	int turns = 1;
	bool screenSizeChosen = false;
	//the game board and who is currently where.
	int gameBoard[3][3] = { { 0,0,0 }, {0,0,0}, {0,0,0} };
	int player1Score = 0;
	int player2Score = 0;
	int stalemate = 0;
	//the bounding boxes for the board.
	Rectangle TicTacToeBoundingBox[3][3];
	
	const int numberOfButtons = 2;
	Button buttons[numberOfButtons];
	int startGame = 0;
	int screenSize;
	//Ask the player for a size so that it sizes the window to the right amount.
	std::cout << "Please Enter a Number between 4 and 10." << std::endl;
	while (screenSizeChosen == false)
	{
		std::cin >> screenSize;
		if (screenSize >= 4 && 10 >= screenSize)
		{
			screenSizeChosen = true;
			break;
		}
		std::cout << "I said Enter a Number between 4 and 10." << std::endl;
	}
	screenSize = screenSize * 100;

	float buttonScale = screenSize / 400;

	
	InitWindow(screenSize, screenSize, "raylib [core] example - basic window");
	Texture2D buttonUp = LoadTexture("Resource Files/blue_button00.png");
	Texture2D buttonHighlighted = LoadTexture("Resource Files/blue_button01.png");
	Texture2D buttonPressed = LoadTexture("Resource Files/blue_button03.png");
	const int cellcount = 4;
	//The other menu button
	buttons[0].buttonTextureNumber = 0;
	buttons[0].ButtonTexture = buttonUp;
	buttons[0].Location.x = float(screenSize / 2 - (buttons[0].ButtonTexture.width*buttonScale) / 2);
	buttons[0].Location.y = float(screenSize / 2 - (buttons[0].ButtonTexture.height*buttonScale) / 2);
	//The menu buttons
	buttons[1].ButtonTexture = buttonUp;
	buttons[1].Location.x = float(screenSize / 2 - (buttons[1].ButtonTexture.width*buttonScale) / 2);
	buttons[1].Location.y = float(screenSize / 1.5 - (buttons[1].ButtonTexture.height*buttonScale) / 2);
	buttons[1].buttonTextureNumber = 0;
	//Getting the mouse position(probably not needed but I ran into  problem at some point and tried this and never reverted it.)
	Vector2 mousePoint = GetMousePosition();
	//making the hit boxes
	TicTacToeBoundingBox[0][0] = { float(screenSize*.1), float(screenSize*.1), float(screenSize*.24) , float(screenSize*.24)};
	TicTacToeBoundingBox[0][1] = { float(screenSize*.34), float(screenSize*.1), float(screenSize*.26) , float(screenSize*.24) };
	TicTacToeBoundingBox[0][2] = { float(screenSize*.60), float(screenSize*.1), float(screenSize*.25) , float(screenSize*.24) };
	TicTacToeBoundingBox[1][0] = { float(screenSize*.1), float(screenSize*.34), float(screenSize*.24) , float(screenSize*.26) };
	TicTacToeBoundingBox[1][1] = { float(screenSize*.34), float(screenSize*.34), float(screenSize*.26) , float(screenSize*.26) };
	TicTacToeBoundingBox[1][2] = { float(screenSize*.60), float(screenSize*.34), float(screenSize*.25) , float(screenSize*.26) };
	TicTacToeBoundingBox[2][0] = { float(screenSize*.1), float(screenSize*.60), float(screenSize*.24) , float(screenSize*.25) };
	TicTacToeBoundingBox[2][1] = { float(screenSize*.34), float(screenSize*.60), float(screenSize*.26) , float(screenSize*.25) };
	TicTacToeBoundingBox[2][2] = { float(screenSize*.60), float(screenSize*.60), float(screenSize*.25) , float(screenSize*.25) };

	SetTargetFPS(60);
	while (!WindowShouldClose())
	{
		mousePoint = GetMousePosition();
		
		BeginDrawing();
		if (startGame == 1)
		{
			//Drawing the game board and the scores
			DrawRectangleLines(screenSize*.1, screenSize * .1, screenSize * .75, screenSize * .75, BLACK);
			DrawLine(screenSize*.1, screenSize*.34, screenSize*.85, screenSize*.34, BLACK);
			DrawLine(screenSize*.1, screenSize*.60, screenSize*.85, screenSize*.60, BLACK);
			DrawLine(screenSize*.34, screenSize*.1, screenSize*.34, screenSize*.85, BLACK);
			DrawLine(screenSize*.60, screenSize*.1, screenSize*.60, screenSize*.85, BLACK);
			DrawText(FormatText("Player1: %01i",  player1Score), screenSize * .01, 0, buttonScale * 10, randomColor());
			DrawText(FormatText("Player2: %01i", player2Score), screenSize * .75, 0, buttonScale * 10, randomColor());
			DrawText(FormatText("Turn: %01i", turns), screenSize * .35, 0, buttonScale * 10, randomColor());
			DrawText(FormatText("Stalemate: %01i", stalemate), screenSize * .35, screenSize * .03, buttonScale * 10, randomColor());

			for (int i = 0; i < 3; i++)
			{
				for (int x = 0; x < 3; x++) 
				{
					//Chekcing the size of the boxes to make them the same size as the board.
					//DrawRectangleLinesEx(TicTacToeBoundingBox[i][x], 1, randomColors[GetRandomValue(0, 10)]);

					//draws the xs(player 1)
					if (gameBoard[i][x] == 1)
					{
						DrawLine(TicTacToeBoundingBox[i][x].x, TicTacToeBoundingBox[i][x].y, TicTacToeBoundingBox[i][x].x + TicTacToeBoundingBox[i][x].width, TicTacToeBoundingBox[i][x].y + TicTacToeBoundingBox[i][x].height, BLACK);
						DrawLine(TicTacToeBoundingBox[i][x].x + TicTacToeBoundingBox[i][x].width, TicTacToeBoundingBox[i][x].y, TicTacToeBoundingBox[i][x].x, TicTacToeBoundingBox[i][x].y + TicTacToeBoundingBox[i][x].height, BLACK);
					}
					//Draws the circles(player 2)
					if (gameBoard[i][x] == 2)
					{
						DrawCircleLines(TicTacToeBoundingBox[i][x].x + TicTacToeBoundingBox[i][x].width / 2, TicTacToeBoundingBox[i][x].y + TicTacToeBoundingBox[i][x].height / 2, screenSize*.12, BLACK);
					}

					//checking if the mouse is in any of the boxes
					if (CheckCollisionPointRec(mousePoint, TicTacToeBoundingBox[i][x]))
					{
						//checks if the left button is pressed. (I should revers this but i don't have time right now)
						if (IsMouseButtonPressed(0))
						{
							//check whos turn it is.
							if (turns == 1)
							{
								//checks if the box is open
								if (gameBoard[i][x] == 0)
								{
									//if it is it makes it to who ever turn it is to the box then 
									gameBoard[i][x] = 1;
									turns = 2;
								}
							}
							else if (turns == 2)
							{
								if (gameBoard[i][x] == 0)
								{
									gameBoard[i][x] = 2;
									turns = 1;
								}
							}
						}
					}
				}
			}
			//checks who if someone has won
			if(checkIfWon(gameBoard) == 1)
			{
				player1Score++;
				for(int i = 0; i < 3; i++)
				{
					for(int x = 0; x < 3; x++)
					{
						gameBoard[i][x] = 0;
					}
				}
			}
			else if (checkIfWon(gameBoard) == 2)
			{
				player2Score++;
				for (int i = 0; i < 3; i++)
				{
					for (int x = 0; x < 3; x++)
					{
						gameBoard[i][x] = 0;
					}
				}
			}
			else if (checkIfWon(gameBoard) == 3)
			{
				stalemate++;
				for (int i = 0; i < 3; i++)
				{
					for (int x = 0; x < 3; x++)
					{
						gameBoard[i][x] = 0;
					}
				}
			}
		}
		//checks if start game is zero so that i have some way to switch from the main menu to the game board.
		if (startGame == 0)
		{
			//for each button it checks if it has been clicked or not.
			for (int i = 0; i < numberOfButtons; i++)
			{
				buttons[i].buttonBooundingBox = { float(buttons[i].Location.x), float(buttons[i].Location.y), (float)buttons[i].ButtonTexture.width * buttonScale , (float)buttons[i].ButtonTexture.height * buttonScale };

				if (CheckCollisionPointRec(mousePoint, buttons[i].buttonBooundingBox))
				{
					if (buttons[i].buttonTextureNumber != 1)
					{
						buttons[i].ButtonTexture = buttonHighlighted;
					}
					buttons[i].buttonTextureNumber = 1;
					if (IsMouseButtonPressed(0))
					{
						buttons[i].ButtonTexture = buttonPressed;
						if (i == 0)
						{
							//starts the game and breaks from thie for.
							startGame = 1;
							break;
						}
						if (i == 1)
						{
							for (int x = 0; x < numberOfButtons; x++) {
								UnloadTexture(buttons[x].ButtonTexture);
							}
							CloseWindow();
							return 0;
						}
					}
				}
				else if (buttons[i].buttonTextureNumber != 0)
				{
					buttons[i].ButtonTexture = buttonUp;
					buttons[i].buttonTextureNumber = 0;
				}
			}
		}

		if (startGame == 0)
		{
			for (int i = 0; i < numberOfButtons; i++)
			{
				DrawTextureEx(buttons[i].ButtonTexture, buttons[i].Location, 0, buttonScale, RAYWHITE);

			}
			//Draws the game board and button text
			DrawRectangleLinesEx(buttons[0].buttonBooundingBox, 1, RED);
			DrawRectangleLinesEx(buttons[1].buttonBooundingBox, 1, RED);
			DrawText("Tic", screenSize * .1, screenSize * 0.1, buttonScale * 50, randomColor());
			DrawText("~", screenSize * .3, screenSize * 0.1, buttonScale * 50, randomColor());
			DrawText("Tac", screenSize * .4, screenSize * 0.1, buttonScale * 50, randomColor());
			DrawText("~", screenSize * .625, screenSize * 0.1, buttonScale * 50, randomColor());
			DrawText("Toe", screenSize * .7, screenSize * 0.1, buttonScale * 50, randomColor());
			DrawText("Play", buttons[0].Location.x + buttons[0].ButtonTexture.width / 2.5, buttons[0].Location.y + buttons[0].ButtonTexture.height / 4, buttonScale * 20, RAYWHITE);
			DrawText("Quit", buttons[1].Location.x + buttons[1].ButtonTexture.width / 2.5, buttons[1].Location.y + buttons[1].ButtonTexture.height / 4, buttonScale * 20, RAYWHITE);
		}
		





		ClearBackground(RAYWHITE);



		EndDrawing();
	}


	CloseWindow();

	return 0;

}