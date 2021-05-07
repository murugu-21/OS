#include<stdio.h>
#include<stdlib.h>
 
int mutex=1,full=0,empty=0,x=0;
 
int wait(int s)
{
    return (--s);
}
 
int signal(int s)
{
    return(++s);
}
 
void producer()
{
    mutex=wait(mutex);
    full=signal(full);
    empty=wait(empty);
    x++;
    printf("Producer produces the item %d",x);
    mutex=signal(mutex);
}
 
void consumer()
{
    mutex=wait(mutex);
    full=wait(full);
    empty=signal(empty);
    printf("Consumer consumes item %d",x);
    x--;
    mutex=signal(mutex);
}

int main()
{
    int n;
    void producer();
    void consumer();
    int wait(int);
    int signal(int);
    printf("Enter buffer size: ");
    scanf("%d", &empty);
    printf("\n1.Producer\n2.Consumer\n3.Exit");
    while(1)
    {
        printf("\nEnter your choice:");
        scanf("%d",&n);
        switch(n)
        {
            case 1:    
                if((mutex==1)&&(empty!=0))
                    producer();
                else
                    printf("Buffer is full!!");
                break;
            case 2:    
                if((mutex==1)&&(full!=0))
                    consumer();
                else
                    printf("Buffer is empty!!");
                break;
            default:
                exit(0);
        }
    }
    return 0;
}