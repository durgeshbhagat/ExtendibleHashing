#include <iostream>
#include <vector>
#include <cmath>
#include<cstdlib>
#include<cstdio>
#include<set>

using namespace std;
class Bucket{
	public:
		//vector<int> entry;
		vector<int> *node;
		int local_depth;
		int cur_size;
		Bucket(int bucketsize){
			node = new vector<int>(0);
			local_depth = log2(bucketsize);
			cur_size = -1;
			//cout << " node size : " << node->size() <<endl; 

		}
};
class HashTable{
	public:
		vector<Bucket*> directory;
		HashTable(int dir_size, int bucket_size){
			for(int i = 0; i<dir_size; i++){
				Bucket* b = new Bucket(bucket_size);
				directory.push_back(b);	
			}
			global_depth = log2(dir_size);
			bucketsize = bucket_size;
		}
		int global_depth;
		int bucketsize;
};
int hashCode(int number, int dir_size) //returns hashKey of a number
{
	int hashKey = number % dir_size;
	return hashKey;
}
int printMenu() {
	//system("clear");
	cout << "\n-----------------------------------------" << endl;
	cout << "Extendible Hashing Implementation." << endl;
	cout << "-----------------------------------------" << endl;
	cout << "\t\t 1. Insert a Record" << endl;
	cout << "\t\t 2. Search a Record" << endl;
	cout << "\t\t 3. Delete a Record" << endl;
	cout << "\t\t 4. Show All Records"<< endl;
	cout << "\t\t 5. Exit" << endl;

	int choice;
	cout << "\nChoice : ";
	cin >> choice;
	return choice;
}

bool isFull(Bucket *b,int bucket_size)
// Return true if bucket full else returns false
{
	if (b->node->size() == bucket_size)
		return true;
	else
		return false;

}

bool isEmpty(Bucket *b)
//Returns true if bucket is empty else returns false
{
	if(b->node->size() ==0)
		return true;
	else
		return false;
}
int search(int value,HashTable h)
{
	int loc=hashCode(value,h.directory.size());
	vector<int> *node=h.directory[loc]->node;
	for(int i=0;i<node->size();i++)
	{
		if((*node)[i]==value)
		{
			cout<<"INFO :: found at location  "<<loc << " and deleted" <<endl;
			return loc;
		}
	}
	cout<<"INFO :: Not Found!!!!";	
	return -1;
}
// Return the postionof Node vector if element found else return -1
int searchNode(int value,vector <int> *node)
{

	for(int i=0;i<node->size();i++)
	{
		if((*node)[i]==value)
		{
			//cout<<value<<"INFO : found in Node at location "<<i<<endl;
			return i;
		}
	}
	//cout<<"INFO ::Not Found in the Node!!";	
	return -1;
}
// Rturn -1 if no image exist otherwise return index of images Bucket
int imageLoc(int orig_loc, int dir_size,int global_depth, int local_depth )
{
	if( local_depth == global_depth)
		return (-1);
	int dir_half_size = dir_size/2, image_loc;
	if(orig_loc < dir_half_size)
		image_loc = orig_loc + dir_half_size;
	else
		image_loc = orig_loc - dir_half_size;
	return image_loc;
}
void print(HashTable &h)
{
	vector<Bucket*> directory=h.directory;
	cout << " ---------------- Printing Hash Table ---------------- " <<endl;
	cout<<"INFO :: DIRECTORY Global Depth : "<<h.global_depth<<endl;
	for(int i=0;i<directory.size();i++){
		Bucket *b=directory[i];
		vector<int> *node=b->node;
		cout<<"Bucket id : " << i<<" local_depth : "<<b->local_depth<<" Bucket Contents : ";		
		if (b->cur_size ==-1) // Escape printing for Mirror Image
		{
			cout << endl;
			continue;
		}
		for(int i=0;i<node->size();i++)
			cout<< (*node)[i] <<"  ";
		cout<<endl;
	}
}

void insertBack(Bucket *b,int value)
{
	b->node->push_back(value);
	//cout << " DEBUG INFO : " << value << " inserted " << endl;

}
void emptyBucket(Bucket *b)
{

	vector<int> *node=b->node;
	node->erase(node->begin(),node->end());
	b->node=node; 
	b->cur_size = -1;
}
int mostSignificantBit(int myInt)
{
	int mask = 1 << 31;
	for(int bitIndex = 31; bitIndex >= 0; bitIndex--)
	{
		if((myInt & mask) != 0)
			return bitIndex;
		mask >>= 1;
	}
	return -1;
}

//void readjustPointers(HashTable &h,set<int> &s){
void reAdjustPointers(HashTable &h,int orig_loc)
{
	vector<Bucket*> directory=h.directory;

	int start=directory.size()/2;
	for(int i=0;i<start;i++){
		if( i!=orig_loc)
		{ int  image_loc = i+ start ; 
			directory[image_loc]->node = directory[i]->node;
			//cout << " DEBUG INFO : original node " << i << " address : " << (directory[i]->node);
			//cout << " DEBUG INFO : Image node : " << image_loc <<" address : "<< (directory[image_loc]->node);
		}

	}
	h.directory=directory;
}
void printNode(vector<int> *v)
{
	for(int i=0;i<v->size();i++)
		cout<<(*v)[i]<<" ";
	cout<<endl;
}
void printDirectory(vector<Bucket*> directory)
{
	for(int i=0;i<directory.size();i++)
	{
		vector<int> *node=directory[i]->node;
		cout<<i<<" "<<directory[i]->local_depth<<":";
		printNode(node);
	}

}
// Doubling Directory and spliting bucket
void insertSplit(HashTable &h,int value)
{
	vector<Bucket*> directory=h.directory;
	int orig_loc=hashCode(value,directory.size());
	int image_loc = orig_loc + directory.size(); 
	int size=directory.size();
	for(int i=0;i<size;i++)
	{
		Bucket* b=new Bucket(h.bucketsize);
		directory.push_back(b);	
	}
	cout<<"INFO : Directory doubled and Bucket Splitted" << endl;
	h.global_depth=log2(directory.size());
	// Re-distributing the keys across the splitted bucket for cur loc
	vector<int> node=*(directory[orig_loc]->node);
	emptyBucket(directory[orig_loc]); // Delete the all the entry from the existing Original Bucket ID 

	//Redistributing  and re-inserting elements of Orginal Bucket between  Image bucket and Original bucket
	for(int i=0;i<node.size();i++)
	{
		int loc =hashCode(node[i],directory.size());
		//cout << " Node element processed : " << node[i] << endl;
		insertBack(directory[loc],node[i]);
		directory[loc]->cur_size +=1;
	}

	// Pushing the new element value
	int loc=hashCode(value,directory.size());
	insertBack(directory[loc],value);
	directory[loc]->cur_size +=1;
	// Increase local depth of Original bucket and Image Bucket ID 

	directory[orig_loc]->local_depth++;
	directory[image_loc]->local_depth++;
	cout<<"INFO : inserted at "<< loc << endl;

	h.directory=directory; // Re-assigning the Directory

	//cout<<"readjusting"<<endl;
	reAdjustPointers(h, orig_loc);
}
// Splitting bucket
void bucketSplit(HashTable &h,int value,int orig_loc)
{
	//cout<<"Location:"<<orig_loc<<endl;
	Bucket* b=h.directory[orig_loc];
	Bucket* nb=new Bucket(h.bucketsize);
	vector<Bucket*> directory=h.directory;
	vector<int> node=*(directory[orig_loc]->node);
	emptyBucket(directory[orig_loc]); // Delete the all the entry from the existing Original Bucket ID 
	// Assign Empty node to image Bucket
	int dir_size = h.directory.size();
	int dir_half_size = dir_size/2;
	int image_loc;
	if (orig_loc < dir_half_size)
	{	image_loc = orig_loc + dir_half_size;
	}
	else
	{	image_loc = orig_loc -dir_half_size ;
	}
	directory[image_loc] = nb;	
	// Reassigning and re-inserting each entry of current loc  
	for(int i=0;i<node.size();i++)
	{
		int loc=hashCode(node[i],directory.size());
		insertBack(directory[loc],node[i]);
		directory[loc]->cur_size +=1;

	}
	// Pushing the new element value
	int loc=hashCode(value,directory.size());
	insertBack(directory[loc],value);
	directory[loc]->cur_size +=1;
	// Increase local depth of Original bucket and Image Bucket ID 
	directory[orig_loc]->local_depth++;
	directory[image_loc]->local_depth++;
	cout<<"INFO : inserted at"<< loc << endl;

	h.directory=directory;

}
void insert(int value,HashTable &h)
{
	vector<Bucket*> directory=h.directory;
	int bucket_size =h.bucketsize;
	int dir_size = directory.size();
	int loc=hashCode(value,directory.size());
	int loc_node = searchNode(value,h.directory[loc]->node);
	if (loc_node !=-1)
	{
		cout << "WARNING :: Value : " << value << " is present in bucket ID : " << loc << " at postion : " << loc_node << " . Not Added !" << endl;
		return;
	} 
	//cout<<"DEBUG_INFO : Location : "<<loc<<endl;
	if(isFull(directory[loc],bucket_size))
	{
		cout<<"INFO : Bucket ID :  " << loc << " is Full "<<endl;
		int local_depth=directory[loc]->local_depth,global_depth=h.global_depth;
		if(local_depth==global_depth) //Splitting bucket & Double Directory
		{
			cout<<"INFO : Splitting the Bucket and Doubling the Directory "<<endl;
			insertSplit(h,value);
		}
		else if(local_depth<global_depth)
		{
			cout<<"INFO  : Splitting bucket "<<endl;
			bucketSplit(h,value,loc);
		}
		else
		{
			cout<<" WARNING : : local depth > global depth : Exiting the PROGRAM";
			exit(0);
		}	
	}
	else
	{
		cout<<"INFO : Normal Insertion --"<<endl;
		insertBack(directory[loc],value);
		cout << "INFO : Inserted at " << loc << endl ;
		int dir_half_size = dir_size /2;
		if(directory[loc]->local_depth == h.global_depth || loc < dir_half_size )
			directory[loc]->cur_size +=1;
		else
		{	int image_loc;
			image_loc = loc - dir_half_size;  
			//int loc=hashCode(value,d);
			//cout << " loc : " << loc << " Image loc "<< image_loc << endl;
			directory[image_loc]->cur_size +=1 ;
		}
	}
}

// Lazy deletetion
void deleteVal(int value,HashTable &h)
{
	int orig_loc=search(value,h);
	int loc_node = searchNode(value,h.directory[orig_loc]->node);
	int image_loc = imageLoc(orig_loc, h.directory.size(),h.global_depth,h.directory[orig_loc]->local_depth);
	if(loc_node>=0)
	{
		vector<int> *node=h.directory[orig_loc]->node;
		
		node->erase(node->begin() +loc_node);
		// Updating cur pointer 
		if (h.directory[orig_loc]->local_depth == h.global_depth || image_loc ==-1)
		{	h.directory[orig_loc]->cur_size -=1;
			//return;
		}
		else
		{
			if(h.directory[orig_loc]->cur_size ==-1)
			{
				h.directory[image_loc]->cur_size -=1;
				//h.directory[image_loc]->local_depth -=1;
			}		
			else
			{
				h.directory[orig_loc]->cur_size -=1;
				//h.directory[orig_loc]->local_depth -=1;
			}
		}
		h.directory[orig_loc]->node=node;
		// Bucket Deletion 
		if(isEmpty(h.directory[orig_loc])) // Delete Bucket and Re-map node to mirror image
		{	cout <<"DEBUG INFO : Bucket ID " << image_loc << " completely Empty " << endl;	
			h.directory[orig_loc]->local_depth -=1;
			image_loc = imageLoc(orig_loc, h.directory.size(),h.global_depth,h.directory[orig_loc]->local_depth);
			h.directory[orig_loc]->node = h.directory[image_loc]->node;
			h.directory[image_loc]->local_depth -=1;
			//h.directory[
		} 
		
	}
}

int main() 
{
	// your code goes here
	int dir_size,bucket_size,value;
	cout<<"Enter the intital directory size (Power of 2) : ";
	cin>>dir_size;
	cout<<"Enter the bucket size : ";
	cin >>bucket_size;
	//bucket_size=dir_size;
	HashTable h(dir_size,bucket_size);
	while(true) 
	{
		int choice = printMenu();
		char ch = getchar();  // eat newline
		switch(choice)
		{
			case 1:   // Insert a record
				{
					cout << "Enter value to be added : ";
					cin >> value;
					insert(value,h);
					break;
				}

			case 2:   // Search a record
				{
					cout << "Enter value to be search :  ";
					cin >> value;
					search(value,h);
					break;
				}
			case 3: // delete data
				{
					cout << "Enter value to be deleted : " ;
					cin>>value;
					deleteVal(value,h);
					break;
				}

			case 4:   // show All Records
				{
					print(h);
					break;
				}
			case 5:
				exit(0);
		}
	}
	return 0;
}
