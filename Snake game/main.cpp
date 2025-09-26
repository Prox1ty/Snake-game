#include <iostream>
#include "classes.h"
#include <chrono>
#include <thread>
#include <conio.h>

const double TARGET_FPS = 3.0;
const std::chrono::milliseconds FRAME_TIME_MS(static_cast<long long>(1000.0 / TARGET_FPS));

void gameLoop(Grid& myGrid, Snake& mySnake, int foodX, int foodY) {

	int xSpeed = 1;
	int ySpeed = 0;
	while (true) {
		if (!myGrid.notFoodCollision(mySnake.getHead().posX, mySnake.getHead().posY, foodX, foodY)) {
			mySnake.grow();
			myGrid.addFood();
			foodX = myGrid.food[0];
			foodY = myGrid.food[1];
		}
		else if (!myGrid.notEndGame(mySnake, mySnake.getHead().posX, mySnake.getHead().posY)) {
			xSpeed = 0;
			ySpeed = 0;
			std::cout << std::endl;
			std::cout << "*** GAME OVER ***";
			return;
			system("pause");
		}
		auto startTime = std::chrono::high_resolution_clock::now();
		system("cls");
		if (_kbhit()) {
			char input = _getch();
			if (input == 'a') {
				xSpeed = -1;
				ySpeed = 0;
			}
			else if (input == 'd') {
				xSpeed = 1;
				ySpeed = 0;
			}
			else if (input == 's') {
				ySpeed = 1;
				xSpeed = 0;
			}
			else if (input == 'w') {
				ySpeed = -1;
				xSpeed = 0;
			}
		}
		/*ySpeed = ySpeed;
		xSpeed = xSpeed;*/

		if ((mySnake.getHead().posX == 8) && xSpeed == 1) {
			mySnake.getHead().posX = -1;
		}
		else if ((mySnake.getHead().posX == 0) && (xSpeed == -1)) {
			mySnake.getHead().posX = 9;
		}
		else if ((mySnake.getHead().posY == 0) && ySpeed == -1) {
			mySnake.getHead().posY = 9;
		}
		else if ((mySnake.getHead().posY == 8) && (ySpeed == 1)) {
			mySnake.getHead().posY = -1;
		}
		myGrid.move(mySnake, mySnake.getHead().posY + ySpeed, mySnake.getHead().posX + xSpeed, foodX, foodY);
		myGrid.renderGrid();

		auto endTime = std::chrono::high_resolution_clock::now();
		auto elapsedTime = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime);

		if (elapsedTime < FRAME_TIME_MS) {
			std::this_thread::sleep_for(FRAME_TIME_MS - elapsedTime);
		}
	}

}


int main() {

	Grid myGrid;
	Snake mySnake;
	myGrid.addFood();
	myGrid.addSnakeToGrid(mySnake);
	gameLoop(myGrid, mySnake, myGrid.food[0], myGrid.food[1]);

	return 0;
}