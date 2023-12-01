//This Program was made by Zane Taylor
//10:14 PM
//finished 1:00 AM, I had a snack and coffee break so I think this took around 2:30? The only thing that was a bitch was input checking.
//some of this is overkill and theres a billion ways to do it, but this is my implementation.
// 
//Starting a tictactoe game for funsies and review by my boy

#include <iostream>
#include <string>
#include <random>

using namespace std;

void TTTCellOutput(string user, string input, char ticTacToe[]);
bool WinCheck(char ticTacToe[]);
string inputChecker(string input, int min, int max);

int main() {
	string userInput = "start";
	string gamesToPlayStr;

	int gamesToPlayInt, movesMade = 0, gameTotal = 0, wonGames = 0, lostGames = 0;

	bool inputCheck = false, gameOver = false;

	char ticTacToe[9] = { '#','#','#',
						  '#','#','#',
						  '#','#','#' };

	//sys dialog and datagrabbing
	cout << "Welcome to Tic-Tac-Toe Mother Fucker!\n" << "You are O and will go first\n" << "Make a play by typing which square you want to enter your O\n";
	TTTCellOutput("Console",userInput, ticTacToe);

	cout << "\nHow many games would you like to play? Type an integer 1-10: \n";
	cin >> gamesToPlayStr;

	//making sure our input is valid and setting an int for easier math
	gamesToPlayStr = inputChecker(gamesToPlayStr, 0, 11);
	gamesToPlayInt = stoi(gamesToPlayStr);
	gameTotal = gamesToPlayInt;
	cout << "At any time if you would like to quit, please enter 'exit'\n\n";
	
	//This is where our main game is played.
	while (gamesToPlayInt > 0) {
		
		//getting everything ready
		cout << "Starting new game!\n";
		TTTCellOutput("Console", userInput, ticTacToe);
		gameOver = false;

		while (gameOver == false) {

			//USERS MOVE getting user input and checking + wincheck
			if (gameOver == false) {
				//output
				cout << "Its your move! Please select a cell: \n";
				cin >> userInput;

				//input check + making move
				userInput = inputChecker(userInput, 0, 10);


				cout << "Your move was: " << userInput << "\n";
				TTTCellOutput("User", userInput, ticTacToe);

				//wincheck
				gameOver = WinCheck(ticTacToe);
				if (gameOver == true) {
					cout << "\n\nCongrats! You won!\n\n";
					wonGames++;
				}

				//tiecheck
				movesMade++;
				if (movesMade == 5) {
					gameOver = true;
					cout << "You tied!";
				}
			}

			//computers move with a wincheck
			if (gameOver == false) {
				cout << "The Computers move was: \n";
				TTTCellOutput("Computer", userInput, ticTacToe);
				gameOver = WinCheck(ticTacToe);
				if (gameOver == true) {
					cout << "\n\nI'm sorry! You Lost!\n\n";
					lostGames++;
				}
			}
		}
		//resetting everything
		gamesToPlayInt--;

		if (gamesToPlayInt > 0) {
			cout << "Time to play another game!\n\n";
		}

		for (int i = 0; i < 9; i++) {
			ticTacToe[i] = '#';
		}
		movesMade = 0;
	}
	cout << "Out of " << gameTotal << " games, you won " << wonGames << " and lost " << lostGames;

		cout << "\n\nGoodbye, have a nice day!\n\n";
		return 418;
}

void TTTCellOutput(string user, string input, char ticTacToe[]) {
	//startup dialog to save typing
	int a = 0,
		b = 1,
		c = 2;

	if (user == "Console") {
		if (input == "start") {
			a = 1;
			b = 2;
			c = 3;
			while (c < 10) {
				cout << "+---+---+---+\n"
					<< "| " << a << " | " << b << " | " << c << " |\n"
					<< "+---+---+---+\n";
				a += 3;
				b += 3;
				c += 3;
			}
			return;
		}
	}
	//real deal for real time

	//our game is going to run purely off of a 9 cell array for simplicity.
	//The game will be initalized to #, if something tries to overwrite our move, we will send an error message
	//we'll use the RAND function to pick a number from 1-9 and say its the computer.

	//special input check and move maker
	//I could've done this better but who gives a shit
	if (user == "User") {
		while (ticTacToe[stoi(input) - 1] != '#') {
			cout << "You tried to move somewhere that is already taken! Please try again \n";
			cin >> input;
			for (int i = 0; i < input.length(); i++) {
				while (isdigit(input[i]) == false) {
					i = 0;
					cout << "Your input was invalid! Please try again: \n";
					cin >> input;
				}
				while (!((stoi(input) < 10) && (stoi(input) > 0))) {
					cout << "Your input was invalid! Please try again: \n";
					cin >> input;
				}
			}
		}
		if (ticTacToe[stoi(input) - 1] == '#') {
			ticTacToe[stoi(input) - 1] = 'O';
		}
		while (c < 9) {
			cout << "+---+---+---+\n"
				<< "| " << ticTacToe[a] << " | " << ticTacToe[b] << " | " << ticTacToe[c] << " |\n"
				<< "+---+---+---+\n";
			a += 3;
			b += 3;
			c += 3;
		}
		return;
	}

	//randomly genorating a move and checking it to make sure its right
	//I dont feel like going ham on the randomizer so this is what you get
	if (user == "Computer") {
		srand(time(NULL));
		int cInput = rand() % 9;

		while (ticTacToe[cInput] != '#') {
			cInput = rand() % 9;
		}
		if (ticTacToe[cInput] == '#') {
			ticTacToe[cInput] = 'X';
		}

		while (c < 10) {
			cout << "+---+---+---+\n"
				<< "| " << ticTacToe[a] << " | " << ticTacToe[b] << " | " << ticTacToe[c] << " |\n"
				<< "+---+---+---+\n";
			a += 3;
			b += 3;
			c += 3;
		}
	}
}

bool WinCheck(char ticTacToe[]) {
	bool win = false;

	//these are the vertical win conditions
	if ( (ticTacToe[0] == ticTacToe[3]) && (ticTacToe[3] == ticTacToe[6]) && (ticTacToe[0] != '#')) {
		win = true;
	}
	if ((ticTacToe[1] == ticTacToe[4]) && (ticTacToe[4] == ticTacToe[7]) && (ticTacToe[1] != '#')) {
		win = true;
	}
	if ((ticTacToe[2] == ticTacToe[5]) && (ticTacToe[5] == ticTacToe[8]) && (ticTacToe[2] != '#')) {
		win = true;
	}

	//these are the horizontal
	if ((ticTacToe[0] == ticTacToe[1]) && (ticTacToe[1] == ticTacToe[2]) && (ticTacToe[0] != '#')) {
		win = true;
	}
	if ((ticTacToe[3] == ticTacToe[4]) && (ticTacToe[4] == ticTacToe[5]) && (ticTacToe[3] != '#')) {
		win = true;
	}
	if ((ticTacToe[6] == ticTacToe[7]) && (ticTacToe[7] == ticTacToe[8]) && (ticTacToe[6] != '#')) {
		win = true;
	}

	//these are the diag
	if ((ticTacToe[0] == ticTacToe[4]) && (ticTacToe[4] == ticTacToe[8]) && (ticTacToe[0] != '#')) {
		win = true;
	}
	if ((ticTacToe[2] == ticTacToe[4]) && (ticTacToe[4] == ticTacToe[6]) && (ticTacToe[2] != '#')) {
		win = true;
	}

	return win;
}

string inputChecker(string input, int min, int max) {
	//easy little input check
	for (int i = 0; i < input.length(); i++) {
		while (isdigit(input[i]) == false) {
			i = 0;
			cout << "Your input was invalid! Please try again: \n";
			cin >> input;
		}
	}
	while (!((stoi(input) < max) && (stoi(input) > min))) {
			cout << "Your input was invalid! Please try again: \n";
			cin >> input;
	}
	return input;
}