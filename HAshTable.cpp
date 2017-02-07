#include <iostream>
#include <vector>
#include <cmath>
#include<cstdlib>
#include<cstdio>
#include<set>
using namespace std;
class Bucket{
	public:
	vector<int> *node;
	int localdepth;
	int cur_size;
	Bucket(int bucketsize){
		node = (node *)malloc(sizeof(node));
		localdepth=log2(bucketsize);
		cur_size = -1;
		cout << " node size : " << node->size() <<endl; 
		/*for(int i=0;i<bucketsize;i++){
			node.push_back(-1);
		}*/
	}
};
class HashTable{
	public:
	vector<Bucket*> directory;
	HashTable(int dir_size, int bucket_size){
		for(int i=0;i<dir_size;i++){
			Bucket* b=new Bucket(bucket_size);
			directory.push_back(b);	
		}
		globaldepth=log2(dir_size);
		bucketsize=bucket_size;
	}
	int globaldepth;
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
	cout << "\t\t 4. Delete All Data"<< endl;
	cout << "\t\t 5. Show All Records" << endl;
	cout << "\t\t 6. Exit" << endl;
	int choice;
	cout << "\nChoice : ";
	cin >> choice;
	//cout.flush();
	return choice;
}
bool isFull(Bucket *b,int bucket_size)
// Return 0 if bucket full else returns the size of bucket
{	
	cout << " the size of Bucket is  : " << endl;
	vector<int> *node=b->node;
	cout << " the size of Bucket is 2  : " << endl;
        int size = node->size();
	cout << " the size of Bucket is 3  : " << endl;
	cout << " the size of Bucket is  : " << size << endl;
        if (size == bucket_size)
		return true;
	else
		return false;
        /*
	for(int i=0;i<node.size();i++){
		if(node[i]==-1){
		return false;
		}
	}
	return true;
	*/
}
void print(HashTable &h){
	vector<Bucket*> directory=h.directory;
        cout << " ---------------- Printing Hash Table ---------------- " <<endl;
	cout<<"INFO :: DIRECTORY Global Depth : "<<h.globaldepth<<endl;
	for(int i=0;i<directory.size();i++){
		Bucket *b=directory[i];
		vector<int> *node=b->node;
		cout<<"Bucket id : " << i<<" local_depth : "<<b->localdepth<<" Bucket Contents : ";
		for(int i=0;i<node->size();i++){
			cout<< (*node)[i] <<"  ";


		}
		cout<<endl;
	}
}

void insertback(Bucket *b,int value){
	/*vector<int> node=b->node;
        int node_size = node.size();
        cout << " node_size : " << node_size << endl ;
        node.push_back(value);*/
        b->node->push_back(value);
        /*
	for(int i=0;i<node.size();i++){
		if(node[i]==-1){
			node[i]=value;
			b->node=node;
			return;
		}
	}*/
	//cout<<" WARNING : Already Full! in Insert Back , Exiting the PROGRAM " << endl;
	//exit(0);
}
void emptybucket(Bucket *b){
	
	vector<int> *node=b->node;
	node->erase(node->begin(),node->end());

	b->node=node; 
}
int mostSignificantBit(int myInt){
  int mask = 1 << 31;
  for(int bitIndex = 31; bitIndex >= 0; bitIndex--){
    if((myInt & mask) != 0){
      return bitIndex;
    }
    mask >>= 1;
  }
  return -1;
}

//void readjustPointers(HashTable &h,set<int> &s){
void reAdjustPointers(HashTable &h,int orig_loc){
	vector<Bucket*> directory=h.directory;

	int start=directory.size()/2;
	for(int i=0;i<start;i++){
		if( i!=orig_loc)
		{ int  image_loc = i+ start ; 
		  (directory[image_loc]->node) = (directory[i]->node) ;
          cout << " original node : " << (directory[i]->node);
          cout << " Image node : " << (directory[image_loc]->node);
	    }
		/*
		if(s.find(i)==s.end()){
			int bitindex=mostSignificantBit(i);
			int val=1<<bitindex;
			int f=val^i;
			cout<<bitindex<<" "<<f<<endl;
			directory[i]=directory[f];
		}*/
	}
	h.directory=directory;
}
void printNode(vector<int> *v){
	for(int i=0;i<v->size();i++){
		cout<<(*v)[i]<<" ";
	}
	cout<<endl;
}
void printDirectory(vector<Bucket*> directory){
	for(int i=0;i<directory.size();i++){
		vector<int> *node=directory[i]->node;
		cout<<i<<" "<<directory[i]->localdepth<<":";
		printNode(node);
	}
	
}
void insertSplit(HashTable &h,int value){
	vector<Bucket*> directory=h.directory;
	int orig_loc=hashCode(value,directory.size());
	int image_loc = orig_loc + directory.size(); 
	int size=directory.size();
	for(int i=0;i<size;i++){
		Bucket* b=new Bucket(h.bucketsize);
		directory.push_back(b);	
	}
	cout<<"DEBUG : Directory doubled" << endl;
	h.globaldepth=log2(directory.size());
        // Re-distributing the keys across the splitted bucket for cur loc
	vector<int> *node=directory[orig_loc]->node;
	emptybucket(directory[orig_loc]); // Delete the all the entry from the existing Original Bucket ID 
	//printDirectory(directory);
	//printNode(node);
       
	//set<int> s;
        //Redistributing  and re-inserting elements of Orginal Bucket between  Image bucket and Original bucket
	cout << " Node size : " << node->size() << endl ;
	for(int i=0;i<node->size();i++){
		int loc =hashCode((*node)[i],directory.size());
		/*if(s.find(loc)==s.end()){
			s.insert(loc);
		}*/
		insertback(directory[loc],(*node)[i]);
		directory[loc]->cur_size +=1;
	}
	// Pushing the new element value
	int loc=hashCode(value,directory.size());
	insertback(directory[loc],value);

        // Increase local depth of Original bucket and Image Bucket ID 
	directory[orig_loc]->localdepth++;
	directory[image_loc]->localdepth++;
	cout<<"inserted"<<endl;
	/*if(s.size()>2){
		cout<<"More than two buckets formed!!!";
		exit(0);
	}
	else{
		cout<<"Incrementing local depth"<<endl;
		for(set<int>::iterator it=s.begin();it!=s.end();it++){
			int loc=*it;
			directory[loc]->localdepth++;
		}
	}
        */
	h.directory=directory; // Re-assigning the Directory
	//print(h);
	//cout<<"readjusting"<<endl;
	reAdjustPointers(h, orig_loc);
}
void bucketSplit(HashTable &h,int value,int loc){
	cout<<"Location:"<<loc<<endl;
	Bucket* b=h.directory[loc];
	Bucket* nb=new Bucket(h.bucketsize);
	vector<Bucket*> directory=h.directory;
	vector<int> *node=directory[loc]->node;
	set<int> s;
	s.insert(loc);
	for(int i=0;i<node->size();i++){
		int loc=hashCode((*node)[i],directory.size());
		if(s.find(loc)==s.end()){
			s.insert(loc);
		}
	}
	for(set<int>::iterator it=s.begin();it!=s.end();it++){
		cout<<*it<<endl;
		if(*it==loc){
			emptybucket(directory[loc]);
		}
		else{
			directory[*it]=nb;
		}
	}
	printDirectory(directory);	
	for(int i=0;i<node->size();i++){
		int loc=hashCode((*node)[i],directory.size());
		insertback(directory[loc],(*node)[i]);
	}
	int loc1=hashCode(value,directory.size());
	insertback(directory[loc1],value);
	if(s.size()>2){
		cout<<"More than two buckets formed!!!";
		exit(0);
	}
	else{
		for(set<int>::iterator it=s.begin();it!=s.end();it++){
			int loc=*it;
			directory[loc]->localdepth++;
		}
	}
	h.directory=directory;
	
}
void insert(int value,HashTable &h){
	vector<Bucket*> directory=h.directory;
	int bucket_size =h.bucketsize;
	int dir_size = directory.size();
	int loc=hashCode(value,directory.size());
	cout<<"DEBUG_INFO : Location : "<<loc<<endl;
	if(isFull(directory[loc],bucket_size)){
		cout<<"INFO : Bucket ID :  " << loc << " Full "<<endl;
		int localdepth=directory[loc]->localdepth,globaldepth=h.globaldepth;
		if(localdepth==globaldepth){
			//Splitting bucket & Double Directory
			cout<<"INFO : Split the Bucket and Double the Directory "<<endl;
			insertSplit(h,value);
		}
		else if(localdepth<globaldepth){
			cout<<"INFO  : Splitting bucket "<<endl;
			//bucketSplit(h,value,loc);
		}
		else{
			cout<<" WARNING : : local depth > global depth : Exiting the PROGRAM";
			exit(0);
		}	
	}
	else{
		cout<<"INFO : Normal Insertion --"<<endl;
		insertback(directory[loc],value);
		cout << " INFO : Innsertion Done -- " << endl ;
		int dir_half_size = dir_size /2;
		if(directory[loc]->localdepth == h.globaldepth || loc < dir_half_size )
			directory[loc]->cur_size +=1;
		else
		{	int image_loc;
			image_loc = loc - dir_half_size;  
			//int loc=hashCode(value,d);
			cout << " loc : " << loc << " Image loc "<< image_loc << endl;
			directory[image_loc]->cur_size +=1 ;
		}
	}
}
int search(int value,HashTable h){
	int loc=hashCode(value,h.directory.size());
	vector<int> *node=h.directory[loc]->node;
	for(int i=0;i<node->size();i++){
		if((*node)[i]==value){
			cout<<value<<"INFO : found at location "<<loc<<endl;
			return loc;
		}
	}
	cout<<"INFO ::Not Found!!!!";	
	return -1;
}
void deleteVal(int value,HashTable &h){
	int loc=search(value,h);
	if(loc>=0){
		vector<int> *node=h.directory[loc]->node;
		int flag=0;
		for(int i=0;i<node->size();i++){
			if((*node)[i]==value || flag==1){
				flag=1;
				if(i+1<node->size())
					(*node)[i]=(*node)[i+1];
				else{
					(*node)[i]=-1;
				}	
			}
		}
		printNode(node);
		h.directory[loc]->node=node;
	}
}
void deleteAll(int loc,HashTable &h){
	if(loc>=h.directory.size()){
		cout<<"Invalid index"<<endl;
	}
	else{
		vector<int> *node=h.directory[loc]->node;
		for(int i=0;i<node->size();i++){
			(*node)[i]=-1;
		}
		h.directory[loc]->node=node;
	}
}
int main() {
	// your code goes here
	int dir_size,bucket_size,value;
	cout<<"Enter the intital directory size (Power of 2) : ";
	cin>>dir_size;
        //cout << "Enter the initial bucket size : ";
        //cin >> bucket_size;
	bucket_size=dir_size;
	HashTable h(dir_size,bucket_size);
	while(true) {
	int choice = printMenu();
	char ch = getchar();  // eat newline
	switch(choice) {
		case 1:   // Insert a record
			{

				cout << "Enter value to be added : ";
				cin >> value;
				insert(value,h);
				break;
			}

		case 2:   // Search a record
			{

				cout << "Enter value to be search ";
				cin >> value;
				search(value,h);
				break;
			}
		case 3: // delete data
			{
				cout << "Enter value to be deleted " << endl;
				cin>>value;
				deleteVal(value,h);
				break;
			}
		case 4: // delete all data
			{
            			cout << " Enter the index to deleted all data : " << endl ;
            			cin>>value;
            			deleteAll(value,h);
				break;
			}
		case 5:   // show All Records
		{
			print(h);
			break;
		}
		case 6:
			exit(0);
	}
}
	return 0;
}
