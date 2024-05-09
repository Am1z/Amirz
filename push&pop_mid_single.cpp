#include<stdio.h>
#include<stdlib.h>

struct data{
	int age;
	data*next=NULL;
}*head=NULL,*tail=NULL;


data*createNode(int age){
	data*toInsert=(data*)malloc(sizeof(age));
	toInsert->age=age;
	toInsert->next=NULL;
	return toInsert;
}

void pushHead(int age){
	data*toInsert=createNode(age);
	if(head==NULL){
		head=toInsert;
		tail=toInsert;
	}else{
		toInsert->next=head;
		head=toInsert;
	}
}
void pushMid(int age){
	data*toInsert=createNode(age);
	if(head==NULL){
		head=toInsert;
		tail=toInsert;
	}else{
		data*curr=head;
		if(age<curr->age){
			pushHead(age);
			return;
		}
		while(curr->next!=NULL&&curr->next->age<age){
			curr=curr->next;
		}
		toInsert->next=curr->next;
		curr->next=toInsert;
		if(tail==curr){
			tail=toInsert;
		}
	}
}

void popHead(){
	data*temp=head->next;
	free(head);
	head=temp;
}


void popTail(){
	data*curr=head;
	while(curr->next->next!=NULL){
		curr=curr->next;
	}
	free(curr->next);
	curr->next=NULL;
}

void popMid(int key){
	if(head==NULL){
		printf("ga ada data bang\n");
		return;
	}
	data*curr=head;
	if(head->age==key){
		popHead();
		return;
	}
	if(tail->age==key){
		popTail();
		return;
	}
	while(curr->next!=NULL&&curr->next->age!=key){
		curr=curr->next;
	}
	data*del=curr->next;
	curr->next=del->next;
	free(del);
}
	
void print(){
	data*curr=head;
	while(curr!=NULL){
		printf("%d\n",curr->age);
		curr=curr->next;
	}
}

int main(){
	pushMid(10);
	pushMid(2);
	pushMid(13);
	pushMid(11);
	pushMid(12);
	pushMid(9);
	print();
//	popHead();
//	popTail();
	puts("++++++++++");
	popMid(12);
	print();
	return 0;
}
