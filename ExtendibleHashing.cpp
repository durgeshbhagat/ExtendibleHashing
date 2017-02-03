#include<cstdio>
#include<iostream>
#include<cstdlib>
//#include <array>

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

class Directory
/* 

*/ Directory Pages
{  int global_depth;
   Bucket *D; // Dynamic Bucket array
   public:
        Directory(int size)
        {
        }
        ~Directory()
        {
        }
        void search_key(int key);
        void add_key(int key);
        void remove_key(int key);
        void double_directory();
        void status_directory();

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
            local_depth = 0; //Initially
            cur_size =-1;
            //A = (int *) malloc(sizeof(int) *size);
            A = new int [size];
        }
        ~Bucket()
        {
            delete[] A;
        }
        void insert(int);
        void remove(int);
        void removeAll();
        bool isbucketEmpty();
        void print();
};       
void Bucket :: insert(int value)
{

	//int hashKey = hashCode(value, max_size); // calculates hash key of value
	//int posDir = findPos(hashKey); //gets the pos of directory
	//here we need to code related to bucket of that directory pos.
	if (cur_size < max_size-1)
	{
		cur_size +=1;
		A[cur_size] = value;
        //cout << " Cur size : " << cur_size << " Max size: " << max_size << endl; 
	}
	else
		cout << " \t Error : Bucket Overflow " << endl;
	/*
	   if (cur_size == max_size-1)//if cur_size == bucket_size ;means bucket is full
	   {
	   Bucket *orinigalBucket, *imageBucket;
	   Directory *dir;
	   if (dir.global_depth > originalBucket.local_depth)
	   {
	   for (int i=0; i <= originalBucket.cur_size; i++) // we have to calculate hashKey of all values in original bucket for distribution
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
	//splitting directory code here
	}



	}*/
}
void Bucket :: remove(int value)
{ 
	//int hashKey = hashCode(value, max_size);
	//int posDir = findPos(hashKey);
	//Directory *dir;
	//Bucket *bucket;
	if(!isbucketEmpty())
	{
		for(int i = 0; i <= cur_size; i++)
		{
			if(A[i] == value)
				//swap(bucket.A[i],bucket.A[cur_size]);
			{
				int temp  = A[i];
				A[i] = A[cur_size];
				A[cur_size] = temp;
			}
		}
		cur_size -= 1;//just decrease cur_size without deleting value
		if(cur_size == -1)
			cout << "Merge bucket with imagebucket" << endl;
	}
	else
		cout << "Elt is not found" << endl;

}
bool Bucket :: isbucketEmpty()
{
	//if (bucket.cur_size == -1)
	return cur_size == -1;
}
void Bucket :: removeAll()
{
	cur_size = -1;	
	delete[] A;
}
void Bucket :: print()
{	
	int i;
	//cout << "-----------------------------------------" << endl;
    cout << " \n Bucket cur size : " << cur_size << " Bucket max size :  " << max_size << endl ;
	cout << "\n--------Printing Bucket----" << endl;
	for(i=0;i<=cur_size; i++)
		cout << A[i] << "\t";
	cout << "\n--------End of Bucket---" << endl;     
}

int printMenu() {
	//system("clear");
	cout << "\n-----------------------------------------" << endl;
	cout << "Extendible Hashing Implementation." << endl;
	cout << "-----------------------------------------" << endl;
	cout << "\t\t 1. Insert a Record" << endl;
	//cout << "\t\t 2. Search a Record" << endl;
	cout << "\t\t 2. Delete a Record" << endl;
	cout << "\t\t 3. Delete All Data"<< endl;
	cout << "\t\t 4. Show All Records" << endl;
	cout << "\t\t 5. Exit" << endl;
	int choice;
	cout << "\nChoice : ";
	cin >> choice;
	//cout.flush();
	return choice;
}

int main()
{
    int n;
    int value;
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
			case 2: // delete data
				{
					cout << "Enter value to be deleted" << endl;
					cin >> value;
					B->remove(value);
					break;
				}
			case 3: // delete all data
				B->removeAll();
				break;

			case 4:   // show All Records
					B->print();
					break;
			
			case 5:
				exit(0);
		}
	}

	return 0;
}

