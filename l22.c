#include<stdio.h>

struct student
{
	char rno[10];
	int a,s;
};

void disp(struct student temp)
{
	printf("%s %d %d\n",temp.rno,temp.a,temp.s);
}

int main()
{
	int i,n,sub,a,b,tl[15],flag,j,k,temp;
	struct student stud[15];
	scanf("%d",&n);
	for(i=0;i<n;i++)
	{	
		scanf("%s%d%d",stud[i].rno,&stud[i].a,&stud[i].s);
	}
	for(i=0;i<n;i++)
	{	
		disp(stud[i]);
	}
	printf("\n");
	scanf("%d%d%d",&sub,&a,&b);
	do{
		printf("%d %d %d\n\n",sub,a,b);
		if(sub==1)
		{
			k=0;
			for(i=0;i<n;i++)
				if(stud[i].a>=a && stud[i].a<=b)
					tl[k++]=i;
			for(i=0;i<k;i++)
			{
				flag=0;
				for(j=0;j<k-i-1;j++)
				{
					if(stud[tl[j]].a<stud[tl[j+1]].a)
					{
						flag=1;
						temp=tl[j];
						tl[j]=tl[j+1];
						tl[j+1]=temp;
					}
				}
				if(!flag)
					break;
			}
		}
		else		
		if(sub==2)
		{
			k=0;
			for(i=0;i<n;i++)
				if(stud[i].s>=a && stud[i].s<=b)
					tl[k++]=i;
			for(i=0;i<k;i++)
			{
				flag=0;
				for(j=0;j<k-i-1;j++)
				{
					if(stud[tl[j]].s<stud[tl[j+1]].s)
					{
						flag=1;
						temp=tl[j];
						tl[j]=tl[j+1];
						tl[j+1]=temp;
					}
				}
				if(!flag)
					break;
			}
		}
		for(i=0;i<k;i++)
			disp(stud[tl[i]]);
		printf("\n");
		scanf("%d%d%d",&sub,&a,&b);
	}while(sub);
	return 0;	
}

