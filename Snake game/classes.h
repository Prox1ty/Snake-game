#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>

class SnakeBody {
public:
	int posX = 0;
	int posY = 1;
	char c = 'O';
};

class Snake {
public:

	std::vector<SnakeBody> bodyArr = {  };

	Snake() {
		bodyArr.push_back(SnakeBody());
	}

	SnakeBody& getHead() {
		return bodyArr.front();
	}

	void grow() {
		bodyArr.push_back(SnakeBody());
	}
};


class Grid {
public:
	int food[2];
	char grid[9][9];
	Grid() {
		for (int i = 0; i < 9; i++) {
			for (int j = 0; j < 9; j++) {
				Grid::grid[i][j] = ' ';
			}
		}
	};
	void addFood();

	void addSnakeToGrid(Snake& snake);
	
	bool notFoodCollision(int snakeX, int snakeY, int foodX, int foodY);

	bool notEndGame(Snake& mySnake, int snakeX, int snakeY);

	void move(Snake& snake, int newRow, int newCol, int foodX, int foodY);

	void renderGrid();
};