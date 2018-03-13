#pragma once
#include <vector>;

using namespace std;

class KeyGenerator {
	public:
		KeyGenerator();
		string generateKey();
		void updateKeypad();

	private:
		vector<vector<int>> keypad;
		vector<int> shiftKey;
};