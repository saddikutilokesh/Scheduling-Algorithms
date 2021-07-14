#include<stdio.h>
struct process
{
    char name;
    int at,bt,wt,tt,rt,rs,first;
    int completed;
    float ntt;
}p[10];

int n;
int q[10]; 
int front=-1,rear=-1;

void enqueue(int i)
{
    if(rear==20)
    printf("overflow");
    rear++;
    q[rear]=i;
    if(front==-1)
    front=0;
}

int dequeue()
{
    if(front==-1)
    printf("underflow");
    int temp=q[front];
    if(front==rear)
    front=rear=-1;
    else
    front++;
    return temp;
}

int isInQueue(int i)
{
    int k;
    for(k=front;k<=rear;k++)
    {
        if(q[k]==i)
        return 1;
    }
    return 0;
}

void sortByArrival()
{
    struct process temp;
    int i,j;
    for(i=0;i<n-1;i++)
    for(j=i+1;j<n;j++)
    {
        if(p[i].at>p[j].at)
        {
            temp=p[i];
            p[i]=p[j];
            p[j]=temp;
        }
    }
}

void main()
{
    int i,j,time=0,sum_bt=0,tq;
    char c;
    float avgwt=0,tat=0;
    printf("Enter no of processes:");
    scanf("%d",&n);
    for(i=0,c='A';i<n;i++,c++)
    {
        p[i].name=c;
        printf("\nEnter the arrival time and burst time of process %c: ",p[i].name);
        scanf("%d%d",&p[i].at,&p[i].bt);
        p[i].rt=p[i].bt;
        p[i].completed=0;
        sum_bt+=p[i].bt;
        p[i].rs=0;
        p[i].first=0;
    }
    printf("\nEnter the time quantum:");
    scanf("%d",&tq);
    sortByArrival();
    enqueue(0);          
    printf("Process execution order: ");
    for(time=p[0].at;time<sum_bt;)  
    {   
        i=dequeue();
        if(p[i].rt<=tq)
        {
			if(p[i].first==0)
			{
				p[i].rs=time;
				p[i].first=1;	
			}                          
            time+=p[i].rt;
            p[i].rt=0;
            p[i].completed=1;         
            printf(" %c ",p[i].name);
            p[i].wt=time-p[i].at-p[i].bt;
            p[i].tt=time-p[i].at;
            for(j=0;j<n;j++)                
            {
                if(p[j].at<=time && p[j].completed!=1&& isInQueue(j)!=1)
                {
                    enqueue(j);
                }
            }
        }
        else               
        {
        	if(p[i].first==0)
			{
				p[i].rs=time;
				p[i].first=1;	
			}
            time+=tq;
            p[i].rt-=tq;
            if(p[i].rt<=tq)
            {
                time+=p[i].rt;
                p[i].rt=0;
                p[i].completed=1;         
                printf(" %c ",p[i].name);
                p[i].wt=time-p[i].at-p[i].bt;
                p[i].tt=time-p[i].at;
                for(j=0;j<n;j++)                
                {
                    if(p[j].at<=time && p[j].completed!=1&& isInQueue(j)!=1)
                    {
                        enqueue(j);
                    }
                }
            }
            else
            {
            printf(" %c ",p[i].name);
            for(j=0;j<n;j++)    
            {
                if(p[j].at<=time && p[j].completed!=1&&i!=j&& isInQueue(j)!=1)
                {
                    enqueue(j);
                }
            }
            enqueue(i);
            }
        }
}
printf("\nName\tArrival Time\tBurst Time\tWaiting Time\tTurnAround Time\tRespone time");
float res=0;
for(i=0;i<n;i++)
{
    avgwt+=p[i].wt;
    tat+=p[i].tt;
    res+=p[i].rs;
    printf("\n%c\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d",p[i].name,p[i].at,p[i].bt,p[i].wt,p[i].tt,p[i].rs);
}
    printf("\nAverage waiting time:%f\n",avgwt/n);
    printf("\nAverage turnaround time:%f\n",tat/n);
    printf("\nAverage resonse time:%f\n",res/n);
}
