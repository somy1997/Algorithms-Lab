#include <stdio.h>

int a[10]={6,2,1,0,0,0,1,0,0,0};

int main()
{
	int i,j,ctr,ck=1;
	for(i=0;i<10;i++)
	{
		ctr=0;
		for(j=0;j<10;j++)
		{
			if(a[j]==i)
				ctr++;			
		}
		if(ctr!=a[i])
		{
			ck=0;
			break;
		}
	}
	if(ck)
		printf("1");
	else
		printf("0");
	printf("\n");
	return 0;
}
