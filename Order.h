#include <vector>
#include <string>
#ifndef ORDER_H
#define ORDER_H

using namespace std;

// vector<int> used(7, 7);

// int calPoint(char s[10], vector<vector<bool>> &check, int l = 0, int r = 6, bool inside = false);
int evaluationOrder(const vector<vector<char>> &board);

// pair<string, int> max(const pair<string, int> &A, const pair<string, int> &B);
// pair<string, int> minimax(vector<vector<char>> &board, int depth, int alpha, int beta, bool isMyTurn);

void order(string firstInput);

#endif // ORDER_H