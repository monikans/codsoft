#include <iostream>
#include <vector>

char board[3][3]; 
char currentPlayer; 
void initializeBoard() {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            board[i][j] = ' ';
        }
    }
}
void displayBoard() {
    std::cout << "\nCurrent Board:\n";
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            std::cout << board[i][j];
            if (j < 2) std::cout << " | ";
        }
        std::cout << std::endl;
        if (i < 2) std::cout << "---------\n";
    }
    std::cout << std::endl;
}
bool checkWin() {
   
    for (int i = 0; i < 3; i++) {
        if ((board[i][0] == currentPlayer && board[i][1] == currentPlayer && board[i][2] == currentPlayer) || 
            (board[0][i] == currentPlayer && board[1][i] == currentPlayer && board[2][i] == currentPlayer)) {
            return true;
        }
    }
    if ((board[0][0] == currentPlayer && board[1][1] == currentPlayer && board[2][2] == currentPlayer) ||
        (board[0][2] == currentPlayer && board[1][1] == currentPlayer && board[2][0] == currentPlayer)) {
        return true;
    }
    return false;
}
bool checkDraw() {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[i][j] == ' ') {
                return false; 
            }
        }
    }
    return true; 
}
void switchPlayer() {
    currentPlayer = (currentPlayer == 'X') ? 'O' : 'X';
}
bool makeMove() {
    int row, col;
    std::cout << "Player " << currentPlayer << ", enter your move (row and column): ";
    std::cin >> row >> col;

    if (row < 1 || row > 3 || col < 1 || col > 3 || board[row - 1][col - 1] != ' ') {
        std::cout << "Invalid move. Try again.\n";
        return false; 
    }

    board[row - 1][col - 1] = currentPlayer; 
    return true; 
}

int main() {
    char playAgain;

    do {
        initializeBoard();
        currentPlayer = 'X'; 

        while (true) {
            displayBoard();

            while (!makeMove()) {
                
            }
            if (checkWin()) {
                displayBoard();
                std::cout << "Player " << currentPlayer << " wins!\n";
                break;
            }
            if (checkDraw()) {
                displayBoard();
                std::cout << "It's a draw!\n";
                break;
            }
            switchPlayer();
        }
        std::cout << "Do you want to play again? (Y/N): ";
        std::cin >> playAgain;

    } while (playAgain == 'Y' || playAgain == 'y');

    std::cout << "Thank you for playing!\n";
    return 0;
}

// output

/* 
Current Board:
  |   |  
---------
  |   |  
---------
  |   |  

Player X, enter your move (row and column): 1 2 1

Current Board:
X |   |  
---------
  |   |  
---------
  |   |  

Player O, enter your move (row and column): 1 2

Current Board:
X | O |  
---------
  |   |  
---------
  |   |  

Player X, enter your move (row and column): 2 2

Current Board:
X | O |  
---------
  | X |  
---------
  |   |  

Player O, enter your move (row and column): 3 3

Current Board:
X | O |  
---------
  | X |  
---------
  |   | O

Player X, enter your move (row and column): 2 1

Current Board:
X | O |  
---------
X | X |  
---------
  |   | O

Player O, enter your move (row and column): 2 3

Current Board:
X | O |  
---------
X | X | O
---------
  |   | O

Player X, enter your move (row and column): 1 2
Invalid move. Try again.
Player X, enter your move (row and column): 1 3

Current Board:
X | O | X
---------
X | X | O
---------
  |   | O

Player O, enter your move (row and column): 3 2

Current Board:
X | O | X
---------
X | X | O
---------
  | O | O

Player X, enter your move (row and column): 3 1

Current Board:
X | O | X
---------
X | X | O
---------
X | O | O

Player X wins!
Do you want to play again? (Y/N): N
Thank you for playing!
*/