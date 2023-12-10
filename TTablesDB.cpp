//Subject: COSC 2425
//Program Set 1
//Sources: 
// "https://www.asciitable.com" 
// (ASCII Value Comparisons for user variables and operators);

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

vector<char> userVariableArray; //Vector array for user variables (no duplicates included).
vector<char> userExpressionArray; //Vector array for raw copy of user expression.
vector<char> parenthesizedUserExpressionArray; //Simplified-with-parentheses version of user expression.
vector<int> expressionBreakdownLengths; //Lengths of individual operations.
//Binary patterns, operator ASCII codes, and important integer values.
string twoVariableBinaryPatterns[4] = { 
	 "00", "01", "10", "11"
};
string threeVariableBinaryPatterns[8] = { 
	"000", "001", "010", "011", "100", "101", "110", "111"
};
string fourVariableBinaryPatterns[16] = { 
	"0000", "0001", "0010", "0011", "0100", "0101", "0110", "0111", "1000", "1001", "1010", "1011", "1100", "1101", "1110", "1111"
};
int operatorASCIICodes[7] = { 32, 33, 40, 41, 42, 43, 94 };
int booleanExpressionLength = 0;
int currentBreakdown = 0;
//Crucial function declarations.
void parenthesesSort();
void truthTableFirstRow(string userBooleanExpression);
void truthTableBinaryGeneration();
void expressionDissector();
void expressionSort(string userBooleanExpression);
void expressionResult(string currentPattern);
bool repetitionCheck(char currentVariable);
bool expressionValidator(string userBooleanExpression);

int main() 
{
	string userRerunChoice = "";
	while (userRerunChoice != "N" && userRerunChoice != "n") { //Loops main functions until user rerun response equals 'N' or 'n'.
		userRerunChoice = "";
		string userBooleanExpressionInput;
		cout << "Enter the Boolean expression: "; //Prompting user input for boolean expression.
		getline(cin, userBooleanExpressionInput);
		cout << "\n";
		if (expressionValidator(userBooleanExpressionInput)) { //Determining if expression contains any incorrect operators, or inappropriate amount of different variables.
			truthTableFirstRow(userBooleanExpressionInput);
			cout << "\n";
			truthTableBinaryGeneration();
		}
		else if (!expressionValidator(userBooleanExpressionInput)) { //
			cout << "Invalid expression! Incorrect operators and/or variable count.\n";
		};
		while (userRerunChoice != "Y" && userRerunChoice != "y" && userRerunChoice != "N" && userRerunChoice != "n") { //Prompting user for program rerun and determining if input is valid.
			cout << "\n" << "Run again (Y/N): ";
			cin >> userRerunChoice;
			cout << "\n";
		}
		//Resetting getline and clearing important variables for next run.
		cin.ignore(10, '\n');
		userVariableArray.clear();
		userExpressionArray.clear();
		expressionBreakdownLengths.clear();
		booleanExpressionLength = 0;
	}
	return 0;
};

// ** FUNCTION DEFINITIONS BEYOND THIS POINT **

void parenthesesSort() { //Adds parentheses to individual operations in order of their priority, essentially simplifying the expression while being inclusive of operator precedence.
	bool parenthesesCheck = false;
	bool parenthesesCheck2 = false;
	parenthesizedUserExpressionArray = userExpressionArray;
	for (int i = 0; i < parenthesizedUserExpressionArray.size(); i++) { //Searching for AND operator '*', as well as skipping already existing parentheses.
		parenthesesCheck = false;
		parenthesesCheck2 = false;
		int currentOperatorIndex = 0;
		if (parenthesizedUserExpressionArray[i] == '(') { //Skipping already existing parentheses by setting loop index equal to position directly at the end of the currently tracked parentheses.
			for (int j = i + 1; j < parenthesizedUserExpressionArray.size(); j++) {
				if (parenthesizedUserExpressionArray[j] == ')') {
					i = j + 1;
					j = 9999;
				}
			}
		}
		else if (parenthesizedUserExpressionArray[i] == '*') {
			currentOperatorIndex = i;
			if (i - 1 == 0 && parenthesizedUserExpressionArray[0] >= 65 && parenthesizedUserExpressionArray[0] <= 90) { //Determining if variable on left side of operator is located at the beginning of vector, and prepends parentheses.
				parenthesizedUserExpressionArray.insert(parenthesizedUserExpressionArray.begin(), '(');
			};
			for (int j = i - 1; j > 0; j--) { //Determines if parentheses encountered; transversing vector to the left.
				if (parenthesizedUserExpressionArray[j] == ')') {
					parenthesesCheck = true;
					j = 0;
				}
				else if (parenthesizedUserExpressionArray[j] >= 65 && parenthesizedUserExpressionArray[j] <= 90) {
					j = 0;
				};
			};
			for (int j = currentOperatorIndex + 1; j < parenthesizedUserExpressionArray.size(); j++) { //Determines if parentheses encountered; transversing vector to the right.
				if (parenthesizedUserExpressionArray[j] == '(') {
					parenthesesCheck2 = true;
					j = 9999;
				}
				else if (parenthesizedUserExpressionArray[j] >= 65 && parenthesizedUserExpressionArray[j] <= 90) {
					j = 9999;
				};
			};
			if (parenthesesCheck != true && parenthesesCheck2 != true) { //Verifying if there were no parentheses encountered, and adding parentheses to operation.
				for (int j = i + 1; j < parenthesizedUserExpressionArray.size(); j++) {
					if (parenthesizedUserExpressionArray[j] >= 65 && parenthesizedUserExpressionArray[j] <= 90) {
						parenthesizedUserExpressionArray.insert(parenthesizedUserExpressionArray.begin() + j + 1, ')');
						i = j + 2;
						j = 9999;
					}
					else if (parenthesizedUserExpressionArray[j] == '(') {
						j = 9999;
					};
				};
				for (int j = currentOperatorIndex - 1; j > 0; j--) {
					if (j - 1 == 0) {
						parenthesizedUserExpressionArray.insert(parenthesizedUserExpressionArray.begin(), '(');
						j = 0;
					}
					else if (parenthesizedUserExpressionArray[j] >= 65 && parenthesizedUserExpressionArray[j] <= 90 && parenthesizedUserExpressionArray[j - 1] == '!') {
						parenthesizedUserExpressionArray.insert(parenthesizedUserExpressionArray.begin() + j - 1, '(');
						j = 0;
					}
					else if (parenthesizedUserExpressionArray[j] >= 65 && parenthesizedUserExpressionArray[j] <= 90 && parenthesizedUserExpressionArray[j - 1] != '!') {
						parenthesizedUserExpressionArray.insert(parenthesizedUserExpressionArray.begin() + j, '(');
						j = 0;
					}
					else if (parenthesizedUserExpressionArray[j] == ')') {
						j = 0;
					};
				};
			};
		};
	};
	for (int i = 0; i < parenthesizedUserExpressionArray.size(); i++) { //Repeating same process as above, except in respect to OR operator '+'.
		parenthesesCheck = false;
		parenthesesCheck2 = false;
		int currentOperatorIndex = 0;
		if (parenthesizedUserExpressionArray[i] == '(') {
			for (int j = i + 1; j < parenthesizedUserExpressionArray.size(); j++) {
				if (parenthesizedUserExpressionArray[j] == ')') {
					i = j + 1;
					j = 9999;
				};
			};
		}
		else if (parenthesizedUserExpressionArray[i] == '+') {
			currentOperatorIndex = i;
			for (int j = i - 1; j > 0; j--) {
				if (parenthesizedUserExpressionArray[j] == ')') {
					parenthesesCheck = true;
					j = 0;
				}
				else if (parenthesizedUserExpressionArray[j] >= 65 && parenthesizedUserExpressionArray[j] <= 90) {
					j = 0;
				};
			};
			for (int j = currentOperatorIndex + 1; j < parenthesizedUserExpressionArray.size(); j++) {
				if (parenthesizedUserExpressionArray[j] == '(') {
					parenthesesCheck2 = true;
					j = 9999;
				}
				else if (parenthesizedUserExpressionArray[j] >= 65 && parenthesizedUserExpressionArray[j] <= 90) {
					j = 9999;
				};
			};
			if (parenthesesCheck != true && parenthesesCheck2 != true) {
				for (int j = i + 1; j < parenthesizedUserExpressionArray.size(); j++) {
					if (parenthesizedUserExpressionArray[j] >= 65 && parenthesizedUserExpressionArray[j] <= 90) {
						parenthesizedUserExpressionArray.insert(parenthesizedUserExpressionArray.begin() + j + 1, ')');
						i = j + 2;
						j = 9999;
					}
					else if (parenthesizedUserExpressionArray[j] == '(') {
						j = 9999;
					};
				};
				for (int j = currentOperatorIndex - 1; j > 0; j--) {
					if (j - 1 == 0) {
						parenthesizedUserExpressionArray.insert(parenthesizedUserExpressionArray.begin(), '(');
						j = 0;
					}
					else if (parenthesizedUserExpressionArray[j] >= 65 && parenthesizedUserExpressionArray[j] <= 90 && parenthesizedUserExpressionArray[j - 1] == '!') {
						parenthesizedUserExpressionArray.insert(parenthesizedUserExpressionArray.begin() + j - 1, '(');
						j = 0;
					}
					else if (parenthesizedUserExpressionArray[j] >= 65 && parenthesizedUserExpressionArray[j] <= 90 && parenthesizedUserExpressionArray[j - 1] != '!') {
						parenthesizedUserExpressionArray.insert(parenthesizedUserExpressionArray.begin() + j, '(');
						j = 0;
					}
					else if (parenthesizedUserExpressionArray[j] == ')') {
						j = 0;
					};
				};
			};
		};
	};
	for (int i = 0; i < parenthesizedUserExpressionArray.size(); i++) { //Repeating same process as above, except in respect to XOR operator '^'.
		parenthesesCheck = false;
		parenthesesCheck2 = false;
		int currentOperatorIndex = 0;
		if (parenthesizedUserExpressionArray[i] == '(') {
			for (int j = i + 1; j < parenthesizedUserExpressionArray.size(); j++) {
				if (parenthesizedUserExpressionArray[j] == ')') {
					i = j + 1;
					j = 9999;
				};
			};
		}
		else if (parenthesizedUserExpressionArray[i] == '^') {
			currentOperatorIndex = i;
			for (int j = i - 1; j > 0; j--) {
				if (parenthesizedUserExpressionArray[j] == ')') {
					parenthesesCheck = true;
					j = 0;
				}
				else if (parenthesizedUserExpressionArray[j] >= 65 && parenthesizedUserExpressionArray[j] <= 90) {
					j = 0;
				};
			};
			for (int j = currentOperatorIndex + 1; j < parenthesizedUserExpressionArray.size(); j++) {
				if (parenthesizedUserExpressionArray[j] == '(') {
					parenthesesCheck2 = true;
					j = 9999;
				}
				else if (parenthesizedUserExpressionArray[j] >= 65 && parenthesizedUserExpressionArray[j] <= 90) {
					j = 9999;
				};
			};
			if (parenthesesCheck != true && parenthesesCheck2 != true) {
				for (int j = i + 1; j < parenthesizedUserExpressionArray.size(); j++) {
					if (parenthesizedUserExpressionArray[j] >= 65 && parenthesizedUserExpressionArray[j] <= 90) {
						parenthesizedUserExpressionArray.insert(parenthesizedUserExpressionArray.begin() + j + 1, ')');
						i = j + 2;
						j = 9999;
					}
					else if (parenthesizedUserExpressionArray[j] == '(') {
						j = 9999;
					};
				};
				for (int j = currentOperatorIndex - 1; j > 0; j--) {
					if (j - 1 == 0) {
						parenthesizedUserExpressionArray.insert(parenthesizedUserExpressionArray.begin(), '(');
						j = 0;
					}
					else if (parenthesizedUserExpressionArray[j] >= 65 && parenthesizedUserExpressionArray[j] <= 90 && parenthesizedUserExpressionArray[j - 1] == '!') {
						parenthesizedUserExpressionArray.insert(parenthesizedUserExpressionArray.begin() + j - 1, '(');
						j = 0;
					}
					else if (parenthesizedUserExpressionArray[j] >= 65 && parenthesizedUserExpressionArray[j] <= 90 && parenthesizedUserExpressionArray[j - 1] != '!') {
						parenthesizedUserExpressionArray.insert(parenthesizedUserExpressionArray.begin() + j, '(');
						j = 0;
					}
					else if (parenthesizedUserExpressionArray[j] == ')') {
						j = 0;
					};
				};
			};
		};
	};
};

void expressionDissector() { //Scans through expression and prints out operations in parentheses (which are also our individual operations, bracketed in order earlier).
	for (int i = 0; i < parenthesizedUserExpressionArray.size(); i++) {
		if (parenthesizedUserExpressionArray[i] == '(') {
			int endingBracketIndex = 0;
			int expressionBreakdownLength = 0;
			for (int j = i + 1; j < parenthesizedUserExpressionArray.size(); j++) {
				if (parenthesizedUserExpressionArray[j] == ')') {
					endingBracketIndex = j;
					j = 9999;
				}
			};
			for (int j = i + 1; j < endingBracketIndex; j++) {
				cout << parenthesizedUserExpressionArray[j];
				booleanExpressionLength += 1;
				expressionBreakdownLength += 1;
			};
			cout << " | ";
			booleanExpressionLength += 3;
			expressionBreakdownLengths.push_back(expressionBreakdownLength);
			i = endingBracketIndex + 1;
		};
	};
};

void truthTableFirstRow(string userBooleanExpression) { //Generates first row/top divider.
	parenthesesSort(); //Adding parentheses to operations, in order of precendence.
	for (int i = 0; i < userVariableArray.size(); i++) { //Printing user variables from userVariableArray.
		cout << " " << userVariableArray[i] << " ";
		booleanExpressionLength += 3;
	};
	cout << "| ";
	booleanExpressionLength += 2;
	expressionDissector(); //Printing individual operations of the expression.
	for (int i = 0; i < userExpressionArray.size(); i++) { //Printing original user expression.
		cout << userExpressionArray[i];
		booleanExpressionLength += 1;
	};
	cout << "\n ";
	for (int i = 0; i <= booleanExpressionLength - 1; i++) { //Generating size-appropriate "=" divider.
		cout << "=";
	};
};

void truthTableBinaryGeneration() { //Generates rows of results, including the final answer, for each case.
	if (userVariableArray.size() == 2) {
		for (int i = 0; i < 4; i++) {
			string currentPattern = twoVariableBinaryPatterns[i];
			cout << " " << currentPattern[0] << "  " << currentPattern[1] << " | ";
			expressionResult(currentPattern);
			cout << "\n";
		};
	}
	else if (userVariableArray.size() == 3) {
		for (int i = 0; i < 8; i++) {
			string currentPattern = threeVariableBinaryPatterns[i];
			cout << " " << currentPattern[0] << "  " << currentPattern[1] << "  " << currentPattern[2] << " | ";
			expressionResult(currentPattern);
			cout << "\n";
		};
	}
	else if (userVariableArray.size() == 4) {
		for (int i = 0; i < 16; i++) {
			string currentPattern = fourVariableBinaryPatterns[i];
			cout << " " << currentPattern[0] << "  " << currentPattern[1] << "  " << currentPattern[2] << "  " << currentPattern[3] << " | ";
			expressionResult(currentPattern);
			cout << "\n";
		};
	};
};

bool expressionValidator(string userBooleanExpression){ //Determines if expression contains invalid operators and/or variables.
	expressionSort(userBooleanExpression);
	for (int i = 0; i < userBooleanExpression.size(); i++) {
		if (find(begin(operatorASCIICodes), end(operatorASCIICodes), userBooleanExpression[i]) == end(operatorASCIICodes) &&
			!(userBooleanExpression[i] >= 65 && userBooleanExpression[i] <= 90) && !(userBooleanExpression[i] >= 97 && userBooleanExpression[i] <= 122) || userVariableArray.size() > 4 || userVariableArray.size() == 1) {
			return false;
		};
	};
	return true;
};

//Analyzing expression and passing to vector array (accounting for lower caps as well).
void expressionSort(string userBooleanExpression) {
	for (int i = 0; i < userBooleanExpression.size(); i++) {
		char userExpressionValue = userBooleanExpression.at(i);
		if (userExpressionValue >= 65 && userExpressionValue <= 90) {
			if (!repetitionCheck(userExpressionValue)) {
				userVariableArray.push_back(userExpressionValue);
			};
			userExpressionArray.push_back(userExpressionValue);
		}
		else if (userExpressionValue >= 97 && userExpressionValue <= 122) {
			if (!repetitionCheck(toupper(userExpressionValue))) {
				userVariableArray.push_back(toupper(userExpressionValue));
			};
			userExpressionArray.push_back(toupper(userExpressionValue));
		}
		else if (find(begin(operatorASCIICodes), end(operatorASCIICodes), userExpressionValue) != end(operatorASCIICodes)) {
			userExpressionArray.push_back(userExpressionValue);
		};
	};
};

bool repetitionCheck(char currentVariable) { //Determines duplicate variable status (embedded in expressionSort).
	if (count(userVariableArray.begin(), userVariableArray.end(), currentVariable) == 0) {
		return false;
	}
	else {
		return true;
	};
};

void expressionResult(string currentPattern) { //Performs all logical operations within any parentheses, and then operates on the simplified expression without parentheses, for every generated binary pattern. *Embedded in truthTableBinaryGeneration()*
		vector <char> tempUserExpressionArray = parenthesizedUserExpressionArray;
		if (currentPattern.size() == 2) { //Patterns for 2 variables.
			replace(tempUserExpressionArray.begin(), tempUserExpressionArray.end(), userVariableArray[0], currentPattern[0]);
			replace(tempUserExpressionArray.begin(), tempUserExpressionArray.end(), userVariableArray[1], currentPattern[1]);
		}
		else if (currentPattern.size() == 3) { //Patterns for 3 variables.
			replace(tempUserExpressionArray.begin(), tempUserExpressionArray.end(), userVariableArray[0], currentPattern[0]);
			replace(tempUserExpressionArray.begin(), tempUserExpressionArray.end(), userVariableArray[1], currentPattern[1]);
			replace(tempUserExpressionArray.begin(), tempUserExpressionArray.end(), userVariableArray[2], currentPattern[2]);
		}
		else if (currentPattern.size() == 4) { //Patterns for 4 variables.
			replace(tempUserExpressionArray.begin(), tempUserExpressionArray.end(), userVariableArray[0], currentPattern[0]);
			replace(tempUserExpressionArray.begin(), tempUserExpressionArray.end(), userVariableArray[1], currentPattern[1]);
			replace(tempUserExpressionArray.begin(), tempUserExpressionArray.end(), userVariableArray[2], currentPattern[2]);
			replace(tempUserExpressionArray.begin(), tempUserExpressionArray.end(), userVariableArray[3], currentPattern[3]);
		};
		//Erasing whitespace from expression vector for easier transversal.
		for (int i = 0; i < tempUserExpressionArray.size(); i++) {
			if (tempUserExpressionArray[i] == 32) {
				tempUserExpressionArray.erase(tempUserExpressionArray.begin() + i);
			}
		};
		//Solving all operations in parentheses, in order of precedence.
		for (int j = 0; j < tempUserExpressionArray.size(); j++) {
			char currentElement = tempUserExpressionArray[j];
			if (currentElement == '(') {
				currentBreakdown += 1;
				int endingBracketIndex = 0;
				for (int r = j + 1; r < tempUserExpressionArray.size(); r++) {
					if (tempUserExpressionArray[r] == ')') {
						endingBracketIndex = r;
						r = 9999;
					};
				};
				for (int r = j + 1; r < endingBracketIndex; r++) {
					char currentParenthesesElement = tempUserExpressionArray[r];
					if (currentParenthesesElement == '!') {
						if (tempUserExpressionArray[r + 1] == '1') {
							tempUserExpressionArray[r + 1] = '0';
							tempUserExpressionArray.erase(tempUserExpressionArray.begin() + r);
							r = j + 1;
							for (int l = j + 1; l < tempUserExpressionArray.size(); l++) {
								if (tempUserExpressionArray[l] == ')') {
									endingBracketIndex = l;
									l = 9999;
								};
							};
						}
						else if (tempUserExpressionArray[r + 1] == '0') {
							tempUserExpressionArray[r + 1] = '1';
							tempUserExpressionArray.erase(tempUserExpressionArray.begin() + r);
							r = j + 1;
							for (int l = j + 1; l < tempUserExpressionArray.size(); l++) {
								if (tempUserExpressionArray[l] == ')') {
									endingBracketIndex = l;
									l = 9999;
								};
							};
						};
					};
				};
				for (int r = j + 1; r < endingBracketIndex; r++) {
					char currentParenthesesElement = tempUserExpressionArray[r];
					if (currentParenthesesElement == '*') {
						if (tempUserExpressionArray[r - 1] == '1' && tempUserExpressionArray[r + 1] == '1') {
							tempUserExpressionArray[r] = '1';
							tempUserExpressionArray.erase(tempUserExpressionArray.begin() + r + 1);
							tempUserExpressionArray.erase(tempUserExpressionArray.begin() + r - 1);
							r = j + 1;
							for (int l = j + 1; l < tempUserExpressionArray.size(); l++) {
								if (tempUserExpressionArray[l] == ')') {
									endingBracketIndex = l;
									l = 9999;
								};
							};
						}
						else {
							tempUserExpressionArray[r] = '0';
							tempUserExpressionArray.erase(tempUserExpressionArray.begin() + r + 1);
							tempUserExpressionArray.erase(tempUserExpressionArray.begin() + r - 1);
							r = j + 1;
							for (int l = j + 1; l < tempUserExpressionArray.size(); l++) {
								if (tempUserExpressionArray[l] == ')') {
									endingBracketIndex = l;
									l = 9999;
								};
							};
						};
					};
				};
				for (int r = j + 1; r < endingBracketIndex; r++) {
					char currentParenthesesElement = tempUserExpressionArray[r];
					if (currentParenthesesElement == '+') {
						if (tempUserExpressionArray[r - 1] == '1' || tempUserExpressionArray[r + 1] == '1') {
							tempUserExpressionArray[r] = '1';
							tempUserExpressionArray.erase(tempUserExpressionArray.begin() + r + 1);
							tempUserExpressionArray.erase(tempUserExpressionArray.begin() + r - 1);
							r = j + 1;
							for (int l = j + 1; l < tempUserExpressionArray.size(); l++) {
								if (tempUserExpressionArray[l] == ')') {
									endingBracketIndex = l;
									l = 9999;
								};
							};
						}
						else {
							tempUserExpressionArray[r] = '0';
							tempUserExpressionArray.erase(tempUserExpressionArray.begin() + r + 1);
							tempUserExpressionArray.erase(tempUserExpressionArray.begin() + r - 1);
							r = j + 1;
							for (int l = j + 1; l < tempUserExpressionArray.size(); l++) {
								if (tempUserExpressionArray[l] == ')') {
									endingBracketIndex = l;
									l = 9999;
								}
							};
						};
					};
				};
				for (int r = j + 1; r < endingBracketIndex; r++) {
					char currentParenthesesElement = tempUserExpressionArray[r];
					if (currentParenthesesElement == '^') {
						if (tempUserExpressionArray[r - 1] == tempUserExpressionArray[r + 1]) {
							tempUserExpressionArray[r] = '0';
							tempUserExpressionArray.erase(tempUserExpressionArray.begin() + r + 1);
							tempUserExpressionArray.erase(tempUserExpressionArray.begin() + r - 1);
							r = j + 1;
							for (int l = j + 1; l < tempUserExpressionArray.size(); l++) {
								if (tempUserExpressionArray[l] == ')') {
									endingBracketIndex = l;
									l = 9999;
								};
							};
						}
						else if (tempUserExpressionArray[r - 1] != tempUserExpressionArray[r + 1]) {
							tempUserExpressionArray[r] = '1';
							tempUserExpressionArray.erase(tempUserExpressionArray.begin() + r + 1);
							tempUserExpressionArray.erase(tempUserExpressionArray.begin() + r - 1);
							r = j + 1;
							for (int l = j + 1; l < tempUserExpressionArray.size(); l++) {
								if (tempUserExpressionArray[l] == ')') {
									endingBracketIndex = l;
									l = 9999;
								};
							};
						};
					};
				};
				//Printing result of operation in parentheses.
				for (int r = 0; r < expressionBreakdownLengths[currentBreakdown - 1] / 2; r++) {
					cout << " ";
				};
				cout << tempUserExpressionArray[j + 1];
				for (int r = 0; r < expressionBreakdownLengths[currentBreakdown - 1] / 2; r++) {
					cout << " ";
					if (expressionBreakdownLengths[currentBreakdown - 1] % 2 == 0 && r == 0) {
						r += 1;
					};
				};
				cout << " | ";
			}
		};
		currentBreakdown = 0;
		//Clearing all parentheses from expression.
		for (int j = 0; j < tempUserExpressionArray.size(); j++) {
			if (tempUserExpressionArray[j] == '(') {
				tempUserExpressionArray.erase(tempUserExpressionArray.begin() + j + 2);
				tempUserExpressionArray.erase(tempUserExpressionArray.begin() + j);
				j = 0;
			};
		};
		//Performing final calculations on simplified expression.
		for (int j = 0; j < tempUserExpressionArray.size(); j++) { //Searching for NOT operator '!'.
			char currentElement = tempUserExpressionArray[j];
			if (currentElement == '!') {
				if (tempUserExpressionArray[j + 1] == '1') {
					tempUserExpressionArray[j + 1] = '0';
					tempUserExpressionArray.erase(tempUserExpressionArray.begin() + j);
					j = 0;
				}
				else if (tempUserExpressionArray[j + 1] == '0') {
					tempUserExpressionArray[j + 1] = '1';
					tempUserExpressionArray.erase(tempUserExpressionArray.begin() + j);
					j = 0;
				};
			};
		};
		for (int j = 0; j < tempUserExpressionArray.size(); j++) { //Searching for AND operator '*'.
			 int currentElement;
			 if (tempUserExpressionArray[j] == '*' && tempUserExpressionArray[j - 1] != ')' && tempUserExpressionArray[j + 1] != '(') {
				if (tempUserExpressionArray[j - 1] == '1' && tempUserExpressionArray[j + 1] == '1') {
					tempUserExpressionArray[j] = '1';
					tempUserExpressionArray.erase(tempUserExpressionArray.begin() + j + 1);
					tempUserExpressionArray.erase(tempUserExpressionArray.begin() + j - 1);
					currentElement = j - 1;
					j = 0;
				}
				else {
					tempUserExpressionArray[j] = '0';
					tempUserExpressionArray.erase(tempUserExpressionArray.begin() + j + 1);
					tempUserExpressionArray.erase(tempUserExpressionArray.begin() + j - 1);
					currentElement = j - 1;
					j = 0;
				};
			};
		};
		for (int j = 0; j < tempUserExpressionArray.size(); j++) { //Searching for OR operator '+'.
			char currentElement = tempUserExpressionArray[j];
			if (currentElement == '+') {
				if (tempUserExpressionArray[j - 1] == '1' || tempUserExpressionArray[j + 1] == '1') {
					tempUserExpressionArray[j] = '1';
					tempUserExpressionArray.erase(tempUserExpressionArray.begin() + j + 1);
					tempUserExpressionArray.erase(tempUserExpressionArray.begin() + j - 1);
					j = 0;
				}
				else {
					tempUserExpressionArray[j] = '0';
					tempUserExpressionArray.erase(tempUserExpressionArray.begin() + j + 1);
					tempUserExpressionArray.erase(tempUserExpressionArray.begin() + j - 1);
					j = 0;
				};
			};
		};
		for (int j = 0; j < tempUserExpressionArray.size(); j++) { //Searching for XOR operator '^'.
			char currentElement = tempUserExpressionArray[j];
			if (currentElement == '^') {
				if (tempUserExpressionArray[j - 1] == tempUserExpressionArray[j + 1]) {
					tempUserExpressionArray[j] = '0';
					tempUserExpressionArray.erase(tempUserExpressionArray.begin() + j + 1);
					tempUserExpressionArray.erase(tempUserExpressionArray.begin() + j - 1);
					j = 0;
				}
				else if (tempUserExpressionArray[j - 1] != tempUserExpressionArray[j + 1]) {
					tempUserExpressionArray[j] = '1';
					tempUserExpressionArray.erase(tempUserExpressionArray.begin() + j + 1);
					tempUserExpressionArray.erase(tempUserExpressionArray.begin() + j - 1);
					j = 0;
				};
			};
		};
		for (int j = 0; j < tempUserExpressionArray.size(); j++) { //Printing final result.
			for (int r = 0; r < userExpressionArray.size() / 2; r++) {
				cout << " ";
			};
			cout << tempUserExpressionArray[j];
		};
};

// ~ Truth Table/Operations Functions End
