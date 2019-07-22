#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

using namespace std;

typedef struct 
{
	char x[21], y[21]; 
} strpair;

typedef struct 
{
	char att[21]; 
	int nassoc; 
	int assoc[10];
} htnode;

typedef struct 
{
	int S; 
	htnode *A,*B; 
} hashtable;

hashtable inittable(int S)
{
	int i;
	hashtable T;
	T.S=S;
	T.A= new htnode[S];
	T.B= new htnode[S];
	for(i=0;i<S;i++)
	{
		T.A[i].nassoc=T.B[i].nassoc=0;
		strcpy(T.A[i].att,"EMPTY");
		strcpy(T.B[i].att,"EMPTY");
	}
	return T;
}

int hashindex(char* z,int S)
{
	int i,Hs=0;
	for(i=0;z[i]!='\0';i++)
	{
		Hs=(128*Hs+(int)z[i])%S;
	}
	return Hs;
}

int mysearchpair(hashtable T,strpair p,int &indx,int &indy)
{
	int i,S=T.S;
	indx=hashindex(p.x,S);
	i=indx;
	while(strcmp(T.A[i].att,p.x))
	{
		i=(i+1)%S;
		if(i==indx)
		{
			return 0;	
		}
	}
	indx=i;
	for(i=0;i<T.A[indx].nassoc;i++)
	{
		indy=T.A[indx].assoc[i];
		if(!strcmp(T.B[indy].att,p.y))
			return 1;
	}
	return 0;
}

void searchpair(hashtable T,strpair p)
{
	int indx,indy;
	if(mysearchpair(T,p,indx,indy))
		cout<<"The given pair is stored at ("<<indx<<","<<indy<<").\n\n";
	else
		cout<<"The given pair is not stored in T.\n\n";
}

void searchattr(hashtable T,char* z, int a)
{
	int i,indx,indy,S=T.S;
	if(a==1)
	{
		indx=hashindex(z,S);
		i=indx;
		while(strcmp(T.A[i].att,z))
		{
			i=(i+1)%S;
			if(i==indx)
			{
				cout<<"Required pairs not found.\n\n";
				return;	
			}
		}
		indx=i;
		for(i=0;i<T.A[indx].nassoc;i++)
		{
			indy=T.A[indx].assoc[i];
			cout<<T.B[indy].att<<"\t";
		}
		cout<<endl<<endl;	
	}
	else
	{
		indy=hashindex(z,S);
		i=indy;
		while(strcmp(T.B[i].att,z))
		{
			i=(i+1)%S;
			if(i==indy)
			{
				cout<<"Required pairs not found.\n\n";
				return;	
			}
		}
		indy=i;
		for(i=0;i<T.B[indy].nassoc;i++)
		{
			indx=T.B[indy].assoc[i];
			cout<<T.A[indx].att<<"\t";
		}
		cout<<endl<<endl;	
	}
}

hashtable insertpair(hashtable T,strpair p)
{
	int i,indx,indy,S=T.S;
	if(mysearchpair(T,p,indx,indy))
		return T;
	indx=hashindex(p.x,S);
	indy=hashindex(p.y,S);
	cout<<"hash = ("<<indx<<","<<indy<<")\n";
	i=indx;
	while(strcmp(T.A[i].att,"EMPTY")&&strcmp(T.A[i].att,"DELETED")&&strcmp(T.A[i].att,p.x))
	{
		i=(i+1)%S;
		if(i==indx)
		{
			cout<<"FULL\n\n";
			return T;	
		}
	}
	indx=i;
	i=indy;
	while(strcmp(T.B[i].att,"EMPTY")&&strcmp(T.B[i].att,"DELETED")&&strcmp(T.B[i].att,p.y))
	{
		i=(i+1)%S;
		if(i==indy)
		{
			cout<<"FULL\n\n";
			return T;	
		}
	}
	indy=i;
	strcpy(T.A[indx].att,p.x);
	strcpy(T.B[indy].att,p.y);
	T.A[indx].assoc[T.A[indx].nassoc]=indy;
	T.A[indx].nassoc++;
	T.B[indy].assoc[T.B[indy].nassoc]=indx;
	T.B[indy].nassoc++;
	cout<<"insertion at ("<<indx<<","<<indy<<")\n\n";
	return T;
}

hashtable deletepair(hashtable T,strpair p)
{
	int flag,i,indx,indy,S=T.S;
	indx=hashindex(p.x,S);
	indy=hashindex(p.y,S);
	cout<<"hash = ("<<indx<<","<<indy<<")\n";
	i=indx;
	while(strcmp(T.A[i].att,p.x))
	{
		i=(i+1)%S;
		if(i==indx)
		{
			return T;	
		}
	}
	indx=i;
	i=indy;
	while(strcmp(T.B[i].att,p.y))
	{
		i=(i+1)%S;
		if(i==indy)
		{
			return T;	
		}
	}
	indy=i;
	flag=0;
	for(i=0;i<T.A[indx].nassoc;i++)
	{
		if(indy==T.A[indx].assoc[i])
		{
			flag=1;
			break;
		}
	}
	if(!flag)
		return T;
	for(;i<T.A[indx].nassoc-1;i++)
	{
		T.A[indx].assoc[i]=T.A[indx].assoc[i+1];
	}
	T.A[indx].nassoc--;
	if(!T.A[indx].nassoc)
		strcpy(T.A[indx].att,"DELETED");
	for(i=0;i<T.B[indy].nassoc;i++)
	{
		if(indx==T.B[indy].assoc[i])
		{
			break;
		}
	}
	for(;i<T.B[indy].nassoc-1;i++)
	{
		T.B[indy].assoc[i]=T.B[indy].assoc[i+1];
	}
	T.B[indy].nassoc--;
	if(!T.B[indy].nassoc)
		strcpy(T.B[indy].att,"DELETED");
	cout<<"deletion at ("<<indx<<","<<indy<<")\n\n";
	return T;
}

int main()
{
	int S,n;
	strpair p;
	cin>>S;
	hashtable T=inittable(S);
	do
	{
	cout<<"Enter choice: ";
	cin>>n;	
	switch(n)
	{
		case 1:
		scanf("%s",p.x);
		searchattr(T,p.x,n);
		break;
		case 2:
		scanf("%s",p.y);
		searchattr(T,p.y,n);
		break;
		case 3:
		scanf("%s",p.x);
		scanf("%s",p.y);
		searchpair(T,p);
		break;
		case 4:
		scanf("%s",p.x);
		scanf("%s",p.y);
		T=insertpair(T,p);
		break;
		case 5:
		scanf("%s",p.x);
		scanf("%s",p.y);
		T=deletepair(T,p);
	}
	}while(n);
	return 0;
}
