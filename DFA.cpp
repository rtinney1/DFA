/*DFA Automata Project 1
	DFA.cpp

	Defines the functions created in DFA.h

	Created by: Randi Tinney
	Date last modified: 19 March 2018
*/
#include "DFA.h"
#include <algorithm>
#include <fstream>
#include <string.h>
#include <vector>
#include <map>
#include <iostream>
#include <iterator>

using namespace std;

//Constructor
DFA::DFA(void)
{
}

//deconstructor
DFA::~DFA(void)
{
}

/* addState(string state)

	Adds a state to the vector<string> states
*/
void DFA::addState(string state)
{
	states.push_back(state);
}

/* addToAlphabet(string symbol)

	Adds a new symbol to the vector<string> alphabet
*/
void DFA::addToAlphabet(string symbol)
{
	alphabet.push_back(symbol);
}

/* addTransition(string src, string symbol, string dest)

	Adds a new transition to the map<pair<string, string>, string> transitions
	where the pair is created by the source state and symbol and the mapped to
	value is the destination state
*/
void DFA::addTransition(string src, string symbol, string dest)
{
	pair<string, string> temp(src, symbol);

	//temp = make_pair(src, symbol);

	transitions.insert(make_pair(temp, dest));
}

/* reset()

	Resets the DFA back to the initialState
*/
void DFA::reset()
{
	currentState = initialState;
}

/* addFinalState(string state)

	Adds a final state the vector<string> finalStates
*/
void DFA::addFinalState(string state)
{
	finalStates.push_back(state);
}

/*display()

	Displays the created DFA to the console screen
*/
void DFA::display()
{
	cout << "----------DFA----------" << endl;
	cout << "<states>" << endl;
	for(int i = 0; i < states.size(); i++)
		cout << states[i] << " ";

	cout << endl;

	cout << "<alphabet>" << endl;

	for(int j = 0; j < alphabet.size(); j++)
		cout << alphabet[j] << " ";

	cout << endl;

	cout << "<transition>" << endl;

	for(std::map<pair<string, string>, string>::iterator k = transitions.begin(); k != transitions.end(); k++)
		cout << "(" << k->first.first << ", " << k->first.second << ") -> " << k->second << endl;

	cout << "<initial state>" << endl;

	cout << initialState << endl;

	cout << "<final states>" << endl;

	for(int n = 0; n < finalStates.size(); n++)
		cout << finalStates[n] << " ";

	cout << endl;

	cout << "-------------------------" << endl;
}

/* isValid(string symbol)

	Returns true if the symbol is an element of the alphabet;
	Returns false if it isn't
*/
bool DFA::isValid(string symbol)
{
	if(find(alphabet.begin(), alphabet.end(), symbol) != alphabet.end())
		return true;
	else
		return false;
}

/* getCurrentState()

	Returns the currentState of the DFA
*/
string DFA::getCurrentState()
{
	return currentState;
}

/* goToWith(string symbol)

	Sets the current state based on the value gotten
	from the mapping of the current state and the given symbol
*/
void DFA::goToWith(string symbol)
{
	pair<string, string> temp;

	temp = make_pair(currentState, symbol);

	std::map<pair<string, string>, string>::iterator it = transitions.find(temp);

	currentState = it->second;
}

/* isFinalState(string state)

	Returns true if the given state is a final state;
	Returns false if it isn't
*/
bool DFA::isFinalState(string state)
{
	if(find(finalStates.begin(), finalStates.end(), state) != finalStates.end())
		return true;
	else
		return false;
}
