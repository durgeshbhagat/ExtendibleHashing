#include <iostream>
#include <vector>
#include <cmath>
#include <cstdlib>
#include <cstdio>
#include <set>
#include <fstream>
#include <string>
#include <sstream>


using namespace std;
class Bucket{
	public:
		vector<int> node;
		vector<int> overflow_page;
		int local_depth;
		int bucket_size;
		
		Bucket(int bucketsize,int localdepth){
			//node = new vector<int>(0);
			//overflow_page = new vector<int>(0);
			local_depth = localdepth;
			bucket_size = bucketsize;
			//cout << " node size : " << node->size() <<endl; 

		}
};
class HashTable{
	public:
		int global_depth;
		int bucket_size;
		int overflow_flag;
		vector<Bucket*> directory;
		HashTable(int dir_size, int bucketsize, int overflowflag)
		{
			global_depth = log2(dir_size);
			bucket_size = bucketsize;
			for(int i = 0; i<dir_size; i++){
				Bucket* b = new Bucket(bucketsize, global_depth);
				directory.push_back(b);	
			}
			overflow_flag = overflowflag;

		}

};

int hashCode(int number, int dir_size) //returns hashKey of a number
{
	int hashKey = number % dir_size;
	return hashKey;
}

bool isFull(Bucket *b, int overflow_option)
	// Return true if bucket full else returns false
{
	if (overflow_option ==0)
	{
		if (b->node.size() == b->bucket_size)
			return true;
		else
			return false;
	}
	else
	{
		if (b->node.size() == b->bucket_size && b->overflow_page.size() ==b->bucket_size)
			return true;
		else
			return false;

	}
}

void print(HashTable &h)
{
	vector<Bucket*> directory=h.directory;
	int dir_size = directory.size();
	int dir_half_size = dir_size/2;
	cout << " ---------------- Printing Hash Table ---------------- " <<endl;
	cout<<"INFO :: DIRECTORY Global Depth : "<<h.global_depth<<endl;
	cout << "------------------------------------------------" << endl;
	// Printing Directory and Bucket Mapping
	cout << "Directory slot | Bucket Pointer" << endl;	
	for(int i=0;i<dir_size;i++)
	{
		cout << i << " |" << i << endl;
	}
	cout << "------------------------------------------------" << endl;
	// Printing Bucket and over flow pages contents
	cout << "------------------------------------------------" << endl;
	cout<<"Bucket id | " <<" Contents | "<<" Overflow Pages | " << endl;
	for(int i=0;i<dir_size;i++){
		Bucket *b=directory[i];
		vector<int> node=b->node;
		int node_size = node.size();
		//cout<<"Bucket id : " << i<<" local_depth : "<<b->local_depth<<endl; //" Bucket Contents : ";
		cout <<  i << "     \t| ";		
		if (i>=dir_half_size && h.global_depth != b->local_depth) // Escape printing for Mirror Image
		{
			cout <<" \t|  Mirror Image |" << "  Mirror Image" << endl;
			continue;
		}
		else if(node_size ==0)
		{	
			cout <<"   Empty   |" << " No Overflow Page" << endl;
			continue;
		}
		for(int j=0;j<node.size();j++)
			cout <<" " << node[j] ; 
		cout << " \t" ;
		// Printing Overflow Contents
		if (h.overflow_flag==0)
			cout<<"| \tNo overflow page" <<endl;
		else
		{	if(b->overflow_page.size() == 0)
			cout<<"| \tNo overflow page" <<endl;
			else
			{	
				vector<int> node=b->overflow_page;
				for(int j=0;j<node.size();j++)
					cout << "|\t" << node[j] << "\t" ; 
			}

		}
		cout<<endl;
	}
	cout << "------------------------------------------------" << endl;
}


void insertBack(Bucket *b,int value, int overflow_option)
{
	if (b->node.size()< b->bucket_size)
	{	b->node.push_back(value);
			return;
	}	
	
	else if(overflow_option==1)
	{	b->overflow_page.push_back(value);
		return;
	}
	
	//cout << " DEBUG INFO : " << value << " inserted " << endl;

}


void insert(int value,HashTable &h)
{
	vector<Bucket*> directory=h.directory;
	int bucket_size =h.bucket_size;
	int dir_size = directory.size();
	cout << " DEBUG: dir_size" << dir_size <<endl;
	int loc=hashCode(value,directory.size());
	//int loc_node = searchNode(value,h.directory[loc]->node);
	
	if(isFull(directory[loc],h.overflow_flag))
	{
		return;
	}
	else
	{
		cout<<"INFO : Normal Insertion --;  ";
		insertBack(directory[loc],value, h.overflow_flag);
		cout << "INFO : Inserted at Bucket ID : " << loc << endl ;
		int dir_half_size = dir_size /2;
		
	}
}

int main ( int argc, char *argv[] )
{
	int i;
	ifstream fin;
	if (argc<5)
	{
		cout <<" USAGE : arguements less than 4" << endl;
		exit(0);
	} 
	else
	{
		for (i=0;i<argc; i++)
		{
			cout << " Arg " << i << " " << argv[i] << "\t";
		}
		cout << endl;
		//exit(0);
	}

	// your code goes here
	int dir_size,bucket_size,value,  overflow_option,count=0;
	dir_size = pow(2,atoi(argv[1]));
	bucket_size = atoi(argv[2]);
	overflow_option = atoi(argv[3]);
	//cout << " Dir size : " << dir_size << endl;
	//cout << " Bucket size : " << bucket_size << endl;
	cout << " Over flow option : " << overflow_option << endl;
	fin.open(argv[4]);
	string line,line1, command;
	HashTable h(dir_size,bucket_size, overflow_option);
	//cout << " Intial global_depth : " << h.global_depth << endl;
	//cout << " Intial bucket size : " << h.bucket_size << endl;
	while(getline(fin, line))
	{
		//cout <<" line : " << line << endl; 
		stringstream ss(line);
		//cout << "printing File : " <<endl;
		count=0;
		while(getline(ss, line1, ' '))
		{	
			count++;
			if (count==1)
				command = line1;
			else if(count==2)
			{
				value = stoi(line1) ;
				//cout << " value ::"<< value<<";"<<endl;;
			}
			else
				break;
		}
		//cout << "Command : "  << command << ",value :  " << value << endl;
		//cout << endl;
		ss.clear();

		if(!command.compare("insert"))  // Insert a record
		{
			insert(value,h);

		}
		/*
		if(!command.compare("search"))   // Search a record
		{

			search(value,h);

		}
		if(!command.compare("delete"))  // delete data
		{

			deleteVal(value,h);

		}
		*/
		if(!command.compare("status"))   // show All Records
		{
			print(h);

		}


	}
	return 0;
}
