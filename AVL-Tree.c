#include<stdio.h>
#include<stdlib.h>
struct avltree
{
	int data;
	struct avltree *left,*right;
	int height;
}*t;

int x;

void inorder(struct avltree*);
static int height(struct avltree *);
static int max(int,int);
struct avltree *insertion(struct avltree *,int);
struct avltree *singlerotationwithleft(struct avltree *k2);
struct avltree *singlerotationwithright(struct avltree *k1);
struct avltree *doublerotationwithleft(struct avltree *k3);
struct avltree *doublerotationwithright(struct avltree *k1);

void main()
{
	int choice;
	printf("\nAVL TREE");

	do
	{
		printf("\n<----MAIN MENU---->");
		printf("\n1.Insertion \n2.Inorder Display \n3.Exit");
		printf("\nEnter Your Choice ");
		scanf("%d",&choice);

		switch(choice)
		{
			case 1:
				printf("\nEnter Data ");
				scanf("%d",&x);
				t=insertion(t,x);
				inorder(t);
				break;
			case 2:
				inorder(t);
				break;
			case 3:
				exit(0);
				break;
		}

	}while(choice<=2);

}

struct avltree *insertion(struct avltree *t,int x)
{
	if(t==NULL)
	{
		t=(struct avltree*)malloc(sizeof(struct avltree));
		t->data=x;
		t->left=t->right=NULL;
		t->height=0;
	}
	else if(x<t->data)
	{
		t->left=insertion(t->left,x);
		if((height(t->left)-height(t->right))==2)
		{
			if(x<t->left->data)
				t=singlerotationwithleft(t);
			else
				t=doublerotationwithleft(t);
		}
	}
	else if(x>t->data)
	{
		t->right=insertion(t->right,x);
		if((height(t->right)-height(t->left)) ==2)
		{
			if(x>t->right->data)
				t=singlerotationwithright(t);
			else
				t=doublerotationwithright(t);
		}
	}
	t->height=max(height(t->left),height(t->right))+1;
	return t;
}

struct avltree *singlerotationwithleft(struct avltree *k2)
{
	struct avltree *k1;
	k1=k2->left;
	k2->left=k1->right;
	k1->right=k2;
	k2->height=max(height(k2->left),height(k2->right))+1;
	k1->height=max(height(k1->left),height(k2))+1;
	return k1;
}

struct avltree *singlerotationwithright(struct avltree *k1)
{
	struct avltree *k2;
	k2=k1->right;
	k1->right=k2->left;
	k2->left=k1;
	k1->height=max(height(k1->right),height(k1->left))+1;
	k2->height=max(height(k2->right),height(k1))+1;
	return k2;
}

struct avltree *doublerotationwithleft(struct avltree *k3)
{
	k3->left=singlerotationwithright(k3->left);
	return singlerotationwithleft(k3);
}

struct avltree *doublerotationwithright(struct avltree *k1)
{
	k1->right=singlerotationwithleft(k1->right);
	return singlerotationwithright(k1);
}

void inorder(struct avltree *t)
{
	if(t!=NULL)
	{
		inorder(t->left);
		printf(" %d ",t->data);
		inorder(t->right);
	}

}

int height(struct avltree *t)
{
	if(t==NULL)
		return -1;
	else
		return t->height;
}

static int max(int left,int right)
{
	return left>right?left:right;
}
