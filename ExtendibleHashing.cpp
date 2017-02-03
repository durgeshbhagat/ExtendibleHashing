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
           int head[max_size]; // A dynamic Array 
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

        }

 }

