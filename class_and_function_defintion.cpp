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

int hashCode(int number, int dir_size)//returns hashKey of a number
bool isFull(Bucket *b, int overflow_option)
void print(HashTable &h) // To print HashTable
void insert(int value,HashTable &h); 
void insertBack(Bucket *b,int value, int overflow_option);

