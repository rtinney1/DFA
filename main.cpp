/* DFA Automata Project 1
	main.cpp

	Uses the functions defined in DFA.h to create a DFA from a text file
	entered by the user. The user will enter the name of the file on the
	command line when running the program. The program will then create
	a DFA and show the created DFA once done. Then, the user will be prompted
	to enter a string and the program will return the path it took based
	on the defined transitions. The string will be reported as ACCEPTED if
	the last state is a final state or REJECTED if the last state is not a final
	state. The processing will also stop if a symbol entered is not in the reported
	alphabet

	Created by: Randi Tinney
	Date last modified: 19 March 2018
*/

#include <iostream>
#include <iomanip>
#include <fstream>
#include <string.h>
#include <vector>
#include "DFA.h"

using namespace std;

ifstream inFile;

/* check()
Will check the input of the file name. Will return true if the file is able
to be opened, and false if not.
*/
bool check (ifstream& inFile)
{
	if(!inFile)
		return false;
	else
		return true;
}

/* create(ifstream& inFile)

	Creates the DFA with the given file.
	The file must be in the proper order as defined in the lab handout for it to work.
*/
void create(DFA& dfa, ifstream& file)
{
	string tempIn;
	string src;
	string symbol;
	string dest;

	//char ki;

	inFile >> tempIn; //get "states" tag
	inFile >> tempIn; //get first state

	while(tempIn.find("alphabet") == std::string::npos)
	{
		dfa.addState(tempIn);
		inFile >> tempIn;
	}
	
	//tempIn = "alphabet" tag
	inFile >> tempIn; //get first alphabet symbol

	while(tempIn.find("transitions") == std::string::npos)
	{
		dfa.addToAlphabet(tempIn);
		inFile >> tempIn;
	}

	inFile >> src;

	while(src.find("initial") == std::string::npos)
	{
		inFile >> symbol >> dest >> ws;

		dfa.addTransition(src, symbol, dest);

		inFile >> src;
	}

	//src = "<initial " tag
	inFile >> tempIn; //skip states>
	inFile >> tempIn; //get initial state

	dfa.initialState = tempIn; //set Initial state
	dfa.reset(); //make sure DFA starts at initial state

	inFile >> tempIn; //get "<final " tag
	inFile >> tempIn; //get "states>" tage

	while(!inFile.eof())
	{
		inFile >> tempIn; //get final states
		dfa.addFinalState(tempIn);
	}
}

int main(int argc, char* argv[])
{
	DFA dfa;
	string toProcess;
	string currentState;
	string sym;
	bool failed;

	if(argc == 1) //only one argument means the user failed to give a file
		cout << "usage: <prog_name> <file_name>" << endl;
	else
	{

		inFile.open(argv[1]);

		if(check(inFile))//check to see if the file is readable
		{
			create(dfa, inFile); //create the DFA

			dfa.display(); //display created DFA

			while(true)
			{
				dfa.reset();//ensures the DFA starts at the initial state
				cout << "Enter a string to process (Ctrl^C to end):";
				getline(cin, toProcess);

				failed = false;//boolean is used to see if there is a symbol entered
								//that was not part of the alphabet

				currentState = dfa.getCurrentState();//get current state

				cout << "[" << currentState << "]";//output current state (initial state)

				for (int i = 0; i < toProcess.length(); i++)
				{
					sym = toProcess[i]; //get char from string
					if(dfa.isValid(sym))//checks to see if the symbol is an element of the alphabet
					{
						currentState = dfa.getCurrentState();
						cout << " -" << sym << "-> ";
						dfa.goToWith(sym); //changes the current state based on the transition from the previous current
											//state and the symbol recieved
						currentState = dfa.getCurrentState();//get new current state
						cout << "[" << currentState << "]";//output current state to screen
					}
					else//char was not an element of the alphabet
					{
						cout << " (Invalid symbol " << sym << ")";
						failed = true;
						break;//exit for loop
					}
		  		}

		  		if(!failed)
		  		{
		  			if(dfa.isFinalState(currentState))//checks to see if the string passed or not
		  				cout << " : ACCEPTED" << endl;
					else
						cout << " : REJECTED" << endl;
				}
				else
					cout << " : REJECTED" << endl;//for when a symbol isn't in the alphabet
			}
		}
		else
			cout << "Automata file could not be opened!" << endl;
	}

	return 0;
}
