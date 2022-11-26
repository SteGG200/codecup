#include <bits/stdc++.h>

using namespace std;

const int inf = 1e9 + 7;
const int level = 1;

vector<int> usedOrder(7, 7);
vector<int> usedChaos(7, 7);

int calPoint(char s[10], vector<vector<bool>> &check, int l = 0, int r = 6, bool inside = false){
	if(check[l][r]) return 0;
	if(l == r){
		if(inside) return 1;
		else return 0;
	}else if(l > r) return 0;
	check[l][r] = true;
	if(l == r - 1 && s[l] == s[r] && s[l] != '0' && s[r] != '0') {
		check[l][r] = true;
		return 2;
	}
	if(s[l] != s[r] || s[l] == '0' || s[r] == '0'){
		if(!inside){
			int temp2 = calPoint(s, check, l, r - 1);
			int temp1 = calPoint(s, check, l + 1, r);
			return temp2 + temp1;
		}
		else return 0;
	}
	int temp  = calPoint(s, check, l + 1, r - 1, true);
	int temp1 = calPoint(s, check, l + 1, r);
	int temp2 = calPoint(s, check, l, r - 1);
	if(temp == 0) return temp1 + temp2;
	if(temp == 1) return (r - l + 1) + temp1 + temp2;
	return (r - l + 1) + temp + temp1 + temp2;
}

pair<string, int> max(const pair<string, int> &A, const pair<string, int> &B){
	if(A.second < B.second) return B;
	return A;
}

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

int main(){
	string input;
	cin >> input;
	if(input == "Start"){
		chaos();
	}else{
		order(input);
	}

	return 0;
}