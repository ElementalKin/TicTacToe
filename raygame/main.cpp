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
	//made this for fun.
	//Color SeizureMaker = { rand() % 256,rand() % 256 ,rand() % 256 ,rand() % 256 };
	//return SeizureMaker;
	return BLACK;
}


int checkIfWon(int** gameBoard, int boardSize)
{
	int playerOneScore = 0;
	int playerTwoScore = 0;
	int stalemate = 0;
	//checking if the players have three in a row.
	for (int i = 0; i < boardSize; ++i)
	{
		//checks colums for player one.
		for (int x = 0; x < boardSize; ++x)
		{
			if (gameBoard[x][i] == 1) { playerOneScore++; }
			else if (gameBoard[x][i] == 2 || 0) { playerOneScore = 0; }
			if (playerOneScore == 3) { return 1; }
		}
	    playerOneScore = 0;
		//checks rows for player one.
		for (int x = 0; x < boardSize; ++x)
		{
			if (gameBoard[i][x] == 1) { playerOneScore++; }
			else if (gameBoard[i][x] == 2 || 0) { playerOneScore = 0; }
			if (playerOneScore == 3) { return 1; }
		}
		playerOneScore = 0; 
		for (int x = 0; x < boardSize; ++x)
		{
			if (x + i < boardSize) {
				if (gameBoard[x + i][x] == 1) { playerOneScore++; }
				else if (gameBoard[x + i][x] == 2 || 0) { playerOneScore = 0; }
				if (playerOneScore == 3) { return 1; }
			}
		}
		playerOneScore = 0;
		for (int x = 0; x < boardSize; ++x)
		{
			if (x + i < boardSize) {
				if (gameBoard[x][x+i] == 1) { playerOneScore++; }
				else if (gameBoard[x][x+i] == 2 || 0) { playerOneScore = 0; }
				if (playerOneScore == 3) { return 1; }
			}
		}
		playerOneScore = 0;
		for (int x = 0; x < boardSize; ++x)
		{
			if (x + i < boardSize) {
				if (gameBoard[x][(boardSize - (x + i)) - 1] == 1) { playerOneScore++; }
				else if (gameBoard[x][(boardSize - (x + i)) - 1] == 2 || 0) { playerOneScore = 0; }
				if (playerOneScore == 3) { return 1; }
			}
		}
		playerOneScore = 0;
		for (int x = 0; x < boardSize; ++x)
		{
			if (x + i < boardSize) {
				if (gameBoard[x+i][(boardSize - (x )) - 1] == 1) { playerOneScore++; }
				else if (gameBoard[x+i][(boardSize - (x)) - 1] == 2 || 0) { playerOneScore = 0; }
				if (playerOneScore == 3) { return 1; }
			}
		}
		playerOneScore = 0;
		for (int x = 0; x < boardSize; ++x)
		{
			if (gameBoard[i][x] == 2) { playerTwoScore++; }
			else if (gameBoard[i][x] == 1 || 0) { playerTwoScore = 0; }
			if (playerTwoScore == 3) { return 2; }
		}
		playerTwoScore = 0;
		for (int x = 0; x < boardSize; ++x)
		{
			if (gameBoard[x][i] == 2) { playerTwoScore++; }
			else if (gameBoard[x][i] == 1 || 0) { playerTwoScore = 0; }
			if (playerTwoScore == 3) { return 2; }
		}
		playerTwoScore = 0;
		for (int x = 0; x < boardSize; ++x)
		{
			if (x + i < boardSize) {
				if (gameBoard[x + i][x] == 2) { playerTwoScore++; }
				else if (gameBoard[x + i][x] == 1 || 0) { playerTwoScore = 0; }
				if (playerTwoScore == 3) { return 2; }
			}
		}
		playerTwoScore = 0;
		for (int x = 0; x < boardSize; ++x)
		{
			if (x + i < boardSize) {
				if (gameBoard[x ][x+i] == 2) { playerTwoScore++; }
				else if (gameBoard[x][x+i] == 1 || 0) { playerTwoScore = 0; }
				if (playerTwoScore == 3) { return 2; }
			}
		}
		playerTwoScore = 0;
		for (int x = 0; x < boardSize; ++x)
		{
			if (x + i < boardSize) {
				if (gameBoard[x][boardSize - (x + i) - 1] == 2) { playerTwoScore++; }
				else if (gameBoard[x][boardSize - (x + i) - 1] == 1 || 0) { playerTwoScore = 0; }
				if (playerTwoScore == 3) { return 2; }
			}
		}
		playerTwoScore = 0;
		for (int x = 0; x < boardSize; ++x)
		{
			if (x + i < boardSize) {
				if (gameBoard[x+i][boardSize - (x) - 1] == 2) { playerTwoScore++; }
				else if (gameBoard[x+i][boardSize - (x) - 1] == 1 || 0) { playerTwoScore = 0; }
				if (playerTwoScore == 3) { return 2; }
			}
		}
		playerTwoScore = 0;
		for (int x = 0; x < boardSize; ++x)
		{
			if (gameBoard[i][x] == 0) { stalemate++; }
		}

	}
	if (stalemate == 0) { return 3; }
	return 0;
}

	


int main()
{

	//variables for the game to work.
	int turns = 1;
	bool boardSizeChosen = false;
	//the game board and who is currently where.
	
	int BoardSize;
	int player1Score = 0;
	int player2Score = 0;
	int stalemate = 0;
	//the bounding boxes for the board.

	
	const int numberOfButtons = 2;
	Button buttons[numberOfButtons];
	int startGame = 0;
	int boardSize;
	int screenSize = 1000;
	//Ask the player for a size so that it sizes the board to the right size.
	std::cout << "Please Enter a Number between 3 and 8." << std::endl;
	while (boardSizeChosen == false)
	{
		std::cin >> boardSize;
		if (boardSize >= 3 && 8 >= boardSize)
		{

			boardSizeChosen = true;
			break;
		}
		std::cout << "I said Enter a Number between 4 and 10." << std::endl;
	}

	int* board_data = new int[boardSize*boardSize];
	int** board = new int*[boardSize];
	for (int i = 0; i < boardSize; ++i) 
	{
		board[i] = board_data + boardSize * i;
	}
	for (int i = 0; i < boardSize; i++)
	{
		for (int x = 0; x < boardSize; x++)
		{
			board[i][x] = 0;
		}
	}
	Rectangle* boundingBox_data = new Rectangle[boardSize*boardSize];
	Rectangle** TTTBoundingBox = new Rectangle*[boardSize];
	for (int i = 0; i < boardSize; ++i)
	{
		TTTBoundingBox[i] = boundingBox_data + boardSize * i;
	}

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
	for (int x = 0; x < boardSize; x++) 
	{
		for (int i = 0; i < boardSize; i++)
		{
			if(i == 0 && x == 0){ TTTBoundingBox[x][i] = { float((screenSize*.01)), float(screenSize*(.1)), float(screenSize/(boardSize+ 1)) , float(screenSize / (boardSize+ 1)) }; }
			else if (i == 0) { TTTBoundingBox[x][i] = { float((screenSize*.01)), float(screenSize/(boardSize+ 1) + TTTBoundingBox[x - 1][0].y), float(screenSize / (boardSize+ 1)) , float(screenSize / (boardSize+1)) }; }
			else { TTTBoundingBox[x][i] = { TTTBoundingBox[x][i-1].x + TTTBoundingBox[x][i - 1].width, float(TTTBoundingBox[x][0].y), float(screenSize / (boardSize + 1)) , float(screenSize / (boardSize + 1)) }; }

		}
	}

	SetTargetFPS(60);
	while (!WindowShouldClose())
	{
		mousePoint = GetMousePosition();
		
		BeginDrawing();
		if (startGame == 1)
		{
			//Drawing the game board and the scores
			for (int x = 0; x < boardSize ; x++) 
			{
				for (int i = 0; i < boardSize; i++) {DrawRectangleLinesEx(TTTBoundingBox[x][i], 1, BLACK);}
			}
			DrawText(FormatText("Player1: %01i",  player1Score), screenSize * .01, 0, buttonScale * 10, randomColor());
			DrawText(FormatText("Player2: %01i", player2Score), screenSize * .75, 0, buttonScale * 10, randomColor());
			DrawText(FormatText("Turn: %01i", turns), screenSize * .35, 0, buttonScale * 10, randomColor());
			DrawText(FormatText("Stalemate: %01i", stalemate), screenSize * .35, screenSize * .03, buttonScale * 10, randomColor()); 

			for (int i = 0; i < boardSize; i++)
			{
				for (int x = 0; x < boardSize; x++) 
				{
					//checks if the left button is pressed.
					if (IsMouseButtonPressed(0))
					{
						//checking if the mouse is in any of the boxes
						if (CheckCollisionPointRec(mousePoint, TTTBoundingBox[i][x]))
						{
							//check whos turn it is.
							if (turns == 1)
							{
								//checks if the box is open
								if (board[i][x] == 0)
								{
									//if it is it makes it to who ever turn it is to the box then 
									board[i][x] = 1;
									turns = 2;
								}
							}
							else if (turns == 2)
							{
								if (board[i][x] == 0)
								{
									board[i][x] = 2;
									turns = 1;
								}
							}
							//checks if someone has won
							if (checkIfWon(board, boardSize) == 1)
							{
								player1Score++;
								for (int i = 0; i < boardSize; i++)
								{
									for (int x = 0; x < boardSize; x++)
									{
										board[i][x] = 0;
									}
								}
							}
							else if (checkIfWon(board, boardSize) == 2)
							{
								player2Score++;
								for (int i = 0; i < boardSize; i++)
								{
									for (int x = 0; x < boardSize; x++)
									{
										board[i][x] = 0;
									}
								}
							}
							else if (checkIfWon(board, boardSize) == 3)
							{
								stalemate++;
								for (int i = 0; i < boardSize; i++)
								{
									for (int x = 0; x < boardSize; x++)
									{
										board[i][x] = 0;
									}
								}
							}

						}
					}

					//draws the xs(player 1)
					if (board[i][x] == 1)
					{
						DrawLine(TTTBoundingBox[i][x].x, TTTBoundingBox[i][x].y, TTTBoundingBox[i][x].x + TTTBoundingBox[i][x].width, TTTBoundingBox[i][x].y + TTTBoundingBox[i][x].height, BLACK);
						DrawLine(TTTBoundingBox[i][x].x + TTTBoundingBox[i][x].width, TTTBoundingBox[i][x].y, TTTBoundingBox[i][x].x, TTTBoundingBox[i][x].y + TTTBoundingBox[i][x].height, BLACK);
					}
					//Draws the circles(player 2)
					if (board[i][x] == 2)
					{
						DrawCircleLines(TTTBoundingBox[i][x].x + TTTBoundingBox[i][x].width / 2, TTTBoundingBox[i][x].y + TTTBoundingBox[i][x].height / 2, TTTBoundingBox[i][x].width/2, BLACK);
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