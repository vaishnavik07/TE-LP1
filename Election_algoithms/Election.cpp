//============================================================================
// Name        : trialElection.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <bits/stdc++.h>
using namespace std;

int n,coordinator;
int pstatus[20];

void display()
{
	cout<<"-----------------------------------------"<<endl;
	cout<<"Processes: ";
	for(int i=1;i<=n;i++)
		cout<<i<<"\t";
	cout<<endl;
	cout<<"Status: ";
	for(int i=1;i<=n;i++)
		cout<<pstatus[i]<<"\t";
	cout<<endl;
	cout<<"Coordinator is "<<coordinator<<endl;
}

void bully(){
	int ch,crash,activate,pid,subcoordinator;
	queue<int>q;
	do{
		cout<<"----------------------------"<<endl;
		cout<<"1.Crash\n2.Initiate election\n3.diplay\n4.Exit"<<endl;
		cout<<"Enter your choice: ";
		cin>>ch;

		switch(ch)
		{
		case 1:

			cout<<"\nEnter process to crash: ";
			cin>>crash;
			if(pstatus[crash])
				pstatus[crash]=0;
			else
				cout<<"\nProcess "<<crash<<" is already dead";

			if(crash==coordinator)
			{
			    cout<<"Coordinator is dead!!! Initiate election..."<<endl;
			}
			break;
		case 2:
				do{
					cout<<"Enter which process will initiate election: ";
					cin>>pid;
					if(pid==coordinator || pstatus[pid]==0)
					{
						cout<<"Please enter valid process id...";
					}
				}while(pid==coordinator || pstatus[pid]==0);
				subcoordinator=pid;
				while(true)
				{
					for(int i=pid+1;i<=n;i++)
					{
						cout<<"Message is sent from "<<pid<<" to "<<i<<endl;

						if(pstatus[i])
						{
							if(subcoordinator==pid)
							q.push(i);
							cout<<"Ok Response is sent from "<<i<<" to "<<pid<<endl;
						}
						else
						{
							cout<<"Process "<<i<<" is dead"<<endl;
						}
					}
					if(!q.empty())
					{
						pid=q.front();
						q.pop();
					}
					else
						break;

				 }
				 coordinator=pid;

			display();
			break;
		case 3:
			display();
			break;
		case 4:
			break;
		}
	}while(ch!=4);

}

void ring()
{
	int ch,crash,last;
	vector<int>activeList;
	int maxi;
    do{
    	cout<<"-------------------------------------------"<<endl;
    	cout<<"1.Crash\n2.Initiate election\n3.display\n4.Exit"<<endl;
    	cout<<"Enter your choice: ";
    	cin>>ch;

    	switch(ch)
    	{
    	case 1:
    		cout<<"\n Enter which process crashes: ";
    		cin>>crash;
    		if(pstatus[crash]==1)
    			pstatus[crash]=0;
    		else
    			cout<<"Process is already dead"<<endl;
    		if(crash==coordinator)
    			cout<<"Coordinator failed. Initiate election...."<<endl;
    		break;
    	case 2:
    		int pid;
    		do{
    			cout<<"Enter which process initiates election";
				cin>>pid;
				if(pid==coordinator || pstatus[pid]==0)
					cout<<"Please enter valid process id"<<endl;
    		}while(pid==coordinator || pstatus[pid]==0);

    		activeList.push_back(pid);
    		last=pid;
    		for(int i=pid+1;i!=pid;i++)
    		{
    			if(pstatus[i]==0)
    			{
    				if(i==n)i=0;
    				continue;
    			}

    			if(i==1)
    			{
    			    cout<<"Process "<<last<<" passes message to process "<<i;
    			}
    			else
    			{
    				cout<<"Process "<<last<<"passes message to process"<<i%n;
    			}
                last=i;
    			activeList.push_back(i);
    			cout<<"Active list contains: ";
    			for(int i=0;i<activeList.size();i++)
    			{
    				cout<<activeList[i]<<" ";
    			}
    			cout<<endl;
    			if(i==n)i=0;
    		}
    		cout<<"Coordinator is: ";
    	    maxi=activeList[0];
    		for(int i=0;i<activeList.size();i++)
			{
				maxi=max(maxi,activeList[i]);
			}
    		cout<<maxi<<endl;
    		break;
    	case 3:
    		display();
    		break;
    	case 4:
    		break;
    	}

    }while(ch!=4);
}

int main() {
//	cout << "!!!Hello World!!!" << endl; // prints !!!Hello World!!!

	cout<<"Enter number of processes: ";
	cin>>n;

	for(int i=1;i<=n;i++)
	{
		cout<<"\nEnter process "<<i<<" is alive or not(0/1): ";
		cin>>pstatus[i];
		if(pstatus[i]==1)
			coordinator=i;
	}
	display();

	bully();
	ring();
	return 0;
}
