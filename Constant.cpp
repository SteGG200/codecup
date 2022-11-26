#include <bits/stdc++.h>
#include "Constant.h"

using namespace std;

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

int predictMore(const vector<vector<char>> &board){
	vector<pair<int, int>> chips;
	for(int i = 0; i < 7; i++){
		for(int j = 0; j < 7; j++){
			if(board[i][j] != '0') chips.push_back(make_pair(i, j));
		}
	}
	int point = 0;
	for(int i = 0; i < chips.size(); i++){
		for(int j = i + 1; j < chips.size(); j++){
			int x1 = chips[i].first;
			int y1 = chips[i].second;
			int x2 = chips[j].first;
			int y2 = chips[j].second;
			// int x3 = x1;
			// int y3 = y2;
			// int x4 = x2;
			// int y4 = y1;
			if(board[x1][y1] == board[x2][y2]){
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
						if(x1 == x2 || abs(x1 - x2) == 2) point = max(point, 3);
						else point = max(point, 2);
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
			}
		}
	}
	return point;
}

pair<string, int> max(const pair<string, int> &A, const pair<string, int> &B){
	if(A.second < B.second) return B;
	return A;
}
