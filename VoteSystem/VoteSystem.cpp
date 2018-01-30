// Michael Sibbald - C00206817
//
#include "stdafx.h"
#include <iostream>
using namespace std;
#include <cstdlib>
#include <fstream>
#include <string>

class Candidate
{
public:
	Candidate();

	string candName;
	string candParty;

	string getcandName()
	{
		return candName;
	}

	void setcandName(string name)
	{
		candName = name;
	}

	string getcandParty()
	{
		return candParty;
	}

	void setcandParty(string party)
	{
		candParty = party;
	}

	Candidate(string name, string party)
	{
		setcandName(name);
		setcandParty(party);
	}

	void printCandidate()
	{
		cout << "Name: " << getcandName() << endl << "Party: " << getcandParty() << endl;
	}

};


Candidate::Candidate()
{
}


int main()
{
	Candidate candArray[5];

	string line, name, party;
	int i = 0, j = 0;

	cout << "Take in each line" << endl;

	ifstream inFile("vote.txt");
	if (inFile.is_open())
	{
		while (!inFile.eof())
		{
			getline(inFile, line);
			cout << line << endl;

			for (i = 0; i < line.length(); i++)
			{
				if (line[i] == ',')
				{
					break;
				}
			}
			name = line.substr(0, i);
			party = line.substr(i + 2);

/*			cout << name << endl;
			cout << party << endl;*/

			candArray[j] = Candidate(name, party);
			j++;

		}
	}
	inFile.close();

	for (int i = 0; i < 3; i++)
	{
		candArray[i].printCandidate();
	}

    return 0;
}

