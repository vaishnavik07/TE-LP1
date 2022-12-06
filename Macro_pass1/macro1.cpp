//============================================================================
// Name        : trialmacro1.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <bits/stdc++.h>
using namespace std;

int main()
{

	ifstream fin;

	fin.open("source.txt");

	ofstream fout;
	fout.open("output.txt");

	ofstream mntout;
	mntout.open("mnt.txt");

	ofstream mdtout;
	mdtout.open("mdt.txt");

	ofstream pout;
	pout.open("pndtab.txt");

	ofstream kout;
	kout.open("kpdtab.txt");

	vector<array<string, 5>> mnt;
	vector<pair<string, string>> kpdtab;

	map<string, int> pntab;

	string line;
	string word;

	bool macroStart = false;

	int p = 1;
	bool started = false;

	while (getline(fin, line))
	{

		stringstream st(line);
		st >> word;

		if (started)
		{
			if (word != "END")
			{
				fout << word << " ";
				while (st >> word)
				{
					fout << word << " ";
				}
				fout << endl;
			}
			continue;
		}

		if (word == "MACRO")
		{
			macroStart = true;
			continue;
		}

		if (macroStart)
		{
			array<string, 5> a;
			mnt.push_back(a);
			int i = mnt.size() - 1;

			mnt[i][0] = word;
			mnt[i][3] = to_string(p);

			int pp = 0;
			int kp = 0;

			pout << "PNTAB for " << word << " Macro\n";

			while (st >> word)
			{
				if (word[word.size() - 1] == ',')
				{
					word = word.substr(0, word.size() - 1);
				}
				int equalInd = -1;

				for (int i = 0; i < word.size(); i++)
				{
					if (word[i] == '=')
					{
						equalInd = i;
						break;
					}
				}

				if (equalInd == -1)
				{
					pp++;
					word = word.substr(1);
					pntab[word] = pntab.size() + 1;
					pout << pntab.size() << ". " << word << endl;
				}
				else
				{
					kp++;

					pair<string, string> newPair = {word.substr(1, equalInd - 1), word.substr(equalInd + 1)};
					kpdtab.push_back(newPair);

					pntab[newPair.first] = pntab.size() + 1;
					pout << pntab.size() << ". " << newPair.first << endl;
				}
			}

			mnt[i][1] = to_string(pp);
			mnt[i][2] = to_string(kp);
			if (kp != 0)
			{
				mnt[i][4] = to_string(kpdtab.size() - kp + 1);
			}

			macroStart = false;
			continue;
		}

		if (word == "MEND")
		{
			mdtout << "MEND" << endl;
			pntab.clear();
		}
		else if (word == "START")
		{
			started = true;
		}
		else
		{
			mdtout << word << " ";
			bool start = true;
			while (st >> word)
			{
				if (!start)
				{
					mdtout << ", ";
				}
				if (word[0] == '&')
				{
					word = word.substr(1);
					if (word[word.size() - 1] == ',')
					{
						word = word.substr(0, word.size() - 1);
					}
					mdtout << "(P," << pntab[word] << ")";
				}
				else
				{
					if (word[word.size() - 1] == ',')
					{
						word = word.substr(0, word.size() - 1);
					}
					mdtout << word;
				}
				start = false;
			}
			mdtout << endl;
		}

		p++;
	}

	fin.close();

	for (int i = 0; i < mnt.size(); i++)
	{
		for (int j = 0; j < 5; j++)
		{
			mntout << mnt[i][j] << " ";
		}
		mntout << endl;
	}

	for (int i = 0; i < kpdtab.size(); i++)
	{
		kout << kpdtab[i].first << " " << kpdtab[i].second << endl;
	}

	return 0;
}
