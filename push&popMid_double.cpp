#include<stdio.h>
#include<string.h>
#include<stdlib.h>

struct Node{
	int umur;
	Node*next=NULL;
	Node*prev=NULL;
}*head=NULL,*tail=NULL;

Node*newNode(int umur){
	Node*createNode=(Node*)malloc(sizeof(Node));
	createNode->umur=umur;
	createNode->next=NULL;
	createNode->prev=NULL;
	return createNode;
}

void pushHead(int umur){
	Node*toInsert=newNode(umur);
	if(head==NULL){
		head=toInsert;
		tail=toInsert;
	}else{
		toInsert->next=head;
		head->prev=toInsert;
		head=toInsert;		
	}
}
void pushTail(int umur){
	Node*toInsert=newNode(umur);
	if(tail==NULL){
		tail=toInsert;
		head=toInsert;
	}else{
		toInsert->prev=tail;
		tail->next=toInsert;
		tail=toInsert;
	}
}
void pushMid(int umur){
	Node*toInsert=newNode(umur);
	if(head==NULL){
		head=toInsert;
		tail=toInsert;
	}else{
		Node*curr=head;
		if(head->umur>umur){
			pushHead(umur);
			return;
		}
		if(tail->umur<umur){
			pushTail(umur);
			return;
		}
		while(curr!=NULL&&curr->umur>toInsert->umur){
			curr=curr->next;
		}
		curr->next->prev=toInsert;
		toInsert->next=curr->next;
		curr->next=toInsert;
	}
}
void print(){
	Node*curr=head;
	while(curr!=NULL){
		printf("%d\n",curr->umur);
		curr=curr->next;
	}
}

void popHead(){
	Node*temp=head->next;
	free(head);
	head=temp;
}
void popTail()
{
	if(!head) return;
	if(head == tail)
	{
		popHead();
		return;
	}
	
	tail = tail->prev;
	free(tail->next);
	tail->next = NULL;
}

void popMid(int key){
	if(head==NULL){
		puts("No data");
		return;
	}	
	Node*curr=head;
	if(head->umur==key){
		popHead();
		return;
	}
	if(tail->umur==key){
		popTail();
		return;
	}
	while(curr->next!=NULL&&curr->next->umur!=key){
		curr=curr->next;
	}
	Node*del=curr->next;
	curr->next=del->next;
	del->next->prev=curr;
	free(del);
}

int main(){
	pushMid(2);
	pushMid(1);
	pushMid(3);
	print();
	puts("=======================");
	popMid(2);
	print();
	return 0;
}
