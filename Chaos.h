#include <vector>
#ifndef CHAOS_H
#define CHAOS_H

using namespace std;

// vector<int> used(7, 7);

// int calPoint(char s[10], vector<vector<bool>> &check, int l = 0, int r = 6, bool inside = false);
int evaluationChaos(const vector<vector<char>> &board);
bool isBoardFull(const vector<vector<char>> &board);

// pair<string, int> max(pair<string, int> &A, pair<string, int> &B);
// pair<string, int> minimax(vector<vector<char>> &board, int depth, int alpha, int beta, bool isMyTurn, char chip);

void chaos();

#endif // CHAOS_H