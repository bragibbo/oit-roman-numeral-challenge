// RomanNumeralConverter.cpp
// Brayden Gibbons
// Start time: 8:45AM 12/27/2019
// End time: 11:49AM 12/27/2019
#include <iostream>
#include <string>
#include <map>
#include <vector>

using namespace std; // Just to make the coding easier due to it not being that large scale

void MenuOptions();
void ConvertToNumber();
void ConvertToRomanNumeral();
bool isPowerOfTen(int input);

int main() {
	cout << "Welcome to the Acme Archaeology Co. roman numeral converter." << endl;

	int menuChoice = 0;
	do {
		cout << endl;
		MenuOptions();
		cin >> menuChoice;
		if (!cin) {
			cout << "Bad value!!" << endl;
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			menuChoice = 0;
		}

		switch (menuChoice) {
		case 1:
			ConvertToRomanNumeral();
			break;
		case 2:
			ConvertToNumber();
			break;
		case 3:
			break;
		default:
			cout << "Please enter a valid selection!!!" << endl;
			break;
		}
	} while (menuChoice != 3);

	cout << "Quitting program....." << endl;
	return 0;
}

void MenuOptions() {
	cout << "Choose from the following options: " << endl;
	cout << "- \'1\' to convert to roman numerals" << endl;
	cout << "- \'2\' to convert to a number" << endl;
	cout << "- \'3\' to quit the program" << endl;
	cout << "Enter your selection: ";
}

void ConvertToNumber() {
	// Map to contain all the key-value pairs
	map<char, int> romanNumerals;
	map<char, int>::iterator itrA;
	map<char, int>::iterator itrB;
	romanNumerals.insert(pair<char, int>('I', 1));
	romanNumerals.insert(pair<char, int>('V', 5));
	romanNumerals.insert(pair<char, int>('X', 10));
	romanNumerals.insert(pair<char, int>('L', 50));
	romanNumerals.insert(pair<char, int>('C', 100));
	romanNumerals.insert(pair<char, int>('D', 500));
	romanNumerals.insert(pair<char, int>('M', 1000));

	string userInputString;
	cout << endl;
	cout << "Please enter the roman numeral to convert: ";
	cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	getline(cin, userInputString);

	bool validNumber = true;
	int finalNumber = 0;
	for (unsigned int i = 0; i < userInputString.size(); i++) {
		// Check to see if we need to account for AB pairs as per instructions
		if ((i + 1) < userInputString.size()) {
			itrA = romanNumerals.find(static_cast<char>(userInputString.at(i)));
			itrB = romanNumerals.find(static_cast<char>(userInputString.at(i + 1)));

			// Check if the input string is found in the map (ie valid roman numeral characters), then check if the values need to
			// be subtracted from each other as per the instructions/rules for roman numerals
			if (itrA == romanNumerals.end() || itrB == romanNumerals.end()) {
				cout << "Invalid input string: " << userInputString << endl;
				validNumber = false;
				break;
			}
			else if ((itrA->second < itrB->second)) {
				// Check if the subtracting value is a power of ten and if it satisfies the rules
				if (isPowerOfTen(itrA->second) && (itrA->second >= (itrB->second / 10))) {
					finalNumber += itrB->second - itrA->second;
					i++;
				}
				else {
					cout << "Invalid input string: " << userInputString << endl;
					validNumber = false;
					break;
				}
			}
			else {
				finalNumber += itrA->second;
			}
		}
		else { // Handles the case of no AB pairs to check for
			itrA = romanNumerals.find(static_cast<char>(userInputString.at(i)));
			if (itrA == romanNumerals.end()) {
				cout << "Invalid input string: " << userInputString << endl;
				validNumber = false;
				break;
			}
			else {
				finalNumber += itrA->second;
			}
		}
	}

	if (validNumber) {
		cout << "The converted number is: " << finalNumber << endl;
	}
}

void ConvertToRomanNumeral() {
	int userInputNumber;
	cout << endl;
	cout << "Please enter the number to convert: ";
	cin >> userInputNumber;
	
	vector<pair<int, string>> thousands = { {1000,"M"} };
	vector<pair<int, string>> hundreds = { {900,"CM"}, {500,"D"}, {400,"CD"}, {100,"C"} };
	vector<pair<int, string>> tens = { {90,"XC"}, {50,"L"}, {40,"XL"}, {10,"X"} };
	vector<pair<int, string>> ones = { {9,"IX"}, {5,"V"}, {4,"IV"}, {1,"I"} };

	cout << "Number in roman numerals: ";
	for (unsigned int i = 0; i < thousands.size(); i++) {
		while (userInputNumber >= thousands.at(i).first) { // Convert thousands place under assumption that the largest number is 3999
			userInputNumber -= thousands.at(i).first;
			cout << thousands.at(i).second;
		}
	}
	for (unsigned int i = 0; i < hundreds.size(); i++) {
		while (userInputNumber >= hundreds.at(i).first) { // Convert hundreds place
			userInputNumber -= hundreds.at(i).first;
			cout << hundreds.at(i).second;
		}
	}
	for (unsigned int i = 0; i < tens.size(); i++) {
		while (userInputNumber >= tens.at(i).first) { // Convert tens place
			userInputNumber -= tens.at(i).first;
			cout << tens.at(i).second;
		}
	}
	for (unsigned int i = 0; i < ones.size(); i++) {
		while (userInputNumber >= ones.at(i).first) { // Convert ones
			userInputNumber -= ones.at(i).first;
			cout << ones.at(i).second;
		}
	}
	cout << endl;
}

bool isPowerOfTen(int input) {
	while (input > 9 && input % 10 == 0) {
		input /= 10;
	}
	return input == 1;
}