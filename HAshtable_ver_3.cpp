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
		//vector<int> entry;
		vector<int> *node;
		vector<int> *overflow_page;
		int local_depth;
		int cur_size;
		Bucket(int bucketsize,int localdepth){
			node = new vector<int>(0);
			overflow_page = new vector<int>(0);
			local_depth = localdepth;
			cur_size = -1;
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


bool isFull(Bucket *b,int bucket_size, int overflow_option)
	// Return true if bucket full else returns false
{
	if (overflow_option ==0)
	{
		if (b->node->size() == bucket_size)
			return true;
		else
			return false;
	}
	else
	{
		if (b->node->size() == bucket_size && b->overflow_page->size() ==bucket_size)
			return true;
		else
			return false;

	}
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
// Return -1 if no image exist otherwise return index of images Bucket
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
	cout << "------------------------------------------------" << endl;
	cout << "Directory slot | Bucket Pointer" << endl;	
	for(int i=0;i<directory.size();i++)
	{
		cout << i << " |" << i << endl;
	}
	cout << "------------------------------------------------" << endl;
	cout << "------------------------------------------------" << endl;
	cout<<"Bucket id | " <<" Contents | "<<" Overflow Pages | " << endl;
	for(int i=0;i<directory.size();i++){
		Bucket *b=directory[i];
		vector<int> *node=b->node;
		//cout<<"Bucket id : " << i<<" local_depth : "<<b->local_depth<<" Bucket Contents : ";
		cout <<  i << " ";		
		if (b->cur_size ==-1) // Escape printing for Mirror Image
		{
			cout <<" \t| \tEmpty \t|" << " No Overflow Page" << endl;
			continue;
		}
		for(int j=0;j<node->size();j++)
			cout <<" \t|\t" << (*node)[j] ; 
		cout << " \t" ;
		if (h.overflow_flag==0)
			cout<<"| \tNo overflow page" <<endl;
		else
		{	if(b->overflow_page->size() == 0)
			cout<<"| \tNo overflow page" <<endl;
			else
			{	
				vector<int> *node=b->overflow_page;
				for(int i=0;i<node->size();i++)
					cout << "|\t" << (*node)[i] << "\t" ; 
			}

		}
		cout<<endl;
	}
	cout << "------------------------------------------------" << endl;
}
void emptyBucket(Bucket *b)
{

	vector<int> *node=b->node;
	vector<int> *overflownode = b->overflow_page;
	node->erase(node->begin(),node->end());
	//emptying overflow_page
	overflownode->erase(overflownode->begin(),overflownode->end());
	b->node=node;
	b->overflow_page=overflownode; 
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
			directory[image_loc]->overflow_page = directory[i]->overflow_page;
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

void insertBack(Bucket *b,int value,int bucket_size, int overflow_option)
{
	if(overflow_option==0)
	{	b->node->push_back(value);
		return;
	}
	else
	{
		if (b->node->size()==bucket_size)
		{	b->overflow_page->push_back(value);
			return;
		}
		else
		{
			b->node->push_back(value);
			//emptyBucket(b->overflow_page);
			return;
		}
	}
	//cout << " DEBUG INFO : " << value << " inserted " << endl;

}
// Doubling Directory and spliting bucket
void insertSplit(HashTable &h,int value)
{
	vector<Bucket*> directory=h.directory;
	int orig_loc=hashCode(value,directory.size());
	int image_loc = orig_loc + directory.size()/2; 
	int size=directory.size();
	for(int i=0;i<size;i++)
	{
		Bucket* b=new Bucket(h.bucket_size,h.directory[orig_loc]->local_depth);
		directory.push_back(b);	
	}
	cout<<"INFO : Directory doubled and Bucket Splitted" << endl;
	h.global_depth=log2(directory.size());
	// Re-distributing the keys across the splitted bucket for cur loc
	vector<int> node=*(directory[orig_loc]->node);
	vector<int> overflow_node = *(directory[orig_loc]->overflow_page);
	emptyBucket(directory[orig_loc]); // Delete the all the entry from the existing Original Bucket ID 
	//emptyBucket(directory[orig_loc]->overflow_page);
	//Redistributing  and re-inserting elements of Orginal Bucket between  Image bucket and Original bucket
	for(int i=0;i<node.size();i++)
	{
		int loc =hashCode(node[i],directory.size());
		//cout << " Node element processed : " << node[i] << endl;
		insertBack(directory[loc],node[i],h.bucket_size, h.overflow_flag);
		directory[loc]->cur_size +=1;
	}
	for(int i=0;i<overflow_node.size();i++)
	{
		int loc =hashCode(overflow_node[i],directory.size());
		//cout << " Node element processed : " << node[i] << endl;
		insertBack(directory[loc],overflow_node[i],h.bucket_size, h.overflow_flag);
		//directory[loc]->cur_size +=1;
	}
	//Bucket *b;
	//vector<int> *overflownode=b->overflow_page;
	//overflow_node->erase(overflow_node->begin(),overflow_node->end());
	// Pushing the new element value
	int loc=hashCode(value,directory.size());
	insertBack(directory[loc],value,h.bucket_size, h.overflow_flag);
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
	Bucket* nb=new Bucket(h.bucket_size,h.directory[orig_loc]->local_depth);
	vector<Bucket*> directory=h.directory;
	vector<int> node=*(directory[orig_loc]->node);
	vector<int> overflow_node = *(directory[orig_loc]->overflow_page);
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
		insertBack(directory[loc],node[i],h.bucket_size, h.overflow_flag);
		directory[loc]->cur_size +=1;

	}
	for(int i=0;i<overflow_node.size();i++)
	{
		int loc =hashCode(overflow_node[i],directory.size());
		//cout << " Node element processed : " << node[i] << endl;
		insertBack(directory[loc],overflow_node[i],h.bucket_size, h.overflow_flag);
		//directory[loc]->cur_size +=1;
	}
	// Pushing the new element value
	int loc=hashCode(value,directory.size());
	insertBack(directory[loc],value,h.bucket_size, h.overflow_flag);
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
	int bucket_size =h.bucket_size;
	int dir_size = directory.size();
	cout << " DEBUG: dir_size" << dir_size <<endl;
	int loc=hashCode(value,directory.size());
	int loc_node = searchNode(value,h.directory[loc]->node);
	/*if (loc_node !=-1)
	  {
	  cout << "WARNING :: Value : " << value << " is present in bucket ID : " << loc << " at postion : " << loc_node << " . Not Added !" << endl;
	  return;
	  } */
	//cout<<"DEBUG_INFO : Location : "<<loc<<endl;
	if(isFull(directory[loc],bucket_size,h.overflow_flag))
	{
		cout<<"INFO : Bucket ID :  " << loc << " is Full "<<endl;
		int local_depth=directory[loc]->local_depth,global_depth=h.global_depth;
		if(local_depth==global_depth) //Splitting bucket & Double Directory
		{
			cout << "INFO : Splitting the Bucket and Doubling the Directory "<<endl;
			insertSplit(h,value);
		}
		else if(local_depth<global_depth)
		{
			cout << "INFO  : Splitting bucket "<<endl;
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
		cout<<"INFO : Normal Insertion --;  ";
		insertBack(directory[loc],value,h.bucket_size, h.overflow_flag);
		cout << "INFO : Inserted at Bucket ID : " << loc << endl ;
		int dir_half_size = dir_size /2;
		cout <<" DEBUG INFO : global depth :  " << h.global_depth << " local_depth : " << directory[loc]->local_depth << endl; 
		if(directory[loc]->local_depth == h.global_depth )
			directory[loc]->cur_size +=1;
		else
		{	int image_loc;
			image_loc = loc - dir_half_size;  
			//int loc=hashCode(value,d);
			cout << "DEBUG INFO IMAGE loc : " << loc << " Image loc "<< image_loc << endl;
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
		{	//cout <<"DEBUG INFO : Bucket ID " << image_loc << " completely Empty " << endl;	
			h.directory[orig_loc]->local_depth -=1;
			image_loc = imageLoc(orig_loc, h.directory.size(),h.global_depth,h.directory[orig_loc]->local_depth);
			h.directory[orig_loc]->node = h.directory[image_loc]->node;
			h.directory[image_loc]->local_depth -=1;
			//h.directory[
		} 

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
	//cout << " Dir size : " << bucket_size << endl;
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

		if(!command.compare("search"))   // Search a record
		{

			search(value,h);

		}
		if(!command.compare("delete"))  // delete data
		{

			deleteVal(value,h);

		}

		if(!command.compare("status"))   // show All Records
		{
			print(h);

		}


	}
	return 0;
}
