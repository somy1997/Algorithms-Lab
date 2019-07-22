#include <stdio.h>
#include <stdlib.h>

#define maxht 15

struct node
{
	int eos;
	struct node* left;
	struct node* right; 
};

void pt(struct node* temp,int *a,int *n)
{
	int i;
	if(temp->eos==1)
	{
		for(i=0;i<*n;i++)
			printf("%d",a[i]);
		printf("\n");
	}
	if(temp->left!=NULL)
	{
		a[*n]=0;
		(*n)++;
		pt(temp->left,a,n);
		(*n)--;
	}
	if(temp->right!=NULL)
	{
		a[*n]=1;
		(*n)++;
		pt(temp->right,a,n);
		(*n)--;
	}
}


void printTree(struct node* root)
{
	if(root->eos==1)
	{
		printf("empty\n");
	}
	int a[maxht],n=0;
	pt(root,a,&n);
}

struct node* insert(struct node* root,int a)
{
	struct node* temp=root;
	int c2bit[maxht],n=0,i=0;
	while(a)
	{
		c2bit[n]=a%2;
		n++;
		a=a/2;
	}

	/*for(i=0;i<n;i++)
		printf("%d",c2bit[i]);
	printf("\n");*/
	
	for(i=n-2;i>=0;i--)
	{
		if(c2bit[i])
		{
			if(temp->right==NULL)
			{
				temp->right=(struct node*)malloc(sizeof(struct node));
				temp->right->eos=0;

			}
			temp=temp->right;	
		}
		else
		{
			if(temp->left==NULL)
			{
				temp->left=(struct node*)malloc(sizeof(struct node));
				temp->left->eos=0;

			}
			temp=temp->left;	
		}
	}
	if(n)		//If 0 is not a possibility then direct temp->eos=1;
	{
		temp->eos=1;
	}
	return root;
}

int main()
{
	struct node* root;
	int a,n,i;
	root=(struct node*)malloc(sizeof(struct node));
	root->eos=0;
	scanf("%d",&n);
	for(i=0;i<n;i++)
	{
		scanf("%d",&a);
		root=insert(root,a);
	}
	printTree(root);
	return 0;
}
