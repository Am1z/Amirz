#include<stdio.h>
#include<string.h>
#include<stdlib.h>

struct data{
	int value;
	data*right;
	data*left;
	int height;
};
int max(int a,int b){
	return (a>b)?a:b;
}
int Height(data*node){
	if(node==NULL)return 0;
	return node->height;
}
int getBalance(data*node){
	if(node==NULL)return 0;
	return Height(node->left)-Height(node->right);
}
data*left_rotate(data*root){
	data*x=root->right;
	data*sub_x=x->left;
	x->left=root;
	root->right=sub_x;
	root->height=1+max(Height(root->left),Height(root->right));
	x->height=1+max(Height(root->left),Height(root->right));
	return x;		
}
data*right_rotate(data*root){
	data*x=root->left;
	data*sub_x=x->right;
	x->right=root;
	root->left=sub_x;
	root->height=1+max(Height(root->left),Height(root->right));
	x->height=1+max(Height(root->left),Height(root->right));
	return x;		
}
data*newNode(int value){
	data*toInsert=(data*)malloc(sizeof(data));
	toInsert->value=value;
	toInsert->right=NULL;
	toInsert->left=NULL;
	toInsert->height=1;
	return toInsert;
}
data*insert(data*root,int value){
	if(root==NULL){
		return newNode(value);
	}
	if(root->value<value){
		root->right=insert(root->right,value);
	}
	else if(root->value>value){
		root->left=insert(root->left,value);
	}else{
		return root;
	}
	root->height=1+max(Height(root->left),Height(root->right));
	int balance=getBalance(root);
	if(balance>1&&value<root->value){
		//left rotate
		return right_rotate(root);
	}
	if(balance>1&&value>root->value){
		//left rotate
		root->left=left_rotate(root->left);
		//right rotate
		return right_rotate(root);
	}
	if(balance<-1&&value<root->value){
		//right rotate
		root->right=right_rotate(root->right);
		//left rotate
		return left_rotate(root);
	}
	if(balance<-1&&value>root->value){
		//left rotate
		return left_rotate(root);
	}
	return root;
}
data*get_pred(data*root){
	data*curr=root->left;
	while(curr->right!=NULL)curr=curr->right;
	return curr;
}
data*search(data*root,int key){
	if(root==NULL){
		return NULL;
	}
	if(root->value<key){
		return search(root->right,key);
	}else if(root->value>key){
		return search(root->left,key);
	}
	return root;
}
data*delet(data*root,int key){
	if (root==NULL){
		printf("no data");
		return NULL;
	}
	if(root->value<key){
		root->right=delet(root->right,key);
	}else if(root->value>key){
		root->left=delet(root->left,key);
	}else{
		if(root->left==NULL||root->right==NULL){
			data*temp=NULL;
			if(root->left){
				temp=root->left;
			}
			else{
				temp=root->right;
			}
			free(root);
			return temp;
		}
		else{
			data*pred=get_pred(root);
			root->value=pred->value;
			root->left=delet(root->left,pred->value);
		}
	}
	root->height=1+max(Height(root->left),Height(root->right));
	int balance=getBalance(root);
	//left left case
	if(balance>1&&getBalance(root->left)>=0){
		return right_rotate(root);
	}else if(balance>1&&getBalance(root->left)<0){//left right
		root->left=left_rotate(root->left);
		return right_rotate(root);
	}else if(balance<-1&&getBalance(root->right)<=0){//right right case
		return left_rotate(root);
	}else if(balance<-1&&getBalance(root->right)>0){//right left case
		root->right=right_rotate(root->right);
		return left_rotate(root);
	}
	return root;
}
void print(data*root){
	if(root!=NULL){
		print(root->left);
		printf("%d\n",root->value);
		print(root->right);
	}
}
int main(){
	data*root=NULL;
	root=insert(root,37);
	insert(root,13);
	insert(root,48);
	insert(root,77);
	insert(root,43);
	print(root);
	puts("\n\n");
	data*find=search(root,13);
	if(find!=NULL){
		printf("data dengan value %d ketemu",find->value);
	}else{
		printf("data not found");
	}
	puts("\n\n");
	root=delet(root,13);
	print(root);
	return 0;
}
