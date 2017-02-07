#include<cstdio>
#include<iostream>
#include<cstdlib>
#include <cmath>
//#include <array>

using namespace std;

// Single block structure for LinkList
struct node
{
	int data;
	node *next;
};

int hashCode(int number, int dir_size) //returns hashKey of a number
{
    //cout << " Line 18 : ";
    //cout << "key :" << number << " dir_size : " << dir_size << endl;
    int hashKey = number % dir_size;
    //cout << "hashkey :: " << hashKey << endl;
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
		this->max_size = size;
		this->local_depth = 0; //Initially
		this->cur_size =-1;
		this->A = (int *) malloc(sizeof(int) *size);
        cout << "this ->A :  " <<this->A <<  "  this->cur_size: " << this->cur_size << " this->max_size  : " << this->max_size << endl; 
		//this->A = new int[size];
	}
	~Bucket()
	{
		delete[] A;
	}
	void insert(int);
	int search(int);
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
    cout << " this->cur_size : " << this->cur_size <<" \t this->max_size : " << this->max_size << " \t this->A : " << this->A<< endl; 
	if (this->cur_size < this->max_size-1)
	{
		this->cur_size +=1;
		this->A[this->cur_size] = value;
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

int Bucket :: search(int value)
{
	bool found_flag=false;
	int i =0;
	for(i=0;i<=this->cur_size;i++)
	{    if( this->A[i] == value)
		{
			found_flag=true;
			break;
		}
	}
	if(found_flag)
	{
		cout <<" \n Key :" << value << " found at pos : " << i << endl; 
		return (i);
	}
	else
	{  
		cout <<" \n key : " << value << " not found " << endl;
		return (-1);
	}
}

void Bucket :: remove(int value)
{ 
	//int hashKey = hashCode(value, max_size);
	//int posDir = findPos(hashKey);
	//Directory *dir;
	//Bucket *bucket;
	int pos;
	pos =search(value);
	if (pos==-1)
	{
		cout << "\n Element :" << value << " not found" << endl;
	}
	else
	{

		int temp  = this->A[pos];
		this->A[pos] = this->A[this->cur_size];
		this->A[this->cur_size] = temp;
		this->cur_size -=1 ;
	}

}
bool Bucket :: isbucketEmpty()
{
	//if (bucket->cur_size == -1)
	return this->cur_size == -1;
}
void Bucket :: removeAll()
{
	this->cur_size = -1;	
	//delete[] A;
}
void Bucket :: print()
{	
	int i;
	//cout << "-----------------------------------------" << endl;
	cout << " \t Bucket cur size : " << cur_size << " Bucket max size :  " << max_size << endl ;
	cout << "\t\t--------Printing Bucket----" << endl;
    cout << "\t\t";
	for(i=0;i<=this->cur_size; i++)
		cout  << this->A[i] << "\t";
	cout << "\n\t\t--------End of Bucket---" << endl;     
}

class Directory
/* 
   Directory Pages
 */
{  	
	Bucket *D; // Dynamic Bucket array
	int dir_size;//No of of buckets in a direcory
	
	public:
		int global_depth;
        int i;
        //int dir_size;
		Directory(int dir_size,int bucket_size) 
		{
            this->dir_size = dir_size;
			global_depth = log2(dir_size);
			D = (Bucket *)malloc(sizeof(Bucket)*dir_size);
            for (i=0;i<dir_size;i++)
                D[i]=Bucket(bucket_size);
		}
		~Directory()
		{
			            
            		//delete[] D;
		}
		void search_key(int key);
		void add_key(int key);
		void remove_key(int key);
		void double_directory();
		void status_directory();

};

void Directory :: status_directory()
{
    int i,j;
    for (int i=0;i<dir_size;i++)
    {
        cout << "Printing Dir :" << i <<endl;
        D[i].print(); 
    }
}
void Directory :: search_key(int key)
{
	
	int hashKey = hashCode(key,dir_size);
	Bucket bucket = D[hashKey];
	bucket.search(key);
		
}
void Directory :: add_key(int key)
{
    cout << " Line 227 " <<endl;
     int size = this->dir_size;
	int hashKey = hashCode(key, size);
	//Bucket bucket = D[hashKey];
	//D[hashKey] = D->insert(key);
    //cout << " Line 230 ::"  << endl;
	D[hashKey].insert(key);
    //cout << "Line 231 ::" << endl;
}

int printMenu() {
	//system("clear");
	cout << "\n-----------------------------------------" << endl;
	cout << "Extendible Hashing Implementation." << endl;
	cout << "-----------------------------------------" << endl;
	cout << "\t\t 1. Insert a Record" << endl;
	cout << "\t\t 2. Search a Record" << endl;
	cout << "\t\t 3. Delete a Record" << endl;
	cout << "\t\t 4. Delete All Data"<< endl;
	cout << "\t\t 5. Show All Records" << endl;
	cout << "\t\t 6. Exit" << endl;
	int choice;
	cout << "\nChoice : ";
	cin >> choice;
	//cout.flush();
	return choice;
}

int main()
{
	int dir_size, bucket_size;
	int value,index,i;
	char ch;
	cout << "Enter Directory-size : ";
	cin >> dir_size;
    cout << " \n Enter the bucket size : " ;
    cin >> bucket_size;
	//Directory *B = new Directory(dir_size,bucket_size);//segmentation fault occurs
	Bucket **D;

    D = (Bucket **)malloc(sizeof(Bucket *)*dir_size);
    for (i=0;i<dir_size;i++){
        D[i] = (Bucket *)new Bucket(bucket_size);
    }
    
	while(true) {
		int choice = printMenu();
		ch = getchar();  // eat newline
		switch(choice) {
			case 1:   // Insert a record
				{

					cout << "Enter value to be added  and index of the D  ";
					cin >> value>>index;
					//B->insert(value);
					D[index]->insert(value);
					break;
				}

			case 2:   // Search a record
				{

					cout << "Enter value to be searched :nd the index of the D ";
					cin >> value >> index;
					//B->search(value);
					D[index]->search(value);
					break;
				}
			case 3: // delete data
				{
					cout << "Enter value to be deleted and the index of the D: " << endl;
					cin >> value >> index;
					D[index]->remove(value);
					break;
				}
			case 4: // delete all data
				{
                    cout << " Enter the index of D to be deleted all data : " << endl ;
                    cin >> index;
					D[index]->removeAll();
					break;
				}
			case 5:   // show All Records
                    //B->status_directory();
                    cout<< " Enter the index of D to be displayed : " ;
                    cin >> index;
                    D[index]->print();
				break;

			case 6:
				exit(0);
		}
	}
   
	return 0;
}

