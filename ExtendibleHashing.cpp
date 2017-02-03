#include<cstdio>
#include<iostream>
#include<cstdlib>

using namespace std;

// Single block structure for LinkList
struct node
{
        int data;
        node *next;
};


class Bucket
/*
   Data pages
*/
{
    
	int local_depth;
        int max_size;
        int cur_size; // -1 indicates Empty Bucket 
        int *A; // A dynamic Array 
    public:
        Bucket(int size)
        {  
		max_size = size;
		local_depth = global_depth; //Initially
		cur_size =-1;
		A = (int *) malloc(sizeof(int) *size);
        }
        ~Bucket()
        {
            delete A;
        }
        
        void insert(int value)
        {
                
		int hashKey = hashCode(value); // calculates hash key of value
		int posDir = findPos(hashKey); //gets the pos of directory
						//here we need to code related to bucket of that directory pos.
		if (cur_size < max_size-1)
                {
                    cur_size +=1;
                    A[cur_size] = value;
                }
		if (cur_size == max_size-1)
		{
			int 
        }
        void remove()
        { 

        }
        void removeAll()
        {
        }
        void print()
        {	
		int i;
		//cout << "-----------------------------------------" << endl;
		cout << "--------Printing Bucket----" << endl;
		for(i=0;i<=cur_size; i++)
			cout << A[i] << "\t";
		cout << "\n--------End of Bucket---" << endl;     
	}

 };


int printMenu() {
	system("clear");
	cout << "-----------------------------------------" << endl;
	cout << "Extendible Hashing Implementation." << endl;
	cout << "-----------------------------------------" << endl;
	cout << "\t\t 1. Insert a Record" << endl;
	//cout << "\t\t 2. Search a Record" << endl;
	//cout << "\t\t 3. Delete a Record" << endl;
	cout << "\t\t 2. Show All Records"<< endl;
	//cout << "\t\t 5. Delete All Records" << endl;
	cout << "\t\t 3. Exit" << endl;
	int choice;
	cout << "\nChoice : ";
	cin >> choice;
	cout.flush();
	return choice;
}

int main()
{
	int n,value;
	char ch;
	cout << "Enter bucket-size : ";
	cin >> n;
	Bucket *B = new Bucket(n);
	while(true) {
		int choice = printMenu();
		ch = getchar();  // eat newline
		switch(choice) {
			case 1:   // Insert a record
				{
					
					cout << "Enter value to be added : ";
					cin >> value;
					B->insert(value);
					break;
				}
			
			case 2:   // show All Records
			        {
					system("clear");
					B->print();
					//cout << endl << "enter to continue ...";
					//ch = getchar();
				}
			case 3:
				exit(0);
		}
	}

	return 0;
}

