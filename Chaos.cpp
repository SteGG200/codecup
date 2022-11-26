#include <bits/stdc++.h>
#include "Constant.h"
#include "Chaos.h"

using namespace std;

vector<int> usedChaos(7, 7);

// int randomChip(){
// 	int start = 1;
// 	int range = 7;
// 	int random = start + (rand() % range);
// 	while(usedChaos[random - 1] <= 0) int random = start + (rand() % range);
// 	return random;
// }

int predictMore(const vector<vector<char>> &board){
	vector<pair<int, int>> chips;
	for(int i = 0; i < 7; i++){
		for(int j = 0; j < 7; j++){
			if(board[i][j] != '0') chips.push_back(make_pair(i, j));
		}
	}
	for(int i = 0; i < board.size(); i++){
		for(int j = i + 1; j < board.size(); j++){
			int x1 = chips[i].first;
			int y1 = chips[i].second;
			int x2 = chips[i].first;
			int y2 = chips[i].second;
			// int x3 = x1;
			// int y3 = y2;
			// int x4 = x2;
			// int y4 = y1;
			if(board[x1][y1] == board[x2][y2]){
				int point = 0;
				if(abs(x1 - x2) < 3){
					bool isBlocked = false;
					for(int k = min(y1, y2); k <= max(y1, y2); k++){
						if(x1 == x2 && k == max(y1, y2)) break;
						if(board[x1][k] != '0'){
							isBlocked = true;
							break;
						}
					}
					if(!isBlocked){
						if(x1 == x2 || abs(x1 - x2) == 2) point = 3;
						else point = 2;
					}
					isBlocked = false;
					for(int k = max(y1, y2); k >= min(y1, y2); k--){
						if(x1 == x2 && k == min(y1, y2)) break;
						if(board[x2][k] != '0'){
							isBlocked = true;
							break;
						}
					}
					if(!isBlocked){
						if(x1 == x2 || abs(x1 - x2) == 2) point = max(3, point);
						else point = max(point, 2);
					}
				}
				if(abs(y1 - y2) < 3){
					bool isBlocked = false;
					for(int k = min(x1, x2); k <= max(x1, x2); k++){
						if(y1 == y2 && k == max(x1, x2)) break;
						if(board[k][y1] != '0'){
							isBlocked = true;
							break;
						}
					}
					if(!isBlocked){
						if(y1 == y2 || abs(y1 - y2) == 2) point = max(point, 3);
						else point = max(point, 2);
					}
					isBlocked = false;
					for(int k = max(x1, x2); k >= min(x1, x2); k--){
						if(y1 == y2 && k == min(x1, x2)) break;
						if(board[k][y2] != '0'){
							isBlocked = true;
							break;
						}
					}
					if(!isBlocked){
						if(y1 == y2 || abs(y1 - y2) == 2) point = max(3, point);
						else point = max(point, 2);
					}
				}
				return point;
			}
		}
	}
	return 0;
}

int evaluationChaos(const vector<vector<char>> &board){
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
	return -sum;
}


bool isBoardFull(const vector<vector<char>> &board){
	bool isFull = true;
	for(auto line : board){
		for(int cell : line){
			if(cell == '0'){
				isFull = false;
				break;
			}
		}
	}
	return isFull;
}

pair<string, int> minimaxChaos(vector<vector<char>> &board, int depth, int alpha, int beta, bool isMyTurn, char chip){
	if((depth == 0 && isMyTurn) || isBoardFull(board)){
		int curState = evaluationChaos(board);
		return make_pair("", curState);
	}
	if(isMyTurn){
		bool isrunning = true;
		pair<string, int> bestMove("Aa", -inf);
		for(int i = 0; i < 7; i++){
			for(int j = 0; j < 7; j++){
				if(board[i][j] == '0'){
					board[i][j] = chip;
					usedChaos[chip - '0' - 1]--;
					pair<string, int> move = minimaxChaos(board, depth - 1, alpha, beta, false, chip);
					move.first += char(i + 'A');
					move.first += char(j + 'a');
					board[i][j] = '0';
					usedChaos[chip - '0' - 1]++;
					bestMove = max(bestMove, move);
					alpha = max(alpha, bestMove.second);
					if(alpha >= beta){
						isrunning = false;
						break;
					}
				}
			}
			if(!isrunning) break;
		}
		return bestMove;
	}else{
		bool isrunning = true;
		int bestScore = inf;
		// char newChip = char(randomChip() + '0');
		for(int i = 0; i < 7; i++){
			for(int j = 0; j < 7; j++){
				if(board[i][j] != '0'){
					for(int x = i; x >= 0; x--){
						if(board[x][j] != '0' && x != i) break;
						swap(board[i][j], board[x][j]);
						int score = minimaxChaos(board, depth, alpha, beta, true, chip).second;
						swap(board[i][j], board[x][j]);
						bestScore = min(bestScore, score);
						beta = min(beta, bestScore);
						if(alpha >= beta){
							isrunning = false;
							break;
						}
					}
					if(isrunning){
						for(int x = i + 1; x < 7; x++){
							if(board[x][j] != '0') break;
							swap(board[i][j], board[x][j]);
							int score = minimaxChaos(board, depth, alpha, beta, true, chip).second;
							swap(board[i][j], board[x][j]);
							bestScore = min(bestScore, score);
							beta = min(beta, bestScore);
							if(alpha >= beta){
								isrunning = false;
								break;
							}
						}
					}
					if(isrunning){
						for(int y = j - 1; y >= 0; y--){
							if(board[i][y] != '0') break;
							swap(board[i][j], board[i][y]);
							int score = minimaxChaos(board, depth, alpha, beta, true, chip).second;
							swap(board[i][j], board[i][y]);
							bestScore = min(bestScore, score);
							beta = min(beta, bestScore);
							if(alpha >= beta){
								isrunning = false;
								break;
							}
						}
					}
					if(isrunning){
						for(int y = j + 1; y < 7; y++){
							if(board[i][y] != '0') break;
							swap(board[i][j], board[i][y]);
							int score = minimaxChaos(board, depth, alpha, beta, true, chip).second;
							swap(board[i][j], board[i][y]);
							bestScore = min(bestScore, score);
							beta = min(beta, bestScore);
							if(alpha >= beta){
								isrunning = false;
								break;
							}
						}
					}
				}
				if(!isrunning) break;
			}
			if(!isrunning) break;
		}
		return make_pair("", bestScore);
	}
}

void chaos(){
	vector<vector<char>> board(7, vector<char>(7, '0'));
	int round = 49;
	string opMove;
	// freopen("input.inp", "r", stdin);
	while(cin >> opMove){
		if(opMove == "Quit"){
			cout << "Quit" << endl;
			cout.flush();
			break;
		}
		char chip;
		if(opMove.length() > 1){
			int beXPos = opMove[0] - 'A';
			int beYPos = opMove[1] - 'a';
			int xPos = opMove[2] - 'A';
			int yPos = opMove[3] - 'a';
			swap(board[beXPos][beYPos], board[xPos][yPos]);
			cin >> chip;
		}else{
			chip = opMove[0];
		}
		string nextPos;
		if(round == 49){
			nextPos = "Ce";
		}else if(round > level){
			nextPos = minimaxChaos(board, level, -inf, inf, true, chip).first;
		}else{
			nextPos = minimaxChaos(board, round, -inf, inf, true, chip).first;
		}
		round--;
		usedChaos[chip - '0' - 1]--;
		int newX = nextPos[0] - 'A';
		int newY = nextPos[1] - 'a';
		board[newX][newY] = chip;
		cout << nextPos << endl;
		cout.flush();
	}
}
