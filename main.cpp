#include <iostream>
#include <time.h>
#include <conio.h>

enum eDir { STOP = 0, LEFT = 1, UPLEFT = 2, DOWNLEFT = 3, RIGHT = 4, UPRIGHT = 5, DOWNRIGHT = 6};

using namespace std;

class cBall {
private:
	int x, y; 
	int originalX, originalY;
	eDir Direction;
	
public:
	cBall(int x_, int y_) {
		originalX = x_;
		originalY = y_;
		Direction = STOP;
		x = x_;
		y = y_;
	}

	void Reset() {
		x = originalX;
		y = originalY;
		Direction = STOP;
	}

	void changeDirection(eDir d) {
		Direction = d;
	}

	void Move() {
		switch (Direction) {
		case STOP:
			break;
		case LEFT:
			x--;
			break;
		case UPLEFT:
			x--;
			y--;
			break;
		case DOWNLEFT:
			x--;
			y++;
			break;
		case RIGHT:
			x++;
			break;
		case UPRIGHT:
			x++;
			y--;
			break;
		case DOWNRIGHT:
			x++;
			y++;
			break;
		}
	}

	void randomDirection() {
		Direction = (eDir)((rand() % 6) + 1);

	}

	inline int getX() { return x; }
	inline int getY() { return y; }
	inline eDir getDirection() { return Direction; }

	friend ostream & operator << (ostream & o, cBall b) {
		o << "Ball " << "[" << b.x << "," << b.y << "] " << "Direction = " << b.Direction;
		return o;
	}

};

class cpaddle {
private:
	int x, y;
	int originalX, originalY;
public:
	cpaddle() {
		x = y = 0;
	}
	cpaddle(int x_, int y_) {
		x = x_;
		y = y_;
		originalX = x_;
		originalY = y_;
	}

	void Reset() {
		x = originalX;
		y = originalY;
	}

	inline void MoveUp() { y--; }
	inline void MoveDown() { y++; }
	inline int getX() { return x; }
	inline int getY() { return y; }

	friend ostream& operator << (ostream& o, cpaddle b) {
		o << "Paddle" << "[" << b.x << "," << b.y << "] " ;
		return o;
	}
};

class cGameManager {
private:
	int width, height;
	int score1, score2;
	char up1, down1, up2, down2;
	bool quit;
	cBall* ball;
	cpaddle* Player1;
	cpaddle* Player2;
public:
	cGameManager(int w, int h) {
	
		srand(time(NULL));
		quit = false;
		width = w;
		height = h;
		score1 = score2 = 0;
		up1 = 'w';
		down1 = 's';
		up2 = 'i';
		down2 = 'k';
		ball = new cBall(w / 2, h / 2);
		Player1 = new cpaddle(1, h / 2 - 3);
		Player2 = new cpaddle(w - 2, h / 2 - 3);
		
	}

	~cGameManager() {
		delete ball, Player1, Player2;
	}

	void ScoreUp(cpaddle * player) {
		if (player == Player1) {
			score1++;
		}
		else if (player == Player2) {
			score2++;
		}
		ball->Reset();
		Player1->Reset();
		Player2->Reset();
	}

	void Draw() {

		system("cls");
		for (int i = 0; i < width + 1; i++) {
			cout << "\xB2";
		}

		for (int i = 0; i < height; i++) {
			for (int j = 0; j < width; j++) {
				int ballx = ball->getX();
				int bally = ball->getY();
				int player1x = Player1->getX();
				int player1y = Player1->getY();
				int player2x = Player2->getX();
				int player2y = Player2->getY();

				if (j == 0)
					cout << "\xB2";

				if (ballx == j && bally == i)
					cout << "O";
				else if (player1x == j && player1y == i)
					cout << "\xDB";
				else if (player2x == j && player2y == i)
					cout << "\xDB";
				//player1
				else if (player1x == j && player1y+1 == i)
					cout << "\xDB";
				else if (player1x == j && player1y+2 == i)
					cout << "\xDB";
				else if (player1x == j && player1y + 3 == i)
					cout << "\xDB";
				//player2
				else if (player2x == j && player2y + 1 == i)
					cout << "\xDB";
				else if (player2x == j && player2y + 2 == i)
					cout << "\xDB";
				else if (player2x == j && player2y + 3 == i)
					cout << "\xDB";

				else
					cout << " ";

				if (j == width - 1)
					cout << "\xB2";
			}
			cout << endl;
		}

		for (int i = 0; i < width + 2; i++) {
			cout << "\xB2";

		}
		cout << endl;
		cout << "Player1: " << score1 << endl;
		cout << "Player2: " << score2 << endl;

	}

	void Input() {
		ball->Move();

		int ballx = ball->getX();
		int bally = ball->getY();
		int player1x = Player1->getX();
		int player1y = Player1->getY();
		int player2x = Player2->getX();
		int player2y = Player2->getY();

		if (_kbhit()) {
			char current = _getch();
			if (current == up1)
				if (player1y > 0)
					Player1->MoveUp();
			if (current == up2)
				if (player2y > 0)
					Player2->MoveUp();
			if (current == down1)
				if (player1y+4 < height)
					Player1->MoveDown();
			if (current == down2)
				if (player2y+4 < height)
					Player2->MoveDown();

			if (ball->getDirection() == STOP)
				ball->randomDirection();

			if (current == 'q')
				quit = true;


		}
	}

	void Bounce() {
		int ballx = ball->getX();
		int bally = ball->getY();
		int player1x = Player1->getX();
		int player1y = Player1->getY();
		int player2x = Player2->getX();
		int player2y = Player2->getY();

		for (int i = 0; i < 4; i++) {
			if (ballx == player1x+1 && bally == player1y+i)
				ball->changeDirection((eDir)(rand() % 3 + 4));
			if (ballx == player2x - 1 && bally == player2y + i)
				ball->changeDirection((eDir)(rand() % 3 + 1));
		}
		
		if (bally == 1) {
			if (ball->getDirection() == UPRIGHT)
				ball->changeDirection(DOWNRIGHT);
			else if (ball->getDirection() == UPLEFT)
				ball->changeDirection(DOWNLEFT);
		}

		if (bally == height-1) {
			if (ball->getDirection() == DOWNRIGHT)
				ball->changeDirection(UPRIGHT);
			else if (ball->getDirection() == DOWNLEFT)
				ball->changeDirection(UPLEFT);
		}

		if (ballx == width - 1)
			ScoreUp(Player1);
		if (ballx == 1)
			ScoreUp(Player2);
	}

	void Run() {
		while (!quit) {
			Draw();
			Input();
			Bounce();
		}
	}
};

int main() {
	cGameManager c(40, 20);
	c.Run();
	return 0;
}
