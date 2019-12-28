/* Minimax algorithm using alpha-beta pruning technique (optimization vertion)
Reference from https://www.geeksforgeeks.org/minimax-algorithm-in-game-theory-set-4-alpha-beta-pruning/
*/
#include<bits/stdc++.h> 
using namespace std; 
  
struct Move{ 
    int row, col; 
};

char computer = 'X', human = 'O'; 

/* evaluate() function return a value (or score) based on who is winning
b[3][3] is the Tic-Tac-Toe board */
int evaluate(char b[3][3]){
    // Checking for Rows for X or O victory. 
    for (int row = 0; row < 3; row++){ 
        if (b[row][0] == b[row][1] && b[row][1] == b[row][2]){ 
            if (b[row][0] == computer) 
                return 10;
            else 
				if (b[row][0] == human) 
                	return -10; 
        }
    }
  
    // Checking for Columns for X or O victory. 
    for (int col = 0; col < 3; col++){ 
        if (b[0][col] == b[1][col] && b[1][col] == b[2][col]){
            if(b[0][col] == computer) 
                return 10; 
            else 
				if (b[0][col] == human) 
                	return -10; 
        }
    }
    
    // Checking for Diagonals for X or O victory. 
    if (b[0][0] == b[1][1] && b[1][1] == b[2][2]){ 
        if (b[0][0] == computer) 
            return 10; 
        else 
			if (b[0][0] == human) 
            	return -10; 
    } 
  
    if (b[0][2] == b[1][1] && b[1][1] == b[2][0]){ 
        if (b[0][2] == computer) 
            return 10; 
        else 
			if (b[0][2] == human) 
            	return -10; 
    } 
  
    // Else if none of them have won then return 0 
    return 0; 
}

/* Function to return a list of move which is available to play in the board. */
vector<Move> getAvailableCells(char board[3][3]){
	vector<Move> availableCells;
	for(int i = 0; i < 3; i++)
		for(int j = 0; j < 3; j++)
			if(board[i][j] == '_'){
				Move move;
				move.row = i;
				move.col = j;
				availableCells.push_back(move);	
			}
	return availableCells;
}

const int MAX = 1000;
const int MIN = -1000;
  
/* This is the minimax function. It considers all the possible ways the game can go and returns 
the value of the board.
- b[3][3] is the current board
- depth is current depth of game tree
- isMax is true if current move is of maximizer, else false
- alpha is the best value that represent for the Maximizer
- beta is the best value that represent for the Minimizer
*/
int minimax(char board[3][3], int depth, bool isMax, int alpha, int beta){ 
    int score = evaluate(board); 
    // If Maximizer has won the game then subtract the depth value for his/her evaluated score  
    if (score == 10) 
        return score-depth; 
  
    // If Minimizer has won the game then add the depth value for his/her evaluated score 
    if (score == -10) 
        return score+depth; 
  
    // If there are no more moves and no winner then it is a tie 
    if (getAvailableCells(board).empty()) 
        return 0; 
  	
  	vector<Move> availableCells = getAvailableCells(board);
    // If this maximizer's move 
    if(isMax){
        int best = MIN; 
        // Traverse all available cells 
        for(int i = 0; i < availableCells.size(); i++){
        	Move move = availableCells[i];
            // Make the move 
            board[move.row][move.col] = computer; 
            // Call minimax recursively
            best = max(best, minimax(board, depth+1, !isMax, alpha, beta));
            alpha = max(alpha,best);
            // Undo the move 
            board[move.row][move.col] = '_';
            if(beta <= alpha)
            	break; // cut-off
        } 
        return best; 
    }
    // If this minimizer's move 
    else{ 
        int best = MAX;
        // Traverse all available cells 
        for(int i = 0; i < availableCells.size(); i++){
        	Move move = availableCells[i];
	        // Make the move 
	        board[move.row][move.col] = human; 
	        // Call minimax recursively
	        best = min(best, minimax(board, !isMax, depth+1, alpha, beta));
	        beta = min(beta,best);
	        // Undo the move
	        board[move.row][move.col] = '_';
	        if(beta <= alpha)
	        	break; // cut-off
        }
        return best; 
    }
}
  
// This will return the best possible move for computer 
Move findBestMove(char board[3][3]){
    int bestVal = -1000;
    Move bestMove;
    bestMove.row = -1;
    bestMove.col = -1;
	vector<Move> availableCells = getAvailableCells(board);
    /* Traverse all available cells, evaluate minimax function for all empty cells. 
	And return the cell with optimal value. */
    for(int i = 0; i < availableCells.size(); i++){
    	Move move = availableCells[i];
        // Make the move 
        board[move.row][move.col] = computer; 
        // compute evaluation function for this move. 
        int moveVal = minimax(board, 0, false, MIN, MAX);
        // Undo the move 
        board[move.row][move.col] = '_';
        // If the value of the current move is more than the best value, then update best
        if (moveVal > bestVal){ 
            bestMove.row = move.row; 
            bestMove.col = move.col; 
            bestVal = moveVal; 
        } 
    }
    // printf("The value of the best Move is : %d\n\n", bestVal); 
  
    return bestMove; 
}

void displayBoard(char board[3][3]){
	cout << endl << endl << endl << endl << endl << endl;
	cout << "\t\t\t\t\t\t\t+-----------------+";
	for(int i = 0; i < 3; i++){
		cout << endl << "\t\t\t\t\t\t\t|";
		for(int j = 0; j < 3; j++){
			cout << setw(3) << board[i][j] << setw(3) << " |";
		}
	}
	cout << endl << "\t\t\t\t\t\t\t+-----------------+" << endl;
}

/* Function to return true if player win the game, otherwise return false. */
bool hasPlayerWon(char board[3][3], char player){
	// check two diagonals
	if((board[0][0] == board[1][1] && board[0][0] == board[2][2] && board[0][0] == player) ||
		(board[0][2] == board[1][1] && board[0][2] == board[2][0] && board[0][2] == player))
		return true;
	
	// check horizontal and vertical
	for(int i = 0; i < 3; i++)
		if((board[i][0] == board[i][1] && board[i][0] == board[i][2] && board[i][0] == player) ||
			(board[0][i] == board[1][i] && board[0][i] == board[2][i] && board[0][i] == player))
			return true;
	return false;
}

bool isGameOver(char board[3][3]){
	return hasPlayerWon(board,computer) || hasPlayerWon(board,human) || getAvailableCells(board).empty();
}

/* Function to return a random number */
int randomNumber(){
	srand(time(0));
	int number = rand()%3;
	return number;
}

/* Check a cell is occupied or not */
bool isOccupiedCell(char board[3][3], Move move){
	return (board[move.row][move.col] == computer || board[move.row][move.col] == human);
}

bool isDraw(char board[3][3]){
	for(int i = 0; i < 3; i++)
		if(board[i][0] == '_' || board[i][1] == '_' || board[i][2] == '_')
			return false;
		return true;
}

void getHumanMove(char board[3][3]){
	bool fail = false;
	while(true){
		cout << "\t\t\t\t\t\t\t  Your move: ";
		Move userMove;
		cin >> userMove.row >> userMove.col;
		
		if(isOccupiedCell(board,userMove)){
			cout << "\t\t\t\t\t\t   This cell is already filled!" << endl;
		}
		else{
			board[userMove.row][userMove.col] = human;
			break;
		}
	}
}

void play(char board[3][3]){
	displayBoard(board);
	cout << "\t\t\t\t\t\tChoose your turn by press 1 or 2\n\t\t\t\t\t\t  1. Computer (X)  2. Player (O)" << endl;
	int turn;
	cin >> turn;
	system("cls");
	displayBoard(board);
	bool exit = false;
	
	if(turn == 1){
		Move move;
		move.row = randomNumber();
		move.col = randomNumber();
		// make the move
		board[move.row][move.col] = computer;
		system("cls");
		displayBoard(board);
	}
	
	while(!isGameOver(board)){
		getHumanMove(board);
		
		if(hasPlayerWon(board, human)){
			system("cls");
			displayBoard(board);
			cout << "\t\t\t\t\t\t\t  You win!!!" << endl;
			break;
		}
		
		Move computerMove = findBestMove(board);
		board[computerMove.row][computerMove.col] = computer;
		
		if(hasPlayerWon(board,computer)){
			system("cls");
			displayBoard(board);
			cout << "\t\t\t\t\t\t\t  Computer win!!!" << endl;
			break;
		}
		system("cls");
		displayBoard(board);
		if(isDraw(board)){
			cout << "\t\t\t\t\t\t\t  Draw!!!";
		}
	}
}

int main(){
	char board[3][3] = {{ '_', '_', '_' },
						{ '_', '_', '_' },
						{ '_', '_', '_' }};
	play(board);
    return 0; 
} 
