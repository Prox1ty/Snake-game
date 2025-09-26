#include "classes.h"

void Grid::addSnakeToGrid(Snake& snake) {
	for (auto& body_part : snake.bodyArr) {
		grid[body_part.posY][body_part.posX] = body_part.c;
	}
}

void Grid::addFood() {
	int randomX = rand() % 9;
	int randomY = rand() % 9;
	
	food[0] = randomX;
	food[1] = randomY;
}

void Grid::move(Snake& snake, int newRow, int newCol, int foodX, int foodY) {

	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++) {
			grid[i][j] = ' ';
		}
	}

	for (int i = snake.bodyArr.size() - 1; i > 0; i--) { 
		snake.bodyArr[i].posX = snake.bodyArr[i - 1].posX;
		snake.bodyArr[i].posY = snake.bodyArr[i - 1].posY;
	}
	snake.getHead().posY = newRow;
	snake.getHead().posX = newCol;
	Grid::grid[foodY][foodX] = '#';
	
	for (const auto& body_part : snake.bodyArr) {
		Grid::grid[body_part.posY][body_part.posX] = body_part.c;
	}
}

void Grid::renderGrid() {
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++) {
			std::cout << grid[i][j];
		}
		std::cout << '\n';
	}
}

bool Grid::notFoodCollision(int snakeX, int snakeY, int foodX, int foodY) {
	if ((snakeX == foodX) && (snakeY == foodY)) return false;
	else return true;
}

bool Grid::notEndGame(Snake& mySnake, int snakeX, int snakeY) {
	int size = mySnake.bodyArr.size();
	for (int i = 1; i < size; i++) {
		if ((snakeX == mySnake.bodyArr[i].posX) && (snakeY == mySnake.bodyArr[i].posY)) {
			return false;
		}
		else {
			return true;
		}
	}
}