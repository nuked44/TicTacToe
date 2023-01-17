#include<iostream>

bool mainRunning = true;
bool currentGameRunning = true;
bool currentPlayer = true;
char turns = 0;
char board[9] = {'1', '2', '3', '4', '5', '6', '7', '8', '9'};
char player1symbol = 'X';
char player2symbol = 'O';

bool checkInputInvalid(short input){
	return (board[input-1] == player1symbol) || (board[input-1] == player2symbol);
}

bool compare(char a, char b, char c){
  return a == b && b == c;
}

void drawBoard(char b[]){
  std::cout << "\e[1;1H\e[2J";
  std::cout << "+---+---+---+\n";
  std::cout << "| " << b[0] << " | " << b[1] << " | " << b[2] << " |\n";
  std::cout << "+---+---+---+\n";
  std::cout << "| " << b[3] << " | " << b[4] << " | " << b[5] << " |\n";
  std::cout << "+---+---+---+\n";
  std::cout << "| " << b[6] << " | " << b[7] << " | " << b[8] << " |\n";
  std::cout << "+---+---+---+\n";
  return;
}

void getInput(bool p){
  std::cout << "Input number 1-9 to place ";
  std::cout << (p?player1symbol:player2symbol) << std::endl;

  short input = std::cin.get();
  std::cin.ignore(256, '\n');
  input -= 48;
  if(input >= 1 && input <= 9 && (board[input-1] != player1symbol || board[input-1] != player2symbol)){
		if (checkInputInvalid(input)) {
			std::cout << input << " is already taken" << std::endl;
			getInput(p);
		}
		else {
			board[input - 1] = (p?player1symbol:player2symbol);
		}
  }
  else{
    std::cout << "Please input a number from 1 to 9" << std::endl;
  }
  return;
}

void checkWin(char b[]){
  if(compare(b[0], b[1], b[2]) || 
      compare(b[3], b[4], b[5]) ||
      compare(b[6], b[7], b[8]) ||
      compare(b[0], b[3], b[6]) ||
      compare(b[1], b[4], b[7]) ||
      compare(b[2], b[5], b[8]) ||
      compare(b[0], b[4], b[8]) ||
      compare(b[2], b[4], b[6]) ){
    std::cout << (currentPlayer?player1symbol:player2symbol) << " WON" << std::endl;
    currentGameRunning = false;
  }
  return;
}

int main(){
	while(mainRunning){
    while(currentGameRunning){
      drawBoard(board);
      getInput(currentPlayer);
      checkWin(board);
      currentPlayer = !currentPlayer;
			turns++;
			if (turns >= 9) {
				std::cout << "Draw" << std::endl;
				currentGameRunning = false;
			}
    }
    std::cout << "Do you want to play again? [y/N]" << std::endl;
    char tempInput = std::cin.get();
    if(!(tolower(tempInput) == 'y')) {
      mainRunning = false;
    }
		else {
			currentGameRunning = true;
			turns = 0;
			for (int i = 0; i < 9; i++) {
				board[i] = i+47;
			}
		}
  }
  return 0;
}
