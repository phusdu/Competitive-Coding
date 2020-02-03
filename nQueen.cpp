#include<bits/stdc++.h>
using namespace std;

int board[11][11];

bool isPossible(int n, int row, int col){

	//checking if coloumn crosses
	for(int i = row-1; i >= 0; i--){
		if(board[i][col] == 1){
			return false;
		}
	}

	//checking upper left diagonal
	for(int i = row-1, j = col-1; i >= 0 && j>= 0; i--, j--){
		if(board[i][j] == 1){
			return false;
		}
	}

	//checking upper right diagonal
	for(int i = row-1, j = col+1; i >= 0 && j < n; i--, j++){
		if(board[i][j] == 1){
			return false;
		}
	}

	return true;
}

void nQueenHelper(int n, int row){

	if(row == n){
		//we have reached a solution
		//print the board
		//return;
		for(int i = 0; i < n; i++){
			for(int j = 0; j < n; j++){
				cout << board[i][j] << " " ;
			}
		}
		cout << endl;
		return;
	}

	for(int i = 0; i < n; i++){

		if(isPossible(n, row, i)){
			board[row][i] = 1;
			nQueenHelper(n, row+1);
			board[row][i] = 0;
		}
	}
}

void placeNQueen(int n){

	for(int i = 0; i < n; i++){
		for(int j = 0; j < n; j++){
			board[i][j] = 0;
		}
	}

	nQueenHelper(n, 0);
}
int main(){

	placeNQueen(4);
	return 0;
}