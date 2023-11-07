#include<sys/types.h>
#include<sys/wait.h>
#include<stdio.h>
#include<stdlib.h>

void quicksort(int list[],int low,int high);
void sort(int array[20],int low,int high);
void merge(int array[20],int low,int mid,int high);

int main()
{
	//int pid;
	int list[50] ={0};
	int status;
	pid_t pid;

	int size,i;
	
	printf("\n\t Enter the number of elements: ");
	scanf("%d",&size);
	

	printf("\n\t Enter the elements to be sorted : \n");
	for(i=0;i<size;i++)
	{
		printf("\n\t Enter the %d element : \t",i+1);
		scanf("%d",&list[i]);
	}
	
	pid=fork();
	
	if(pid==0)
	{
		printf("\n-----Inside child-----\n");
		sort(list,0,size-1);
		printf("\nChild id %d",getpid());
		printf("\nparent id %d",getppid());
		
		
		printf("\n\tafter applying merge child\n");
		for(i=0;i<size;i++)
		{
			printf("%d\t",list[i]);
		}
		
		
	}
	else
	{
		wait(&status);
		printf("\n-----Inside parent-----\n");
		quicksort(list,0,size-1);
		printf("\nparent id %d",getpid());
		printf("\n\tafter applying quicksort parent\n");
		for(i=0;i<size;i++)
		{
			printf("\t%d\t",list[i]);
		}
	}
	
	
}

void quicksort(int list[],int low,int high)
{
	int pivot,i,j,temp;
	if(low < high)
	{
		pivot = low;
		i= low;
		j=high;
		while(i < j)
		{
			while(list[i] <= list[pivot] && i <= high)
			{
				i++;
			}
			while(list[j] > list[pivot] && i >= low)
			{
				j--;
			}
			if(i < j)//swp
			{
				temp = list[i];
				list[i] = list[j];
				list[j] = temp;
			}
		}
		temp=list[j];
		list[j]= list[pivot];
		list[pivot] = temp;
		quicksort(list,low,j-1);
		quicksort(list,j + 1,high);
	}
}

void sort(int array[20],int low,int high)
{
	int mid,num;
	if(low<high)
	{
		mid=(low+high)/2;
		sort(array,low,mid);
		sort(array,mid+1,high);
		merge(array,low,mid,high);
	}
	else
	{
		return;
	}
}


void merge(int array[20],int low,int mid,int high)
{
	int l1,l2,i,num;
	int b[20];
	for(l1=low,l2=mid+1,i=low;l1<=mid&&l2<=high;i++)
	{
		if(array[l1]<=array[l2])
			b[i]=array[l1++];
		else
			b[i]=array[l2++];
	}
	while(l1<=mid)
		b[i++]=array[l1++];
	while(l2<=high)
		b[i++]=array[l2++];
	for(i=low;i<=high;i++)
		array[i]=b[i];
}

