//============================================================================
// Name        : trial_macro2.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <bits/stdc++.h>
using namespace std;

int main() {

    ifstream fin,kpdt,mnt,mdt;
    fin.open("intermediate2.txt");
    kpdt.open("kpdtab2.txt");
    mnt.open("mnt2.txt");
    mdt.open("mdt2.txt");

    ofstream fout;
    fout.open("output.txt");

    vector<array<int,4>>mntab;
    vector<pair<string ,string>>kpdtab;
    map<string,int>mp;  //macro name and mnt index
    vector<vector<string>>mdtab;

    string word,line;
    while(getline(mnt,line))
    {
        cout<<line<<endl;
    	stringstream ss(line);
    	ss>>word;
    	mp[word]=mntab.size();

    	array<int,4>mntEntry;
    	for(int i=0;i<4;i++)
    	{
    		ss>>word;
    		if(word=="-") mntEntry[i]=-1;
    		else mntEntry[i]=stoi(word);
    	}
    	cout<<mntEntry[0]<<" "<<mntEntry[1]<<" "<<mntEntry[2]<<" "<<mntEntry[3]<<endl;
    	mntab.push_back(mntEntry);
    }


    while(getline(kpdt,line))
    {
    	stringstream ss(line);
    	ss>>word;
    	pair<string,string>kpdEntry={"",""};
    	kpdEntry.first=word;
    	if(ss>>word)
    	  kpdEntry.second=word;
    	kpdtab.push_back(kpdEntry);
    }

    while(getline(mdt,line))
	{
		stringstream ss(line);
		ss>>word;
		vector<string>mdtEntry;
		mdtEntry.push_back(word);
		while(ss>>word)
		{
//			if(word[0]=='=')
//			cout<<word<<" ";
			if(word[word.size()-1]==',')
				word=word.substr(0,word.size()-1);
			if(word[0]=='(')
			{
				word=word.substr(3,1);
			}
			mdtEntry.push_back(word);
		}
		mdtab.push_back(mdtEntry);
	}


    while(getline(fin,line))
    {
    	stringstream ss(line);
    	ss>>word;
    	int mntIndex=mp[word];
//    	cout<<"MNTINDEX"<<mntIndex<<endl;
    	int noparams=mntab[mntIndex][0]+mntab[mntIndex][1];

    	vector<string>ala(noparams+1);
    	map<string,int>alaIndexofKp;

    	int kpdtabIndex=mntab[mntIndex][3];
    	int p=1;
    	if(kpdtabIndex!=-1){
    		for(int i=kpdtabIndex-1;i<(kpdtabIndex+mntab[mntIndex][1]-1);i++)
			{
//    			cout<<kpdtab[i].first<<" "<<kpdtab[i].second<<endl;
				ala[p]=kpdtab[i].second;
				alaIndexofKp[kpdtab[i].first]=p;
				p++;
			}
    	}
//    	cout<<"kpdindex"<<endl;
//    	for(auto it:alaIndexofKp)
//    	{
//    		cout<<it.first<<" "<<it.second<<endl;
//    	}

    	while(ss>>word)
    	{
    		if(word[word.size()-1]==',')
    			word=word.substr(0,word.size()-1);
            cout<<word<<" ";
    		int indexofequal=-1;
    		for(int i=0;i<word.size();i++)
    		{
    			if(word[i]=='=')
    			{
    				indexofequal=i;
    				break;
    			}
    		}
    		if(indexofequal==-1)
    		{
    			ala[p]=word;
    			p++;
    		}
    		else
    		{
				string token1=word.substr(0,indexofequal);
				string token2=word.substr(indexofequal+1);
				ala[alaIndexofKp[token1]]=token2;
//				cout<<token1<<" "<<token2<<endl;
    		}

    	}

    	cout<<"----ala------"<<endl;
    	for(int i=1;i<noparams+1;i++)
    	{
    		cout<<ala[i]<<endl;
    	}

    	cout<<"----EXPANDED CODE-------"<<endl;
    	int mdtIndex=mntab[mntIndex][2];
    	while(true)
    	{
    		if(mdtab[mdtIndex-1][0]=="MEND")
    			break;
            fout<<mdtab[mdtIndex-1][0]<<" ";
            cout<<mdtab[mdtIndex-1][0]<<" ";
    		for(int i=1;i<mdtab[mdtIndex-1].size();i++)
    		{
    			if(mdtab[mdtIndex-1][i][0]=='=')
    			{	fout<<mdtab[mdtIndex-1][i]<<" ";
    			    cout<<mdtab[mdtIndex-1][i]<<" ";
    			}
    			else{
    				fout<<ala[stoi(mdtab[mdtIndex-1][i])]<<" ";
    				cout<<ala[stoi(mdtab[mdtIndex-1][i])]<<" ";
    			}
    			if(i!=mdtab[mdtIndex-1].size()-1)
    			{
    				fout<<", ";
    				cout<<", ";
    			}
    		}
    		fout<<endl;
			cout<<endl;
    	    mdtIndex++;
    	}
        fout<<endl;
        cout<<endl;
    }

    cout<<"-------macro name and index--------"<<endl;
    for(auto it=mp.begin();it!=mp.end();it++)
    {
    	cout<<it->first<<"\t"<<it->second<<endl;
    }

    cout<<"-------MNTAB--------"<<endl;

    for(int i=0;i<mntab.size();i++)
    {
    	cout<<mntab[i][0]<<"\t"<<mntab[i][1]<<"\t"<<mntab[i][2]<<"\t"<<mntab[i][3]<<"\n";
    }

    cout<<"-------KPDTAB--------"<<endl;

	for(int i=0;i<kpdtab.size();i++)
	{
		cout<<i<<"\t"<<kpdtab[i].first<<"\t"<<kpdtab[i].second<<"\n";
	}

	cout<<"-------MDTAB--------"<<endl;

	for(int i=0;i<mdtab.size();i++)
	{
		for(int j=0;j<mdtab[i].size();j++)
		{
			cout<<mdtab[i][j]<<" ";
		}
		cout<<endl;
	}

	return 0;
}
