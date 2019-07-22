#include<stdio.h>

struct student
{
	char rno[10];
	int a,s;
};

void disp(struct student temp)
{
	printf("    %s,  %d,  %d",temp.rno,temp.a,temp.s);
}

int main()
{
	int i,n,sub,a,b,tl[15],tla[15],tls[15],flag,j,k,temp,ba=0,bs=0,sc=0;
	struct student stud[15];
	scanf("%d",&n);
	printf("n = %d\n",n);
	for(i=0;i<n;i++)
	{	
		scanf("%s%d%d",stud[i].rno,&stud[i].a,&stud[i].s);
	}
	printf("+++ Initial list (sorted by roll numbers)\n");
	for(i=0;i<n;i++)
	{	
		disp(stud[i]);
		printf("\n");
	}
	printf("\n");
	printf("+++ Interval search\n\n");
	scanf("%d%d%d",&sub,&a,&b);
	do{
		if(sub==1)
		{
			printf("+++ Arts: a = %d, b = %d\n",a,b);
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
			printf("+++ Science: a = %d, b = %d\n",a,b);
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
		printf("--- List of students:\n");
		for(i=0;i<k;i++)
		{
			disp(stud[tl[i]]);
			printf("\n");
		}
		printf("\n");
		scanf("%d%d%d",&sub,&a,&b);
	}while(sub);
	for(i=0;i<n;i++)
		tl[i]=i;
	for(i=0;i<n;i++)
	{
		flag=0;
		for(j=0;j<n-i-1;j++)
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
	tla[tl[0]]=1;
	for(i=1;i<n;i++)
	{
		if(stud[tl[i]].a==stud[tl[i-1]].a)
			tla[tl[i]]=tla[tl[i-1]];
		else
			tla[tl[i]]=i+1;
	}	
	for(i=0;i<n;i++)
		tl[i]=i;
	for(i=0;i<n;i++)
	{
		flag=0;
		for(j=0;j<n-i-1;j++)
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
	tls[tl[0]]=1;
	for(i=1;i<n;i++)
	{
		if(stud[tl[i]].a==stud[tl[i-1]].a)
			tls[tl[i]]=tls[tl[i-1]];
		else
			tls[tl[i]]=i+1;
	}
	printf("+++ Rank comparisons\n");
	for(i=0;i<n;i++)
	{
		disp(stud[i]);
		printf(",  Arts rank = %d,  Science rank = %d,  Decision : ",tla[i],tls[i]);
		if(tla[i]<tls[i])
		{
			printf("BA\n");
			ba++;
		}
		else
		if(tla[i]>tls[i])
		{
			printf("BS\n");
			bs++;
		}
		else
		{
			printf("SC\n");
			sc++;
		}
	}
	printf("\n");
	printf("No. of BA = %d\n",ba);
	printf("No. of BS = %d\n",bs);
	printf("No. of SC = %d\n",sc);
	return 0;	
}

