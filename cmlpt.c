#include<stdio.h>
#include<stdlib.h>
struct node {
	int data;
	struct node *left;
	struct node *right;
};
struct node *new(int data) 
{
	struct node *t;	
	t=malloc(sizeof(struct node));
	t->data=data;
	t->left=0;
	t->right=0;
	return t;
}
struct node *append(struct node *h,struct node *n)
{
	if (h == 0) {
		return n;
		
	}
	else if ((h->data)>(n->data)) {
		h->left=append(h->left,n);
	}
	else {
		h->right=append(h->right,n);
	}
	return h;
}
struct node *findlargest(struct node *h)
{
	while ((h->right)!=0) {
		h=h->right;
	}
	return h;
}
struct node *findsmallest(struct node *h)
{
	while ((h->left)!=0) {
		h=h->left;
	}
	return h;
}
struct node *searchdata(struct node *h,int data)
{
	if (h == 0) return 0;
		
	else if (h->data == data) {
		return h;
	}
	else if ((h->data) > data) {
		return searchdata(h->left,data);
	}
	else {
		return searchdata(h->right,data);
	}
}
struct node *findparent(struct node *h,struct node *item)
{
	if ((h == 0)||(h == item)) return NULL;
	else if ((h->left == item) || (h->right == item )) return h;
	else if (h->data > item->data) return findparent(h->left,item);
	else return findparent(h->right,item);
}
		
void inorder(struct node *h)
{
	if(h != 0) {
		inorder(h->left);
		printf("%d\n", h->data);
		inorder(h->right);
	}
}
struct node *findaddress(struct node *h,int value)
{
	if (h == 0) return 0;
	else if (h->data == value) return h;
	else if (h->data > value) return findaddress(h->left,value);
	else return findaddress(h->right,value);
}
int leftchild(struct node *parent,struct node *child)
{
	if (parent->left == child) return 1;
	else return 1;
}
int rightchild(struct node *parent,struct node *child)
{
	if (parent->right == child) return 1;
	else return 0;
}
int containsleft(struct node *h)
{
	if ((h->left)!=0) return 1;
	else return 0;
}
int containsright(struct node *h)
{
	if ((h->right)!=0) return 1;
	else return 0;
}
int leafnode(struct node *address)
{
	if ((address->left == NULL) && (address->right == NULL)) {
		 return 1;
	}
	else return 0;
}
void deleteroot(struct node *h)
{
	struct node *smallest,*parent,*largest,*temp;
	temp=h;
	if ((h->left)!=NULL) {
		temp=temp->left;
		largest = findlargest(temp);
		if ((temp->right)==NULL) {
			parent = findparent(h,largest);
			parent->left = largest->left;
			h->data = largest->data;
			free(largest);
		}
		else {
			parent = findparent(h,largest);
			h->data = largest->data;
			if ((parent->left) == largest) parent->left = NULL;
			else parent->right = NULL;
			free(largest);
		}			
	}
	else {
		temp = temp->right;
		smallest = findsmallest(temp);
		if ((temp->left)==NULL) {
			parent = findparent(h,smallest);
			parent->right = smallest->right;
			h->data = smallest->data;
			free(smallest);
		}
		else {
			parent = findparent(h,smallest);
			h->data = smallest->data;
			if ((parent->left) == smallest) parent->left = NULL;
			else parent->right = NULL;
			free(smallest);
				
		}
	}						
}
void deleteleafnode(struct node *h,struct node *address)
{
	struct node *parent;
	parent = findparent(h,address);
	if (leftchild(parent,address)) {
		parent->left = NULL;
		free(address);
	}
	else {
		parent->right = NULL;
		free(address);
	}
}

void delete(struct node *h,struct node *nodeaddress)
{ 	struct node *temp,*smallest,*parent,*largest;
	temp = nodeaddress;
	if ((nodeaddress->left == 0) && (nodeaddress->right == 0)) {
		parent = findparent(h,nodeaddress);
		if (parent->left == nodeaddress) {
			parent->left = NULL;
		}
		else parent->right = NULL;
		free(nodeaddress);	
	}
	else if (h == nodeaddress) {
		deleteroot(nodeaddress);
	}
	else {	parent = findparent(h,nodeaddress);
		if ((nodeaddress->right)==NULL) {
			largest = findlargest(nodeaddress->left);
			temp = nodeaddress->left;
			if ((temp->right)==NULL) {
				if ((parent->left)==nodeaddress) {
					parent->left = largest;
				}
				else parent->right = largest;
				free(nodeaddress);
			}
			else {
				smallest = findsmallest(temp->right);
				parent = findparent(h,smallest);
				nodeaddress->data = smallest->data;
				if ((parent->left) == smallest) {
					parent->left = NULL;
				}
				else parent->right = NULL;
				free(smallest);
			}
		}
		else {
			temp = nodeaddress->right;
			smallest = findsmallest(nodeaddress->right);
			parent = findparent(h,smallest);			
			if ((temp->left)==NULL) {
				parent->right = temp->right;
				nodeaddress->data = smallest->data;
			}
			else {
				nodeaddress->data = smallest->data;
				parent->left = NULL;
			}
			free(smallest);
		}			
	}	
}
main()
{
	int values[9],i=0,element,delval;
	struct node *h=0;
	struct node *item,*parent,*smallest,*address=0;
	printf("Enter the value to be inserted :\n");
	for(i=0;i<9;i++) {
		scanf("%d",&values[i]);
		h=append(h,new(values[i]));
	}
	printf("inorder traversal ...\n");
	inorder(h);
	printf(" enter the data to be deleted :\n");
	scanf("%d",&delval);
	address = findaddress(h,delval);
	while (address == 0) {
		printf("data not present, please enter the correct data :\n");
		printf("enter the data to be deleted : \n");
		scanf("%d",&delval);
		address = findaddress(h,delval);
	}
	delete(h,address);
	printf("-----------after deletion--------------\n");
	inorder(h);
}
