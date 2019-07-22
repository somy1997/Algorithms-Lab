#include <iostream>
#include <stdlib.h>

using namespace std;

struct indexpair
{
	int i,j;
};

void minheapify(int *a,int n,int i)
{
	int min=i,temp;
	if(2*i<=n && a[2*i]<a[min])
		min=2*i;
	if(2*i+1<=n && a[2*i+1]<a[min])
		min=2*i+1;
	if(min!=i)
	{
		temp=a[i];
		a[i]=a[min];
		a[min]=temp;
		minheapify(a,n,min);
	}
}

void buildheap(int *a,int n)
{
	int i;
	for(i=n/2;i>=1;i--)
		minheapify(a,n,i);
}

int extractmin(int *a,int &n)
{
	int min;
	min=a[1];
	a[1]=a[n];
	--n;
	minheapify(a,n,1);
	return min;
}

void insertQ(indexpair *Q,int &l,int *a,int *b,int i,int j)
{
	l++;
	Q[l].i=i;
	Q[l].j=j;
	int n=l;
	indexpair temp;
	while(n>1 && a[Q[n].i]+b[Q[n].j]<a[Q[n/2].i]+b[Q[n/2].j])
	{
		temp=Q[n];
		Q[n]=Q[n/2];
		Q[n/2]=temp;
		n=n/2;
	}
}

void minheapify2(indexpair *Q,int l,int i,int *a,int *b)
{
	int min=i;
	indexpair temp;
	if(2*i<=l && a[Q[2*i].i]+b[Q[2*i].j]<a[Q[min].i]+b[Q[min].j])
		min=2*i;
	if(2*i+1<=l && a[Q[2*i+1].i]+b[Q[2*i+1].j]<a[Q[min].i]+b[Q[min].j])
		min=2*i+1;
	if(min!=i)
	{
		temp=Q[i];
		Q[i]=Q[min];
		Q[min]=temp;
		minheapify2(Q,l,min,a,b);
	}
}

indexpair extractQ(indexpair *Q,int &l,int *a,int *b)
{
	indexpair min;
	min=Q[1];
	Q[1]=Q[l];
	--l;
	minheapify2(Q,l,1,a,b);
	return min;
}

void disparr(int *a,int n)
{
	for(int i=1;i<=n;i++)
		cout<<a[i]<<endl;
	cout<<endl;
}

void method1(int *a,int *b,int m,int n,int k)
{
	int i,j,p=1,l=m*n;
	int *s=new int[l+1];
	for(i=1;i<=m;i++)
		for(j=1;j<=n;j++)
			s[p++]=a[i]+b[j];
	buildheap(s,l);
	for(i=1;i<=k;i++)
		cout<<extractmin(s,l)<<endl;
	cout<<endl;
	delete s;
}

void method2(int *a,int *b,int m,int n,int k)
{
	int ctr=1,l=0,presum=0,sum,i,j;
	indexpair *Q=new indexpair[8*k+2];
	indexpair min;
	insertQ(Q,l,a,b,1,1);
	while(ctr<=k)
	{
		min=extractQ(Q,l,a,b);
		i=min.i;
		j=min.j;
		sum=a[i]+b[j];
		if(sum!=presum)
		{
			presum=sum;
			cout<<sum<<"=A["<<i<<"]"<<"+B["<<j<<"]="<<a[i]<<"+"<<b[j]<<endl;
			ctr++;
			if(2*i<=m)
				insertQ(Q,l,a,b,2*i,j);
			if(2*i+1<=m)
				insertQ(Q,l,a,b,2*i+1,j);
			if(2*j<=n)
				insertQ(Q,l,a,b,i,2*j);
			if(2*j+1<=n)
				insertQ(Q,l,a,b,i,2*j+1);
		}
	}
	cout<<endl;
	delete Q;
}

void insertQ1(indexpair *Q,int &l,int *a,int *b,int i,int j)
{
	l++;
	Q[l].i=i;
	Q[l].j=j;
	int n=l;
	indexpair temp;
	while(n>1 && a[Q[n].i]+b[Q[n].j]<a[Q[n-1].i]+b[Q[n-1].j])
	{
		temp=Q[n];
		Q[n]=Q[n-1];
		Q[n-1]=temp;
		n=n-1;
	}
}

int findQ1(indexpair *Q,int &l,int *a,int *b,int i,int j)
{
    l++;
    int sum=a[i]+b[j],first=1,last=l,mid=(l+1)/2,found=0;
    while(first<=last)
    {
        if(sum>a[Q[mid].i]+b[Q[mid].j])
            first=mid+1;
        else if(sum<a[Q[mid].i]+b[Q[mid].j])
            last=mid-1;
        else
        {
            found=1;
            break;
        }
        mid=(first+last)/2;
    }
    if(found)
    {
        found=0;
        indexpair temp={i,j};
        if(temp.i==Q[mid].i&&temp.j==Q[mid].j)
            found=1;
        else
        {
            int p;
            for(p=mid-1;p>=1&&a[Q[p].i]+b[Q[p].j]==sum;p--)
            {
                if(temp.i==Q[p].i&&temp.j==Q[p].j)
                {
                    found=1;
                    break;
                }
            }
            for(p=mid+1;p<=l&&a[Q[p].i]+b[Q[p].j]==sum;p++)
            {
                if(temp.i==Q[p].i&&temp.j==Q[p].j)
                {
                    found=1;
                    break;
                }
            }
        }
    }
    return found;
}

void method3(int *a,int *b,int m,int n,int k)
 {
 	int ctr=1,l=0,l1,sum,i,j;
	indexpair *Q=new indexpair[8*k+2];
	indexpair *Q1=new indexpair[k+1];
	indexpair min;
	insertQ(Q,l,a,b,1,1);
	while(ctr<=k)
	{
		min=extractQ(Q,l,a,b);
		i=min.i;
		j=min.j;
		sum=a[i]+b[j];
        cout<<sum<<"=A["<<i<<"]"<<"+B["<<j<<"]="<<a[i]<<"+"<<b[j]<<endl;
        insertQ1(Q1,l1,a,b,i,j);
        ctr++;
        if(2*i<=m)
            if(!findQ1(Q1,l1,a,b,2*i,j/2))
                insertQ(Q,l,a,b,2*i,j);
        if(2*i+1<=m)
            if(!findQ1(Q1,l1,a,b,2*i+1,j/2))
                insertQ(Q,l,a,b,2*i+1,j);
        if(2*j<=n)
            if(!findQ1(Q1,l1,a,b,i/2,2*j))
                insertQ(Q,l,a,b,i,2*j);
        if(2*j+1<=n)
            if(!findQ1(Q1,l1,a,b,i/2,2*j+1))
                insertQ(Q,l,a,b,i,2*j+1);
	}
	cout<<endl;
 }

int main()
{
	int m,n,i,k;
	cout<<"Array A:\n\n";
	cin>>m;
	cout<<m<<endl<<endl;
	int *a=new int[m+1];
	for(i=1;i<=m;i++)
		cin>>a[i];
	cout<<endl;
	disparr(a,m);
	cout<<"Array B:\n\n";
	cin>>n;
	cout<<n<<endl<<endl;
	int *b=new int[n+1];
	for(i=1;i<=n;i++)
		cin>>b[i];
	cout<<endl;
	disparr(b,n);
	cin>>k;
	cout<<"k = "<<k<<endl<<endl;
	buildheap(a,m);
	buildheap(b,n);
	cout<<"Method 1:\n\n";
	method1(a,b,m,n,k);
	cout<<"Method 2:\n\n";
	method2(a,b,m,n,k);
	cout<<"Array A:\n\n";
	for(i=1;i<=m;i++)
		cin>>a[i];
	cout<<endl;
	disparr(a,m);
	cout<<"Array B:\n\n";
	for(i=1;i<=n;i++)
		cin>>b[i];
	cout<<endl;
	disparr(b,n);
	buildheap(a,m);
	buildheap(b,n);
	cout<<"Method 1:\n\n";
	method1(a,b,m,n,k);
	cout<<"Method 3:\n\n";
	method3(a,b,m,n,k);
	delete a;
	delete b;
}

