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


class LinkedList
/*
   Data pages
*/
{
    public:
        LinkedList(int size =0) : size(t)
        {  int local_depth =0;
           head = new node(); // vs node *head = NULL;
           head ->next = NULL;

        }
        ~LinkedList()
        {
            delete head;
        }
        
        void insert( )
        {
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

