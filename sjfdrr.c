#include<stdio.h>
struct process
{
    char name;
    int at,bt,wt,tt,e,rt,rs,first,id,sp,ent,td,comp;
    float spf;
    int completed;
    float ntt;
}p[10];

int n,preid;
int q[100],q1[100],flag[10],first[10]; 
int front=-1,rear=-1,c=0,c1=0;
int front1=-1,rear1=-1;

void enqueue(int i)
{
    if(rear==20)
    printf("overflow");
    rear++;
    c++;
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
    else{
    front++;
}
c--;
    return temp;
}

void enqueue1(int i)
{
    if(rear1==20)
    printf("overflow1");
    rear1++;
    c1++;
    q1[rear1]=i;
    if(front1==-1)
    front1=0;
}

int dequeue1()
{
    if(front1==-1)
    printf("underflow1");
    int temp=q1[front1];
    if(front1==rear1)
    front1=rear1=-1;
    else
    front1++;
    c1--;
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

int isInQueue1(int i)
{
    int k;
    for(k=front1;k<=rear1;k++)
    {
        if(q1[k]==i)
        return 1;
    }
    return 0;
}

void sortbyarrival()
{
	int i,j;
    struct process temp;
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

int sort()
{
    int a[10],i,j=0,k=0,bmax=0;
    for(i=front;i<=rear;i++)
    {
        a[j]=p[q[i]].bt;
        if(a[j]>bmax)
        {
        	bmax=a[j];
		}
		j++;
		k++;
    }
    for(i=0;i<k;i++)
    {
        for(j=0;j<k;j++)
        {
            if(a[i]<a[j])
            {
                int t=a[i];
                a[i]=a[j];
                a[j]=t;
            }
        }
    }
    int m;
    if((k)%2==0)
    {
        m=(a[(k-1)/2]+a[(k+1)/2])/2;
    }
    else
    {
        m=a[(k)/2];
    }
    return (bmax+m)/2;
}

void sortspf()
{
	int i,j;
	for(i=front1;i<=rear1;i++)
	{
		for(j=i+1;j<=rear1;j++)
		{
			if(p[q1[i]].spf<p[q1[j]].spf)
			{
				int t=q1[i];
				q1[i]=q1[j];
				q1[j]=t;
			}	
		}	
	}	
}

void sortspf1()
{
	int i,j;
	for(i=front;i<=rear;i++)
	{
		for(j=i+1;j<=rear;j++)
		{
			if(p[q[i]].spf<p[q[j]].spf)
			{
				int t=q[i];
				q[i]=q[j];
				q[j]=t;
			}	
		}	
	}	
}

int tr()
{
	int i,j,cc=0;
	for(i=front;i<=rear;i++)
	{
		cc++;
	}
	return cc;
}
void main()
{
	int i,j,time=0,ttime=0,as[10],f[10],cs=0,c11=0;
	printf("Enter number of processes");
	scanf("%d",&n);
	for(i=0;i<n;i++)
	{
		printf("Enter Process id, Arrival Time and burst time\n");
		scanf("%d%d%d",&p[i].id,&p[i].at,&p[i].bt);
		printf("Enter Priority\n");
		scanf("%d",&p[i].e);
		ttime+=p[i].bt;
		as[i]=p[i].bt;
		p[i].rt=p[i].bt;
		f[i]=0;
		p[i].comp=0;
		p[i].first=0;
	}
	for(i=0;i<n;i++)
	{
		for(j=0;j<n;j++)
		{
			if(as[i]<as[j])
			{
				int o=as[i];
				as[i]=as[j];
				as[j]=o;
			}
		}
	}
	for(i=0;i<n;i++)
	{
		printf("%d ",as[i]);
	}
	printf("\n");
	int k=n;
	for(i=0;i<n;i++)
	{
		for(j=0;j<n;j++)
		{
			if(p[i].bt==as[j])
			{
				p[i].sp=(n-j);
			}
		}
	}
	
	for(i=0;i<n;i++)
	{
		printf("%d\t",p[i].sp);
		p[i].spf=(0.55*p[i].e)+(0.45*p[i].sp);
		printf("%f\t",p[i].spf);
	}
	printf("\n");
	
	sortbyarrival();
	int a=p[0].at;
	enqueue(0);
	//printf("Process execution order: ");
	for(i=1;i<n;i++)
	{
		if(p[i].at==a)
		{
			enqueue(i);	
		}	
	}
	int tq;
	sortspf1();
	while(time<ttime)
	{
		int tq=sort();
        printf("%d\n",tq);
        //printf("%d\t",c);
        int pp=tr();
        for(k=0;k<pp;k++)
        {
	        i=dequeue();
	        if(p[i].bt<=tq)
	        {       
				if(p[i].first==0)
				{
					p[i].rs=time;	
					p[i].first=1;
				}                   
	            time+=p[i].bt;
	            //printf(" %d ",p[i].id);
	            p[i].wt=time-p[i].rt-p[i].at;
	            p[i].td=time-p[i].at; 
				p[i].comp=1;   
				c11++;  
	            cs++;
	        }
	        else               
	        {
	        	if(p[i].first==0)
				{
					p[i].rs=time;
					p[i].first=1;	
				}
				//printf(" %d ",p[i].id);
	            time+=tq;
	            p[i].bt-=tq;
	            cs++;
	        }
        }
		for(i=0;i<n;i++)
		{
			if(p[i].at<=time && p[i].comp==0)
			{
				enqueue1(i);	
			}	
		}
		sortspf();
		if(c11<n)
		{
		for(i=front1;i<=rear1;i++)
		{
			//printf("%d\t%d",c1,q1[i]);
			enqueue(dequeue1());	
		}
	}
		printf("\n");
	}
	float avg_wt=0,avg_td=0,avg_rs=0;
	printf("Turn around time: ");
	for(i=0;i<n;i++)
	{
		printf("%d ",p[i].td);
	}
	printf("\n");
	printf("Response time: ");
	for(i=0;i<n;i++)
	{
		printf("%d ",p[i].rs);
	}
	printf("\n");
	printf("Waiting time: ");
	for(i=0;i<n;i++)
	{
		printf("%d\n",p[i].wt);
		avg_wt+=p[i].wt;
		avg_td+=p[i].td;
		avg_rs+=p[i].rs;
	}
	printf("Average Waiting time is %f",avg_wt/n);
	printf("Average Turnaround time is %f",avg_td/n);
	printf("Average Response time is %f",avg_rs/n);
}

