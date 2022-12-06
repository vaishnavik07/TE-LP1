//============================================================================
// Name        : Best_fit.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================


// C++ implementation of Best - Fit algorithm
#include<bits/stdc++.h>
using namespace std;

// Function to allocate memory to blocks as per Best fit
// algorithm
void bestFit(int block[], int m, int processSize[], int n)
{
    // Stores block id of the block allocated to a
    // process
    int allocation[n];
    int blockSize[m];

    for(int i=0;i<m;i++){
	   blockSize[i]=block[i];
    }
    // Initially no block is assigned to any process
    memset(allocation, -1, sizeof(allocation));

    // pick each process and find suitable blocks
    // according to its size ad assign to it
    for (int i=0; i<n; i++)
    {
        // Find the best fit block for current process
        int bestIdx = -1;
        for (int j=0; j<m; j++)
        {
            if (blockSize[j] >= processSize[i])
            {
                if (bestIdx == -1)
                    bestIdx = j;
                else if (blockSize[bestIdx] > blockSize[j])
                    bestIdx = j;
            }
        }

        // If we could find a block for current process
        if (bestIdx != -1)
        {
            // allocate block j to p[i] process
            allocation[i] = bestIdx;

            // Reduce available memory in this block.
            blockSize[bestIdx] -= processSize[i];
        }
    }
    cout<<"-------Output of best fit-------"<<endl;
    cout << "\nProcess No.\tProcess Size\tBlock no.\n";
    for (int i = 0; i < n; i++)
    {
        cout << "   " << i+1 << "\t\t" << processSize[i] << "\t\t";
        if (allocation[i] != -1)
            cout << allocation[i] + 1;
        else
            cout << "Not Allocated";
        cout << endl;
    }
}

// Function to allocate memory to
// blocks as per First fit algorithm
void firstFit(int block[], int m,int processSize[], int n)
{
    // Stores block id of the
    // block allocated to a process
    int allocation[n];
    int blockSize[m];

	for(int i=0;i<m;i++){
	blockSize[i]=block[i];
	}
    // Initially no block is assigned to any process
    memset(allocation, -1, sizeof(allocation));

    // pick each process and find suitable blocks
    // according to its size ad assign to it
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            if (blockSize[j] >= processSize[i])
            {
                // allocate block j to p[i] process
                allocation[i] = j;

                // Reduce available memory in this block.
                blockSize[j] -= processSize[i];

                break;
            }
        }
    }

    cout<<"\n-------Output of first fit algorithm-------"<<endl;
    cout << "\nProcess No.\tProcess Size\tBlock no.\n";
    for (int i = 0; i < n; i++)
    {
        cout << " " << i+1 << "\t\t"
             << processSize[i] << "\t\t";
        if (allocation[i] != -1)
            cout << allocation[i] + 1;
        else
            cout << "Not Allocated";
        cout << endl;
    }
}

// Function to allocate memory to blocks as per Next fit
// algorithm
void NextFit(int block[], int m, int processSize[], int n)
{
    int allocation[n], j = 0;
    int blockSize[m];

   	for(int i=0;i<m;i++){
   	blockSize[i]=block[i];
   	}

    // Initially no block is assigned to any process
    memset(allocation, -1, sizeof(allocation));

    // pick each process and find suitable blocks
    // according to its size ad assign to it
    for (int i = 0; i < n; i++) {

        // Do not start from beginning
        while (j < m) {

            if (blockSize[j] >= processSize[i]) {

                // allocate block j to p[i] process
                allocation[i] = j;

                // Reduce available memory in this block.
                blockSize[j] -= processSize[i];

                break;
            }

            // mod m will help in traversing the blocks from
            // starting block after we reach the end.
            j = (j + 1) % m;
        }
    }

    cout << "\nProcess No.\tProcess Size\tBlock no.\n";
    for (int i = 0; i < n; i++) {
        cout << " " << i + 1 << "\t\t" << processSize[i]
             << "\t\t";
        if (allocation[i] != -1)
            cout << allocation[i] + 1;
        else
            cout << "Not Allocated";
        cout << endl;
    }
}


// Function to allocate memory to blocks as per worst fit
// algorithm
void worstFit(int blockSize[], int m, int processSize[],
                                                 int n)
{
    int allocation[n];

    // Initially no block is assigned to any process
    memset(allocation, -1, sizeof(allocation));

    for (int i=0; i<n; i++)
    {
        // Find the best fit block for current process
        int wstIdx = -1;
        for (int j=0; j<m; j++)
        {
            if (blockSize[j] >= processSize[i])
            {
                if (wstIdx == -1)
                    wstIdx = j;
                else if (blockSize[wstIdx] < blockSize[j])
                    wstIdx = j;
            }
        }

        // If we could find a block for current process
        if (wstIdx != -1)
        {
            // allocate block j to p[i] process
            allocation[i] = wstIdx;

            // Reduce available memory in this block.
            blockSize[wstIdx] -= processSize[i];
        }
    }

    cout << "\nProcess No.\tProcess Size\tBlock no.\n";
    for (int i = 0; i < n; i++)
    {
        cout << "   " << i+1 << "\t\t" << processSize[i] << "\t\t";
        if (allocation[i] != -1)
            cout << allocation[i] + 1;
        else
            cout << "Not Allocated";
        cout << endl;
    }
}

// Driver code
int main()
{
	int ch;
	char ans;
	do{
		cout<<"\n1.Best fit"<<endl;
		cout<<"\n2.First fit"<<endl;
		cout<<"\n3.Next fit"<<endl;
		cout<<"\n4.Worst fit"<<endl;
		cout<<"\n5.Exit"<<endl;

		cout<<"\nEnter your choice: ";
		cin>>ch;
		int nb,np;
		cout<<"\nEnter number of blocks: ";
		cin>>nb;
		int block[nb];
		for(int i=1;i<=nb;i++)
		{
			cout<<"\nEnter size of block "<<i<<": ";
			cin>>block[i];
		}
		cout<<"\nEnter number of processes: ";
		cin>>np;
		int processSize[np];
		for(int i=1;i<=np;i++)
		{
			cout<<"\nEnter size of process "<<i<<": ";
			cin>>processSize[i];
		}
		int m = sizeof(block)/sizeof(block[0]);
		int n = sizeof(processSize)/sizeof(processSize[0]);

		switch(ch){
		   case 1:
			   bestFit(block, m, processSize, n);
			   break;
		   case 2:
			   firstFit(block, m, processSize, n);
			   break;
		   case 3:
			   NextFit(block, m, processSize, n);
        	   break;
		   case 4:
        	   return 0;
		   default:
			   cout<<"\nError!!!!Enter correct choice!!!!";
		}
		       cout<<"\nDo you want to continue? (y/n) :";
		       cin>>ans;
		       cout<<"----------------------------------------------------";
	}while(ans=='Y' || ans=='y');
////    int block[] = {100, 500, 200, 300, 600};
//	int block[]={5,30,20};
//	int processSize[]={5,10,20};
////    int processSize[] = {212, 417, 112, 426};
//    int m = sizeof(block)/sizeof(block[0]);
//    int n = sizeof(processSize)/sizeof(processSize[0]);
//
//
//
//    firstFit(block, m, processSize, n);
//    NextFit(block, m, processSize, n);

    return 0 ;
}
