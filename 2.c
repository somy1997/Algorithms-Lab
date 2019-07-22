#include <stdio.h>

int a[10];
static int count=0;

void dispnum()
{
	int j;
	char ch;
	for(j=0;j<10;j++)
		printf("%d",a[j]);
	printf("\n");
	if(count < 10)
		count++;
	else
	{
		count=0;
		scanf("%c",&ch);
		printf("\n");
	}
}

void findnum(int pos,int sum)
{
	int i,j;
	if(sum==0)
	{
		for(j=pos;j<10;j++)
			a[j]=0;
		dispnum();
		return;
	}
	if(pos==9)
	{
		a[9]=sum;
		dispnum();
		return;
	}
	for(i=0;i<=sum;i++)
	{
		a[pos]=i;
		findnum(pos+1,sum-i);
	}
}

int main()
{
	int j;
	a[0]=1;
	for(j=1;j<10;j++)
		a[j]=0;
	findnum(1,9);
	return 0;
}
