#include <bits/stdc++.h>
#include "Constant.h"
#include "Order.h"

using namespace std;

vector<int> usedOrder(7, 7);

int evaluationOrder(const vector<vector<char>> &board){
	int sum = 0;
	for(int i = 0; i < 7; i++){
		vector<vector<bool>> check(7, vector<bool>(7, false));
		char s[10];
		for(int j = 0; j < 7; j++) s[j] = board[i][j];
		sum += calPoint(s, check, 0, 6, false);
	}
	for(int j = 0; j < 7; j++){
		vector<vector<bool>> check(7, vector<bool>(7, false));
		char s[10];
		for(int i = 0; i < 7; i++) s[i] = board[i][j];
		sum += calPoint(s, check, 0, 6, false);
	}
	sum += predictMore(board);
	return sum;
}


pair<string, int> minimaxOrder(vector<vector<char>> &board, int depth, int alpha, int beta, bool isMyTurn){
	if(depth == 0 && isMyTurn){
		int curState = evaluationOrder(board);
		string move = "Aa";
		// printf("%d\n", curState);
		return make_pair(move, curState);
	}
	if(isMyTurn){
		bool running = true;
		string start = "Aa";
		pair<string, int> bestMove(start, -inf);
		for(int i = 0; i < 7; i++){
			for(int j = 0; j < 7; j++){
				if(board[i][j] != '0'){
					for(int x = i; x >= 0; x--){
						if(board[x][j] != '0' && x != i){
							break;
						}
						swap(board[i][j], board[x][j]);
						pair<string, int> move = minimaxOrder(board, depth, alpha, beta, false);
						move.first += char(i + 'A');
						move.first += char(j + 'a');
						move.first += char(x + 'A');
						move.first += char(j + 'a');
						swap(board[i][j], board[x][j]);
						bestMove = max(bestMove, move);
						alpha = max(alpha, bestMove.second);
						if(alpha >= beta) {
							running = false;
							break;
						}
					}
					if(running){
						for(int x = i + 1; x < 7; x++){
							if(board[x][j] != '0'){
								break;
							}
							swap(board[i][j], board[x][j]);
							pair<string, int> move = minimaxOrder(board, depth, alpha, beta, false);
							move.first += char(i + 'A');
                            move.first += char(j + 'a');
                            move.first += char(x + 'A');
                            move.first += char(j + 'a');
							swap(board[i][j], board[x][j]);
							bestMove = max(bestMove, move);
							alpha = max(alpha, bestMove.second);
							if(alpha >= beta) {
								running = false;
								break;
							}
						}
					}
					if(running)
						for(int y = j - 1; y >= 0; y--){
							if(board[i][y] != '0'){
								break;
							}
							swap(board[i][j], board[i][y]);
							pair<string, int> move = minimaxOrder(board, depth, alpha, beta, false);
							move.first += char(i + 'A');
							move.first += char(j + 'a');
							move.first += char(i + 'A');
							move.first += char(y + 'a');
							swap(board[i][j], board[i][y]);
							bestMove = max(bestMove, move);
							alpha = max(alpha, bestMove.second);
							if(alpha >= beta){
								running = false;
								break;
							}
						}
					if(running)
						for(int y = j + 1; y < 7; y++){
							if(board[i][y] != '0'){
								break;
							}
							swap(board[i][j], board[i][y]);
							pair<string, int> move = minimaxOrder(board, depth, alpha, beta, false);
							move.first += char(i + 'A');
							move.first += char(j + 'a');
							move.first += char(i + 'A');
							move.first += char(y + 'a');
							swap(board[i][j], board[i][y]);
							bestMove = max(bestMove, move);
							alpha = max(alpha, bestMove.second);
							if(alpha >= beta){
								running = false;
								break;
							}
						}
				}
				if(!running) break;
			}
			if(!running) break;
		}
		return bestMove;
	}else{
		bool running = true;
		int bestScore = inf;
		for(int chip = 1; chip <= 7; chip++){
			if(usedOrder[chip - 1] > 0){
				for(int i = 0; i < 7; i++){
					for(int j = 0; j < 7; j++){
						if(board[i][j] == '0'){
							board[i][j] = char(chip + '0');
							usedOrder[chip - 1]--;
							int score = minimaxOrder(board, depth - 1, alpha, beta, true).second;
							usedOrder[chip - 1]++;
							bestScore = min(bestScore, score);
							beta = min(beta, bestScore);
							board[i][j] = '0';
							if(alpha >= beta){
								running = false;
								break;
							}
						}
					}
					if(!running) break;
				}
			}
			if(!running) break;
		}
		return make_pair("", bestScore);
	}
}

void order(string firstInput){
	vector<vector<char>> board(7, vector<char>(7, '0'));
	int round = 49;
	string opMove;
	// freopen("input.inp", "r", stdin);
	while(true){
        if(round == 49) opMove = firstInput;
		else cin >> opMove;
		//cin.ignore();
		char opIndex = opMove[0];
		usedOrder[opIndex - '0' - 1]--;
		int x = opMove[1] - 'A';
		int y = opMove[2] - 'a';
		board[x][y] = opIndex;
		bool isFull = true;
		for(auto line : board){
			for(char c : line){
				if(c == '0'){
					isFull = false;
					break;
				}
			}
			if(!isFull) break;
		}
		if(isFull){
			cout << "Quit" << endl;
			cout.flush();
			break;
		}
		round--;
		string nextPos;
		if(round > level){
			nextPos = minimaxOrder(board, level, -inf, inf, true).first;
		}else{
			nextPos = minimaxOrder(board, round, -inf, inf, true).first;
		}
		int beXPos = nextPos[0] - 'A';
		int beYPos = nextPos[1] - 'a';
		int xPos = nextPos[2] - 'A';
		int yPos = nextPos[3] - 'a';
		swap(board[xPos][yPos], board[beXPos][beYPos]);
		cout << nextPos << endl;
		cout.flush();
	}
}
