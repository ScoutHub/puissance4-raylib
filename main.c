#include <stdio.h>
#include "raylib.h"

#define SCREEN_WIDTH   800
#define SCREEN_HEIGHT  900
#define ROWS           8
#define COLS           8
#define PAD            100

char board[8][8] = {0};

void draw_board()
{
	DrawRectangleLines(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT - PAD, BLACK);
	for(int i = 0; i < ROWS; ++i)
	{
		for (int j = 0; j < COLS; ++j)
		{
			DrawLine(100 * j, 0, 100 * j, SCREEN_HEIGHT - PAD, BLACK);
			
			if(board[i][j] == 1) DrawCircle((100 * i) + 50, (100 * j) + 50, 40, YELLOW);
			else if(board[i][j] == 2) DrawCircle((100 * i) + 50, (100 * j) + 50, 40, RED);
			else DrawCircleLines((100 * i) + 50, (100 * j) + 50, 40, BLACK);

		}
		DrawLine(0, 100 * i, SCREEN_WIDTH, 100 * i, BLACK);
	}
}

void mouse_action(Vector2 *mouse_coord, int *turn)
{
	int pos_x = (int) mouse_coord->x / 100;
	int pos_y = (int) mouse_coord->y / 100;
	if(board[pos_x][pos_y] == 0)
	{
		if(*turn == 0)
		{
			board[pos_x][pos_y] = 1;
			*turn = 1;
		}
		else
		{
			board[pos_x][pos_y] = 2;
			*turn = 0;
		}
	}
}

void redraw_piece()
{
	for (int i = 0; i < 8; ++i) {
		for (int j = 0; j < 7; ++j) {
			if(board[i][j] != 0 && board[i][j+1] == 0)
			{
				board[i][j+1] = board[i][j];
				board[i][j] = 0;
			}
		}
	}
}

int check_winner()
{
	for (int i = 0; i < ROWS; ++i) {
		for (int j = 0; j < COLS; ++j) {
			if(board[i][j] != 0)
			{
				// Vertical check
				if(board[i][j] == board[i][j+1] &&
					board[i][j+1] == board[i][j+2] &&
				 	 board[i][j+2] == board[i][j+3]) return board[i][j];

				// Horizontal check
				else if(board[i][j] == board[i+1][j] &&
						 board[i+1][j] == board[i+2][j] &&
				 	 	  board[i+2][j] == board[i+3][j]) return board[i][j];

				// Diagonal down check
				else if(board[i][j] == board[i+1][j+1] &&
						 board[i+1][j+1] == board[i+2][j+2] &&
						  board[i+2][j+2] == board[i+3][j+3]) return board[i][j];

				// Diagonal up check
				else if(board[i][j] == board[i+1][j-1] &&
						 board[i+1][j-1] == board[i+2][j-2] &&
						  board[i+2][j-2] == board[i+3][j-3]) return board[i][j];
			}
		}
	}
	return 0;
}

int main(void)
{
	int turn = 1, winner = 0;
	InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Puissance 4");
	while(!WindowShouldClose())
	{
		BeginDrawing();
		ClearBackground(DARKBLUE);
		draw_board();
		if(winner == 0)
		{
			if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
			{
				Vector2 mouse_position = GetMousePosition();
				mouse_action(&mouse_position, &turn);
			}
			redraw_piece();
			winner = check_winner();
		}
		if(winner) DrawText(winner == 1 ? "Yellow won !" : "Red won !", (SCREEN_WIDTH / 3) + 70, SCREEN_HEIGHT - 60, 30, WHITE);
		else DrawText(turn == 1 ? "Red turn" : "Yellow turn", (SCREEN_WIDTH / 3) + 70, SCREEN_HEIGHT - 60, 30, WHITE);
		EndDrawing();
	}
	return 0;
}
