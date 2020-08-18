#include <stdio.h>
#include <stdlib.h>
#define MAX_STACK_SIZE	100

//DblLinkedList 를 활용
class Node2{
	Node2* prev;
	Node2* next;
	int data;
	public:
	Node2(int val=0):data(val),prev(NULL),next(NULL){}
	Node2* getPrev(){return prev;}
	Node2* getNext(){return next;}
	void setPrev(Node2* p){prev=p;}
	void setNext(Node2* n){next=n;}
	void display(){printf(" <%2d>",data);}
	bool hasData(int val){return data==val;}
	
	void insertNext(Node2* n){
		if(n!=NULL){
			n->prev=this;
			n->next=next;
			if(next!=NULL)next->prev=n;
			next=n;
		}
	}
	
	Node2* remove(){
		if(prev!=NULL) prev->next=next;
		if(next!=NULL) next->prev=prev;
		return this;
	}
};

class DblLinkedList{
	Node2 org;
	public:
	DblLinkedList():org(0){}
	~DblLinkedList(){while(!isEmpty()) delete remove(0);}
	Node2* getHead(){return org.getNext();}
	bool isEmpty(){return getHead()==NULL;}
	
	Node2* getEntry(int pos){
		Node2* n = &org;
		for(int i=-1; i<pos; i++, n=n->getNext())
			if(n==NULL) break;
		return n;
	}
	
	void insert(int pos, Node2* n){
		Node2* prev=getEntry(pos-1);
		if(prev!=NULL)
			prev->insertNext(n);
	}
	
	Node2* remove(int pos){
		Node2* n=getEntry(pos);
		return n->remove();
	}
	
	void replace(int pos,Node2 *n){
		Node2* prev=getEntry(pos-1);
		if(prev!=NULL){
			delete prev->getNext()->remove();
			prev->insertNext(n);
		}
	}
	
	int size(){
		int count=0;
		for(Node2* p=getHead();p!=NULL;p=p->getNext())
			count++;
		return count;
	}
	
	void display(){
		printf("[ the size of Deque = %2d] : ",size());
		for(Node2* p=getHead();p!=NULL;p=p->getNext())
			p->display();
		printf("\n");
	}
	
	void clear(){while(!isEmpty()) delete remove(0);}
};

class LinkedDeque : public DblLinkedList
{
//LinkedDeque 클래스 구현
public:
void addFront(Node2* n){insert(0,n);}
Node2* deleteFront(){return remove(0);}
Node2* getFront(){return getEntry(0);}
void addRear(Node2* n){insert(size(),n);}
Node2* deleteRear(){return remove(size()-1);}
Node2* getRear(){return getEntry(size()-1);}

};//class LinkedDeque 끝



int main()
{
		LinkedDeque deq;
    for( int i=1 ; i<10 ; i++ ) {
         if( i % 2 ) deq.addFront( new Node2(i) );
         else deq.addRear( new Node2(i) );
    }
    deq.display();
    delete deq.deleteFront();
    delete deq.deleteRear();
    delete deq.deleteFront();
    deq.display();
	
		return 0;
}


