#include "KeyGenerator.h";

//This constructor generates the keypad.
KeyGenerator::KeyGenerator() {
	for (int i = 0; i < 16; i++) {
		vector<int> row;
		for (int j = 0; i < 16; j++) {
			row.push_back(rand() % 16);
		}
		keypad.push_back(row);
	}

	for (int i = 0; i < 16; i++) {
		shiftKey.push_back(rand() % 16);
	}
}

//This method generates the ID's for the AI's and cores from the keypad.
string KeyGenerator::generateKey(string binary) {
	vector<string> half_O;
	vector<string> half_T;
	vector<string> totalIn;
	vector<string> total;

	//Splits the binary value in half.
	for (int i = 0; i < sizeof(binary); i++) {
		if (i < 4) {
			half_O.push_back(binary[i]);
		}
		else {
			half_T.push_bak(binary[i]);
		}
	}

	//Finds the value that needs to be flipped.
	string carry = "0";
	for (int i = 3; i > 0; i--) {
		if (i == 3) {
			if (half_O[i] == "0" && half_T[i + 4] == "0") {
				totalIn.push_back("0");
			}
			else if (half_O[i] == "0" && half_T[i + 4] == "1" || half_O[i] == "1" && half_T[i + 4] == "0") {
				totalIn.push_back("1");
			}
			else if (half_O[i] == "1" && half_T[i + 4] == "1") {
				totalIn.push_back("0");
				carry = "1";
			}
		}
		else {
			if (half_O[i] == "0" && half_T[i + 4] == "0") {
				if (carry == "0") {
					totalIn.push_back("0");
				}
				else {
					totalIn.push_back("1");
				}
			}
			else if (half_O[i] == "0" && half_T[i + 4] == "1" || half_O[i] == "1" && half_T[i + 4] == "0") {
				if (carry == "0") {
					totalIn.push_back("1");
				}
				else {
					totalIn.push_back("0");
					carry = "1";
				}
			}
			else if (half_O[i] == "1" && half_T[i + 4] == "1") {
				if (carry == "0") {
					totalIn.push_back("0");
					carry = "1";
				}
				else {
					totalIn.push_back("1");
					carry = "1";
				}
			}
		}
	}

	//Flip the binary value to find the key.
	int count = 0;
	for (int i = 3; i > 0; i--) {
		total[count] = totalIn[i];
		count += 1;
	}

	//This finds the integer value of the 4 bit binary to convert to hex.
	int value = 0;
	for (int i = 0; i < 4; i++) {
		if (total[i] == "1") {
			switch (i) {
			case 0:
				value += 8;

			case 1:
				value += 4;

			case 2:
				value += 2;

			case 3:
				value += 1;
			}
		}
	}

	//Converts the integer into a hex value.
	string search = _HEX(to_string(value));

	//This creates the key.
	int count = 0;
	string key = "";
	for (int i = 0; i < keypad.size(); i++) {
		vector<int> posFoundVert; //The Vertical positions that the search value has been found at.
		for (int j = 0; j < keypad[i].size(); j++) {
			if (search == keypad[i][j]) {
				posFoundVert.push_back(j);
			}
		}

		for (int j = 0; j < posFoundVert.size(); j++) {
			count += posFoundVert[j];
		}

		while (count >= 16) {
			count -= 16;
		}

		key += _HEX(to_string(value));
		search = _HEX(to_string(value));
	}

	return key;
}

//This method updates the keypad.
void KeyGenerator::updateKeypad() {
	for (int i = 0; i < keypad.size(); i++) {
		for (int j = 0; j < keypad.size(); j++) {
			keypad[i] += shiftKey[j];

			while (keypad[i] >= 16) {
				keypad[i] -= 16;
			}
		}
	}
}