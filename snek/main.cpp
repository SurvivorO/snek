#include<iostream>
#include<windows.h>

#define UP 0
#define DOWN 1
#define LEFT 2
#define RIGHT 3

const int width = 40;
const int height = 20;


int fruitCordX;
int fruitCordY;
int prev;
int tailLen;
int playerHeadPosX;
int playerHeadPosY;

int moveDirection[100];
int playerPosX[100];
int playerPosY[100];

void gameInit();
void gameRender();
void handleMovement(int []);




int main() {

	
	HANDLE stdHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO cursorInfo;
	GetConsoleCursorInfo(stdHandle, &cursorInfo);
	cursorInfo.bVisible = 0;
	SetConsoleCursorInfo(stdHandle, &cursorInfo);

	gameInit();

	while (true) {

		SetConsoleCursorPosition(stdHandle, { 0,0 });
				
		if (GetAsyncKeyState(VK_ESCAPE)) {
			system("cls");
			return 0;
		}
		else if (GetAsyncKeyState('W')) {
			moveDirection[0] = UP;
			if (tailLen != 1) {
				for (int i = 0; i < tailLen; i++) {
					moveDirection[i + 1] = prev;
					prev = moveDirection[i];
				}
			}
			handleMovement(moveDirection);
		}
		else if (GetAsyncKeyState('A')) {
			moveDirection[0] = LEFT;
			if (tailLen != 1) {
				for (int i = 0; i < tailLen; i++) {
					moveDirection[i + 1] = prev;
					prev = moveDirection[i];
				}
			}
			handleMovement(moveDirection);
		}
		else if (GetAsyncKeyState('S')) {
			moveDirection[0] = DOWN;
			if (tailLen != 1) {
				for (int i = 0; i < tailLen; i++) {
					moveDirection[i + 1] = prev;
					prev = moveDirection[i];
				}
			}
			handleMovement(moveDirection);
		}
		else if (GetAsyncKeyState('D')) {
			moveDirection[0] = RIGHT;
			if (tailLen != 1) {
				for (int i = 0; i < tailLen; i++) {
					moveDirection[i + 1] = prev;
					prev = moveDirection[i];
				}
			}
			handleMovement(moveDirection);
		}
		else {
			handleMovement(moveDirection);
		}

		if (playerPosX[0] == fruitCordX && playerPosY[0] == fruitCordY) {
			fruitCordX = rand() % width;
			fruitCordY = rand() % height;
			tailLen += 1;
		}

		

		if (playerHeadPosX == 0 || playerHeadPosX == width || playerHeadPosY == 0 || playerHeadPosX == height) {
			system("cls");
			return 0;
		}
		gameRender();
		Sleep(500);
	}

	return 0;
}

void gameRender() {
	int i = 0;
	bool isPlayer = false;
	while (i < height) {
		
		int j = 0;
		while (j < width) {

			for (int k = 0; k < tailLen; k++) {
				if (playerPosX[k] == j && playerPosY[k] == i) {
					std::cout << "o";
					isPlayer = true;
				}
				else {
					isPlayer = false;
				}
			}
			if (i == 0 || i == height - 1) {
				std::cout << '-';
			}
			else if (j == fruitCordX && i == fruitCordY) {
				std::cout << "*";
			}
			else if (j == 0 || j == width - 1) {
				std::cout << "|";
			}
			else if(!isPlayer){
				std::cout << " ";
			}

			j = j + 1;
		}
		std::cout << "\n";
		i = i + 1;
	}
}

void handleMovement(int moveDir[]) {

	for (int i = 0; i < tailLen; i++) {
		if(moveDir[i] == RIGHT) {
			playerPosX[i] += 1;
		}
		else if (moveDir[i] == DOWN) {
			playerPosY[i] += 1;
		}
		else if (moveDir[i] == LEFT) {
			playerPosX[i] -= 1;
		}
		else if (moveDir[i] == UP) {
			playerPosY[i] -= 1;
		}		
	}

	playerHeadPosX = playerPosX[0];
	playerHeadPosY = playerPosY[0];

}

void gameInit() {

	fruitCordX = rand() % width;
	fruitCordY = rand() % height;

	moveDirection[0] = rand() % 4;
	prev = moveDirection[0];

	tailLen = 1;

	playerHeadPosX = 14;
	playerHeadPosY = 14;


	playerPosX[0] = playerHeadPosX;
	playerPosY[0] = playerHeadPosY;

}