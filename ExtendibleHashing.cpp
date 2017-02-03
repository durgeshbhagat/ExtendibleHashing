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

int hashCode(int number, int bucket_size) //returns hashKey of a number
{
	int hashKey = number % bucket_size;
	return hashKey;
}

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
		//A = (int *) malloc(sizeof(int) *size);
		A = new int [size];
        }
        ~Bucket()
        {
            delete A;
        }
 };       
        void insert(int value)
        {
                
		int hashKey = hashCode(value, max_size); // calculates hash key of value
		int posDir = findPos(hashKey); //gets the pos of directory
						//here we need to code related to bucket of that directory pos.
		if (cur_size < max_size-1)
                {
                    cur_size +=1;
                    A[cur_size] = value;
                }
		if (cur_size == max_size-1)
		{
			Bucket *orinigalBucket, *imageBucket;
			Directory *dir;
			if (dir.global_depth > originalBucket.local_depth)
			{
				for (int i=0; i <= originalBucket.cur_size; i++)
				{
					hashKey = hashCode(originalBucket[i], max_size);
					if(originalBucket.local_depth == hashKey)
					{
						originalBucket.A[++cur_size] = originalBucket.A[i];
					}
					else
						imageBucket.A[++cur_size] = originalBucket.A[i];
				}
					originalBucket.local_depth += 1;
					imageBucket.local_depth +=1; 
			}
			else //dir.global_depth == originalBucket.local_depth
			{
				
				for (int i=0; i <= originalBucket.cur_size; i++)
				{
					hashKey = hashCode(originalBucket[i], max_size);
					if(originalBucket.local_depth == hashKey)
					{
						originalBucket.A[++cur_size] = originalBucket.A[i];
					}
					else
						imageBucket.A[++cur_size] = originalBucket.A[i];
				}
					originalBucket.local_depth += 1;
					imageBucket.local_depth +=1; 
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

