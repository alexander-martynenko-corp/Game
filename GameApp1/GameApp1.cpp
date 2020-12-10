// GameApp1.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <conio.h>
#include <Windows.h>

#define SPACE 32
#define UP 72
#define DOWN 80
#define LEFT 75
#define RIGHT 77
#define EXIT 27
#define SAVE 49
#define NewGame 49
#define LOAD 50

struct BALL {
	int x;
	int y;
	char show = '+';
};

struct PERSON {
	int x;
	int y;
};

struct TEAM {
	PERSON* players;
	char show = ' ';
};

struct FIELD {
	int Nsize = 30;
	int Msize = 80;
	char show = ' ';
};

struct OBJECTS {
	BALL* ball;
	TEAM* team_a;
	TEAM* team_b;
	FIELD* field;
	int countPlayers = 6;
};

using namespace std;

void FirstMenu();		//draw first menu

OBJECTS* init();		//initialization objects

void Game(OBJECTS*);	//Logic of actions

OBJECTS* LoadObj();			//Load objects from file

void Clear(OBJECTS*);	//clear objects

void show(OBJECTS*);	//show all objects

void showPlayers(int, int, OBJECTS*); //show all objects

void moveBallUp(OBJECTS* allObj) {
	allObj->ball->x--;
}

void moveBallDown(OBJECTS* allObj) {
	allObj->ball->x++;
}

void moveBallRight(OBJECTS* allObj) {
	allObj->ball->y++;
}

void moveBallLeft(OBJECTS* allObj) {
	allObj->ball->y--;
}

int main()
{
	FirstMenu();
	return 0;
}



void FirstMenu() {
	char ch;
	int code;

	while (1) {
		bool fl = false;

		system("cls");
		cout << "\n\n\t\tWELCOME TO GAME" << endl << endl;
		cout << "\t1 - start new game" << endl;
		cout << "\t2 - load previous game" << endl;
		cout << "\t\tESC - exit" << endl;

		ch = _getch();
		code = static_cast<int>(ch);
		OBJECTS* allObj;

		switch (ch) {
		case NewGame:
			allObj = init();
			Game(allObj);
			Clear(allObj);
			break;

		case LOAD:
			//allObj = LoadObj();
			//Game(allObj);
			//Clear(allObj);
			break;

		case EXIT:
			fl = true;
		}

		if (fl) {
			break;
		}
	}
}

OBJECTS* init() {
	OBJECTS* allObj = new OBJECTS;
	allObj->ball = new BALL;

	allObj->field = new FIELD;

	allObj->ball->x = allObj->field->Nsize / 2;
	allObj->ball->y = allObj->field->Msize / 2;

	allObj->team_a = new TEAM;
	allObj->team_a->show = '$';
	allObj->team_a->players = new PERSON[allObj->countPlayers];

	allObj->team_b = new TEAM;
	allObj->team_b->show = '%';
	allObj->team_b->players = new PERSON[allObj->countPlayers];

	int pos = 1;
	for (int i = 0; i < allObj->countPlayers; ++i) {
		allObj->team_a->players[i].x = 1;
		allObj->team_a->players[i].y = pos;

		allObj->team_b->players[i].x = allObj->field->Nsize - 2;
		allObj->team_b->players[i].y = pos;

		pos += allObj->field->Msize / allObj->countPlayers - 1;
	}

	return allObj;
}

void Clear(OBJECTS* allObj) {
	delete allObj->field;

	delete[] allObj->team_b->players;
	delete[] allObj->team_a->players;

	delete allObj->team_a;
	delete allObj->team_b;

	delete allObj->ball;

	allObj->ball = NULL;
	allObj->team_b = NULL;
	allObj->team_a = NULL;
	allObj->field = NULL;
	allObj = NULL;
	return;
}

void Game(OBJECTS* allObj) {
	char ch;
	int code;

	while (1)
	{
		//system("cls");
		show(allObj);

		ch = _getch();
		code = static_cast<int>(ch);
		bool fl = false;

		switch (ch) {

		case UP:
			moveBallUp(allObj);
			break;

		case SPACE:
			//movePersons(allObj);
			break;

		case DOWN:
			moveBallDown(allObj);
			break;

		case RIGHT:
			moveBallRight(allObj);
			break;

		case LEFT:
			moveBallLeft(allObj);
			break;

		case EXIT:
			fl = true;
			break;

		case SAVE:
			//save(allObj);
			fl = true;
		}

		if (fl) // если клавиша esc
			break;
	}
}

void show(OBJECTS* allObj) {
	
	for (int i = 0; i < allObj->field->Nsize; ++i) {		//30
		for (int j = 0; j < allObj->field->Msize; ++j) {	//80
			showPlayers(i, j, allObj);
		}
		cout << endl;
	}
	
}

void showPlayers(int i, int j, OBJECTS* allObj) {
	if (i == 0 || i == allObj->field->Nsize - 1) {
		cout << "|";
		return;
	}

	if (j == 0 || j == allObj->field->Msize - 1) {
		cout << "_";
		return;
	}

	for (int k = 0; k < allObj->countPlayers; ++k) {
		if (i == allObj->team_a->players[k].x && j == allObj->team_a->players[k].y) {
			cout << allObj->team_a->show;
			return;
		}

		if (i == allObj->team_b->players[k].x && j == allObj->team_b->players[k].y) {
			cout << allObj->team_b->show;
			return;
		}
	}
	if (i == allObj->ball->x && j == allObj->ball->y) {
		cout << allObj->ball->show;
		return;
	}

	cout << allObj->field->show;
	return;
}