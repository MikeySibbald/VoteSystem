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
	int noOfPref = 0;

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
	Candidate(string name, string party, int noOfPref)
	{
		setcandName(name);
		setcandParty(party);
		setNoOfPref(noOfPref);
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
	int getPersonPref(string candName, int noOfCandidates)
	{
		bool found = false;
		string output = 0;
		///////////////////////////This is broken beyond repair//////////////////////////////////////////
		for (int i = 0; i < noOfCandidates; i++)
		{
			if (ballotArr[i][1] == candName)
			{
				output = ballotArr[i][0];
				found = true;
			}
		}
		if (found == true)
		{
			return std::stoi(output);
		}
		else
		{
			return noOfCandidates;
		}
	}

	
};

BallotPaper::BallotPaper()
{
}

int getVotes(Candidate candArray[], int noOfBallots,int noOfCandidates, BallotPaper ballotArr[])
{
	for (int j = 0; j < noOfCandidates; j++)
	{
		int counter = 0;

		for (int i = 0; i < noOfBallots; i++)
		{
			if (ballotArr[i].getPreference(1, noOfBallots) == candArray[j].getcandName())
			{
				counter++;
			}
		}
		candArray[j] = Candidate(candArray[j].getcandName(), candArray[j].getcandParty(), counter);

		if (candArray[j].getcandName() != "")
		{
			cout << candArray[j].getcandName() << ": " << candArray[j].getNoOfPref() << endl;
		}
	}
	
	return 0;
}

int getLowestCandLocation(Candidate candArray[], int noOfCand)
{
	Candidate lowest;
	string output;
	int lowestPos = 0;

	for (int i = 0; i < noOfCand; i++)
	{
		if (candArray[i].getNoOfPref() < lowest.getNoOfPref() || i == 0)
		{
			lowestPos = i;
			lowest = candArray[i];
		}
	}
	return lowestPos;
}


string deleteLowestCand(Candidate candArray[], int noOfCand)
{
	Candidate lowest;
	string output;

	for (int i = 0; i < noOfCand; i++)
	{
		if (candArray[i].getNoOfPref() < lowest.getNoOfPref() || i == 0)
		{
			lowest = candArray[i];
		}
	}
	cout << lowest.getcandName() << " has been eliminated" << endl;
	output = lowest.getcandName();
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
	return output;
}

void redistributeVotes(Candidate candArray[], int noOfCandidates, BallotPaper ballotArray[], int noOfBallots, int deletedPos, string allBallots[], string deletedPerson)
{
	string line;
	int deletedPreference;

	for (int j = 0; j < noOfBallots; j++)
	{
		line = allBallots[j];
		for (int k = deletedPos; k < noOfCandidates; k++)
		{
			line[k] = line[k + 1];
		}
		line[noOfCandidates] = NULL;
		for (int i = 0; i < noOfCandidates; i++)
		{
			deletedPreference = ballotArray[i].getPersonPref(deletedPerson, noOfBallots);
			if (line[i] > deletedPreference)
			{
				line[i] = line[i] - 1;
			}
		}
		allBallots[j] = line;
	}

	for (int i = 0; i < noOfBallots;i++)
	{
		ballotArray[i].setPreference(candArray, allBallots[i], noOfBallots);
	}
}



int main()
{
	//Count all the candidates and ballots
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

	//The main bit of code
	Candidate candArray[100];
	BallotPaper ballotArray[100];
	string line, name, party, allBallots[100], deletedPerson;
	int i = 0, j = 0, lineLen = 0, ballotCount = 0, lowestCandPos = 0;
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

	getVotes(candArray, noOfBallots, candCount,ballotArray);


	lowestCandPos = getLowestCandLocation(candArray, candCount);
	deletedPerson = deleteLowestCand(candArray, candCount);
	candCount--;

	getVotes(candArray, noOfBallots, candCount, ballotArray);
	redistributeVotes(candArray, candCount, ballotArray, noOfBallots, lowestCandPos, allBallots, deletedPerson);
	getVotes(candArray, noOfBallots, candCount, ballotArray);


    return 0;
}

