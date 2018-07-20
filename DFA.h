/*DFA Automata Project 1
	DFA.h

	Defines the class DFA.

	This class creates a DFA based on a text file using the
	functions addState, addToAlphabet, addTransition, and addFinalState.

	For processing purposes,

	isValid is to check if a symbol is an element of the given alphabet,
	getCurrentState returns the current state the DFA is in,
	goToWith processes the transition from the current state to another state on a given symbol,
	isFinalState checks to see if a given state is a final state.

	The function setCurrentState is used to change the current state to a given state and is used
	primarily in goToWith and reset.
	The function reset resets the DFA to the initial state.
	The function display displays the created DFA to the screen.

	Created by: Randi Tinney
	Date last modified: 19 March 2018
*/
#ifndef DFA_H
#define DFA_H

#include <vector>
#include <map>
#include <fstream>
#include <string.h>

using namespace std;

class DFA
{
	public:
		DFA();
		~DFA();
		void addState(string state);
		void addToAlphabet(string symbol);
		void addTransition(string src, string symbol, string dest);
		void setCurrentState(string state);
		void reset();
		void addFinalState(string state);
		void display();
		bool isValid(string symbol);
		string getCurrentState();
		void goToWith(string symbol);
		bool isFinalState(string state);
		string initialState;

	private:
		vector<string> states;
		vector<string> alphabet;
		map<pair<string, string>, string> transitions;
			//1st string = current state, 2nd string = symbol to process, 3rd string or value = transitioned to state
		string currentState;
		vector<string> finalStates;
};

#endif
