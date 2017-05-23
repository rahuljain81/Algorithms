/* 
 * C Program to Implement Priority Queue to Add and Delete Elements
 */
#include <stdio.h>
#include <stdlib.h>
 
#define MAX 5
int pri_que[MAX];
int front, rear;
void display_pqueue();
 
void insert_by_priority(int data)
{
	int i, j;
	if (rear == -1 && front == -1)
	{
		rear++;
		front++;
		pri_que[rear] = data;
	}
	else
	{
		if (rear+1 == MAX)
		{
			printf ("Q is full\n");
			display_pqueue();
		}
		else
		{
			rear+=1;
			for (i=0; i <= rear; i++)
				if (pri_que[i] > data)
				{
					for (j=i; j <= rear; j++)
						pri_que[j+1] = pri_que[j];
					pri_que[i]=data;
					return;
				}
		}
	}
}
void delete_by_priority(int data)
{
	int i;
	if (front == -1 && rear == -1)
		printf ("No Elements to delete\n");
	else
	{
		for (i=0; i <= rear; i++)
		{
			if (pri_que[i] == data)
			{
				for (; i <= rear; i++)
				{
					pri_que[i] = pri_que[i+1];
				}
				rear--;
			}
			if (rear == -1)
				front = -1;
		}
	}
}
void create()
{
	front = rear = -1;
}
void display_pqueue()
{
	int i;
	if (front == -1 && rear == -1)
		printf ("No Elements to delete\n");
	else
	{
		printf ("front %d rear %d\n", front, rear);
		for (i=0; i <= rear; i++)
			printf ("[%d] ", pri_que[i]);
		printf ("\n");
	}
}
 
 
int main()
{
    int n, ch;
 
    printf("\n1 - Insert an element into queue");
    printf("\n2 - Delete an element from queue");
    printf("\n3 - Display queue elements");
    printf("\n4 - Exit");
 
    create();
 
    while (1)
    {
        printf("\nEnter your choice : ");    
        scanf("%d", &ch);
 
        switch (ch)
        {
        case 1: 
            printf("\nEnter value to be inserted : ");
            scanf("%d",&n);
            insert_by_priority(n);
            break;
        case 2:
            printf("\nEnter value to delete : ");
            scanf("%d",&n);
            delete_by_priority(n);
            break;
        case 3: 
            display_pqueue();
            break;
        case 4: 
            exit(0);
        default: 
            printf("\nChoice is incorrect, Enter a correct choice");
        }
    }
	return 0;
}


 


