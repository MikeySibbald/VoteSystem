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
	int noOfPref;

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

	int getNoOfPref()
	{
		return noOfPref;
	}

	void setNoOfPref(int n)
	{
		noOfPref = n;
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

	string preference, ballotArr[100][2], candName;

	void setPreference(Candidate candArray[], string pref, int noOfBallots)
	{
		for (int i = 0; i < noOfBallots; i++)
		{
			candName = candArray[i].getcandName();
			ballotArr[i][0] = pref[i];
			ballotArr[i][1] = candName;
		}
	}
	string getPreference(int n, int noOfBallots)
	{
		string p = to_string(n);
		bool found = false;
		string output = "";

		for (int i = 0; i < noOfBallots; i++)
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

void getVotes(Candidate cand, int noOfBallots, BallotPaper ballotArr[])
{
	int counter = 0;

	for (int i = 0; i < noOfBallots; i++)
	{
		if (ballotArr[i].getPreference(1, noOfBallots) == cand.getcandName())
		{
			counter++;
		}
	}
	cand.setNoOfPref(counter);
	if (cand.getcandName() != "")
	{
		cout << cand.getcandName() << ": " << cand.getNoOfPref() << endl;
	}
}

int deleteLowestCand(Candidate candArray[], int noOfCand)
{
	Candidate lowest;

	for (int i = 0; i < noOfCand; i++)
	{
		if (candArray[i].getNoOfPref() < lowest.getNoOfPref() || i == 0)
		{
			lowest = candArray[i];
		}
	}
	for (int i = 0; i < noOfCand; i++)
	{
		if (candArray[i].getcandName() == lowest.getcandName())
		{
			for (int j = i; j < noOfCand; j++)
			{
				candArray[j] = candArray[j + 1];
			}
		}
	}
	candArray[noOfCand].setcandName("");
	candArray[noOfCand].setcandParty("");
	candArray[noOfCand].setNoOfPref(0);
	noOfCand--;
	return noOfCand;
}

int main()
{
	string fileLine;
	int candCount = 0, noOfBallots = 0;
	bool isCand = false;
	ifstream fileCount("vote.txt");
	if (fileCount.is_open())
	{
		while (!fileCount.eof())
		{
			getline(fileCount, fileLine);

			if (fileLine[0] == '-')
			{
				isCand = true;
			}
			if (isCand == false)
			{
				candCount++;
			}
			else if (isCand == true && fileLine[0] != '-')
			{
				noOfBallots++;
			}

		}

	}
	fileCount.close();





	Candidate candArray[100];
	BallotPaper ballotArray[100];
	string line, name, party, allBallots[100];
	int i = 0, j = 0, lineLen = 0, ballotCount = 0;
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
				allBallots[ballotCount] = line;
				ballotArray[ballotCount].setPreference(candArray, line, noOfBallots);
				ballotCount++;
			}
		}
	}
	inFile.close();

	for (int i = 0; i < candCount; i++)
	{
		getVotes(candArray[i], noOfBallots, ballotArray);
	}
	candCount = deleteLowestCand(candArray, candCount);
	cout << candCount << endl;

	for (int i = 0; i < candCount; i++)
	{
		getVotes(candArray[i], noOfBallots, ballotArray);
	}

    return 0;
}

