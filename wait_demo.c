#include<stdio.h>
#include<sys/types.h>

void quick(int a[10],int f,int l)	
{
	int i,j,p,temp,k=1;		
	p=i=f;
	j=l;
	if(i<j)
	{
	while(i<j) 			
	{
	
		while(a[i]<=a[p])	
		{	
			i++;
		}
		while(a[j]>a[p])	
		{
			j--;
		}
		if(i<j)			
		{
		temp=a[i];
		a[i]=a[j];
		a[j]=temp;
		}
	}
	
		temp=a[p];
		a[p]=a[j];
		a[j]=temp;
	
		
		quick(a,f,j-1);	
		quick(a,j+1,l);
	}
	
}

void merge(int low,int high, int mid,int b[10])		
{
	int l1,l2,i,c[10];
	for(l1=low,l2=mid+1,i=low;l1<=mid && l2<=high;i++)
	{
		if(b[l1]<=b[l2])
			c[i]=b[l1++];
		else
			c[i]=b[l2++];
	}
	while(l1<=mid)
	c[i++]=b[l1++];
	while(l2<=high)
	c[i++]=b[l2++];
	
	for(i=low;i<=high;i++)
		b[i]=c[i];
}

void sort(int low,int high,int b[10])
{
	int mid;
	if(low<high)
	{
		mid=(low+high)/2;
		sort(low,mid,b);
		sort(mid+1,high,b);
		merge(low,high,mid,b);
	}
}

 main()
{
	int c,a[10],n,i,l,b[10],d[10],status;
	pid_t pid;			
	
	printf("\nEnter the number of integers to be sorted: ");
	scanf("%d",&n);
	
	printf("\nEnter the integers: ");
	
	for(i=0;i<n;i++)
	scanf("%d",&a[i]);
	
	pid=fork();			
	if(pid==0)
	{
		
		l=n-1;
			quick(a,0,l);		
			printf("\nSorted array using quick sort is :");
		for(i=0;i<=l;i++)
		printf("%d\n",a[i]);
		
		printf("\n");
	}
  	
	else
	{
		wait(&status);
		l=n-1;
			sort(0,n-1,a);		
			printf("\nSorted array using merge sort is :");
			
		for(i=0;i<=l;i++)
		printf("%d\n",a[i]);
		printf("Exit child status:%d",status);
		}
	
}


