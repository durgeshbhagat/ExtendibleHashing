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
    public:
        Bucket(int size =0)
        {  int local_depth =0;
           int max_size = size 
           int cur_size =-1; // -1 indicates Empty Bucket 
           int A[max_size]; // A dynamic Array 
        }
        ~LinkedList()
        {
            delete head;
        }
        
        void insert(int value)
        {
                if (cur_size < max_size-1)
                {
                    cur_size +=1;
                    head[cur_size] = value;
                }
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
		cout << "-----------------------------------------" << endl;
		cout << "--------Printing Bucket----" << endl;
		for(i=0;i<cur_size; i++)
			cout << A[i] << '\t';
		cout << "--------End of Bucket---" << endl;     
	}

 }


int printMenu() {
	system("clear");
	cout << "-----------------------------------------" << endl;
	cout << "Extendible Hashing Implementation." << endl;
	cout << "-----------------------------------------" << endl;
	cout << "\t\t 1. Insert a Record" << endl;
	cout << "\t\t 2. Search a Record" << endl;
	cout << "\t\t 3. Delete a Record" << endl;
	cout << "\t\t 4. Show All Records"<< endl;
	cout << "\t\t 5. Delete All Records" << endl;
	cout << "\t\t 6. Exit" << endl;
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
					ch = getchar();
					break;
				}
		}
	}

	return 0;
}

