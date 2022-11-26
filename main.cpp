#include <bits/stdc++.h>
#include "Chaos.h"
#include "Order.h"

using namespace std;

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