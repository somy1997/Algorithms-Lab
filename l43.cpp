#include <iostream>
#include <stdlib.h>
#include <stdio.h>

using namespace std;

struct node
{
    int key;
    struct node *left, *right, *parent;
};

struct node *newNode(int item)
{
    struct node *temp =  new node;
    temp->key = item;
    temp->left = temp->right = temp->parent = NULL;
    return temp;
}

struct node * minValueNode(struct node* node)
{
    struct node* current = node;
 
    /* loop down to find the leftmost leaf */
    while (current->left != NULL)
        current = current->left;
 
    return current;
}

int size(node *u)
{
    if (u == NULL)
    {
        return 0;
    }
	return size(u->left)+size(u->right)+1;
}

int height(node *T)
{
    if (T == NULL)
        return -1;
    int lefth = height(T->left);
    int righth = height(T->right);
    if (lefth > righth)
        return lefth + 1;
    else
        return righth + 1;
}

void inorder(struct node *root)
{
    if (root != NULL)
    {
        inorder(root->left);
        printf("%d ", root->key);
        inorder(root->right);
    }
}

void destroy(struct node *v)
{
    if (v != NULL)
    {
        destroy(v->left);
		destroy(v->right);
        delete v;
    }
}

struct node* insertKey(struct node* temp, int key)
{
    if (temp == NULL) 
		return newNode(key); 
	if(temp->key != key)
	{
    	if (key < temp->key)
     	   temp->left  = insertKey(temp->left, key);
    	else
        	temp->right = insertKey(temp->right, key);
	}
    return temp;
}

struct node* deleteKey(struct node* root, int key)
{
    // base case
    if (root == NULL) return root;
 
    // If the key to be deleted is smaller than the root's key,
    // then it lies in left subtree
    if (key < root->key)
        root->left = deleteKey(root->left, key);
 
    // If the key to be deleted is greater than the root's key,
    // then it lies in right subtree
    else if (key > root->key)
        root->right = deleteKey(root->right, key);
 
    // if key is same as root's key, then This is the node
    // to be deleted
    else
    {
        // node with only one child or no child
        if (root->left == NULL)
        {
            struct node *temp = root->right;
            free(root);
            return temp;
        }
        else if (root->right == NULL)
        {
            struct node *temp = root->left;
            free(root);
            return temp;
        }
 
        // node with two children: Get the inorder successor (smallest
        // in the right subtree)
        struct node* temp = minValueNode(root->right);
 
        // Copy the inorder successor's content to this node
        root->key = temp->key;
 
        // Delete the inorder successor
        root->right = deleteKey(root->right, temp->key);
    }
    return root;
}

void storekeys(struct node *temp,int *a,int &n)
{
    if (temp != NULL)
    {
        a[n]=temp->key;
		++n;
		storekeys(temp->left,a,n);
		storekeys(temp->right,a,n);
    }
}

void bsort(int *a,int n)
{
	int i,j,flag,temp;
	for(i=0;i<n;i++)
	{
		flag=0;
		for(j=0;j<n-i-1;j++)
		{
			if(a[j]>a[j+1])
			{
				flag=1;
				temp=a[j];
				a[j]=a[j+1];
				a[j+1]=temp;
			}
		}
		if(!flag)
			return;
	}
}

node * mybuild(int *a, int n)
{
	if(n == 0)
		return NULL;
	node *v=newNode(a[n/2]);
	v->left=mybuild(a,n/2);
	v->right=mybuild(a+n/2+1,n-n/2-1);
	return v;
}

node * rebuild(node *v,int s)
{
	int *a=new int[s];
	int n=0;
	storekeys(v,a,n);
	destroy(v);
	bsort(a,n);
	node *temp=NULL;
	temp=mybuild(a,n);
	delete a;
	return temp;
}

int main()
{
	node *root=NULL;
	int m,n;
	m=n=0;
	root=insertKey(root,1);
	inorder(root);
	cout<<endl;
	root=insertKey(root,2);
	inorder(root);
	cout<<endl;
	root=insertKey(root,3);
	inorder(root);
	cout<<endl;
	root=insertKey(root,4);
	inorder(root);
	cout<<endl;
	root=insertKey(root,5);
	inorder(root);
	cout<<endl;
	root=insertKey(root,6);
	inorder(root);
	cout<<endl;
	root=insertKey(root,7);
	inorder(root);
	cout<<endl;
	cout<<size(root)<<endl<<height(root)<<endl;
	root=rebuild(root,size(root));
	inorder(root);
	cout<<endl;
	cout<<size(root)<<endl<<height(root)<<endl;
	return 0;
}
