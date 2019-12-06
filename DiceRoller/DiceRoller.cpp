// DiceRoller.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <cstdlib>
#include <ctime>
using namespace std;

string mInput;
int mDice;
int mSize;
int mDPos;
int mTotal;
vector<int> mResults;

void GetInput()
{
	cout << "Enter Dice in usual D&D format (eg 1d6): \n";
	getline(cin, mInput);
}

bool VerifyInput()
{
	bool _rtnVal = false;
	// Set _dice to letter d
	string _dice("d");

	// Search for the d
	size_t found = mInput.find(_dice);

	// If d found, record it's position
	if (found != string::npos)
	{
		_rtnVal = true;
		mDPos = found;
	}
	// If d not found, throw up a warning
	else
		cout << "Please check dice selection includes d between the numbers. \n";

	// Check for anything incompatible, display warning if invalid input found
	found = mInput.find_first_not_of("d1234567890");

	if (found != string::npos)
	{
		_rtnVal = false;
		cout << "Please only enter numbers and the letter d. \n";
	}

	return _rtnVal;
}

void ParseInput()
{
	string _Dice;
	string _Size;
	// Save all the numbers from position 0 to the d position
	_Dice = mInput.substr(0, mDPos);
	// Save the numbers after the d position
	_Size = mInput.substr(mDPos + 1, mInput.length());

	// Convert string to int
	istringstream iss1(_Dice);
	iss1 >> mDice;
	istringstream iss2(_Size);
	iss2 >> mSize;

	//cout << "Dice: " + _Dice + "\n";
	//cout << "Size: " + _Size + "\n";
}

void RollDice()
{
	mResults.clear();
	int _currentRoll = 0;
	mTotal = 0;
	mResults.reserve(mDice);
	for (int i = 1; i <= mDice; i++)
	{
		_currentRoll = rand() % mSize + 1;
		mResults.push_back(_currentRoll);
		mTotal += _currentRoll;
	}
}

void PrintResults()
{
	stringstream _output;
	_output << mTotal;
	cout << "Your total roll was: " + _output.str() + " \n";
	cout << "Your individual rolls were: \n";

	for (int var : mResults)
	{
		stringstream ss;
		ss << var;
		cout << ss.str() + "\n";
	}

}

string ReRoll()
{
	// Ask user to reroll?
	std::cout << "Do you want to reroll? \n";
	std::cout << "[1] Yes\n"
		<< "[2] No\n";

	std::string _input;
	std::getline(std::cin, _input);

	while (_input != "1" && _input != "2") {
		std::cout << "Invalid!\n\n";

		std::cout << "Do you want to reroll?\n";
		std::cout << "[1] Yes\n"
			<< "[2] No\n";
		std::getline(std::cin, _input);
	}
	return _input;
}

int main()
{
	// Set random number generator seed to system time
	srand(time(NULL));
	// Get initial input
	GetInput();
	// Check input is correct
	while (!VerifyInput())
		GetInput();
	// Extract nubmer of dice and size of dice
	ParseInput();
	// Roll Dice
	RollDice();
	// Print Results
	PrintResults();

	// Check to reroll or not
	while (ReRoll() != "2")
	{
		// Get initial input
		GetInput();
		// Check input is correct
		while (!VerifyInput())
			GetInput();
		// Extract nubmer of dice and size of dice
		ParseInput();
		// Roll Dice
		RollDice();
		// Print Results
		PrintResults();
	}
	return 0;
}


// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
