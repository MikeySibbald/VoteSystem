// Michael Sibbald - C00206817
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

class BallotPaper
{
public:
	BallotPaper();

	string preference, ballotArr[4][2], candName;

	void setPreference(Candidate candArray[], string pref)
	{
		for (int i = 0; i < 4; i++)
		{
			candName = candArray[i].getcandName();
			ballotArr[i][0] = pref[i];
			ballotArr[i][1] = candName;
		}
	}
	string getPreference(int n)
	{
		string p = to_string(n);
		bool found = false;
		string output = "";

		for (int i = 0; i < 4; i++)
		{
			if (ballotArr[i][0] == p)
			{
				output = ballotArr[i][1];
				found = true;
			}
		}
		if (found == true)
		{
			return output;
		}
		else
		{
			return "";
		}
	}
};

BallotPaper::BallotPaper()
{
}



int main()
{
	Candidate candArray[5];
	BallotPaper ballotArray[100];
	string line, name, party;
	int i = 0, j = 0, lineLen = 0, noOfBallots = 4;
	bool allCand = false;

	ifstream inFile("vote.txt");
	if (inFile.is_open())
	{
		while (!inFile.eof())
		{
			getline(inFile, line);
			lineLen = line.length();
			if (line[0] == '-')
			{
				allCand = true;
			}
			if (allCand == false)
			{
				for (i = 0; i < lineLen; i++)
				{
					if (line[i] == ',')
					{
						break;
					}
				}
				name = line.substr(0, i);
				party = line.substr(i + 2);

				candArray[j] = Candidate(name, party);
				j++;
			}
			else if(allCand == true && line[0] != '-')
			{
				for (int i = 0; i < noOfBallots; i++)
				{
					ballotArray[i].setPreference(candArray, line);
//					for (int j = 1; j < 5; j++)
//					{
						cout << ballotArray[i].getPreference(1);
//					}
				}
				cout << endl;
			}
		}
	}
	inFile.close();

/*	for (int i = 0; i < 4; i++)
	{
		candArray[i].printCandidate();
	}*/

    return 0;
}

