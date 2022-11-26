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

pair<string, int> max(const pair<string, int> &A, const pair<string, int> &B){
	if(A.second < B.second) return B;
	return A;
}
