#include<stdio.h>

int n,preid;
int q[10],flag[10],bt[10],first[10]; 
int front=-1,rear=-1,n;

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

int tr()
{
    int c=0,i;
    for(i=0;i<n;i++)
    {
        if(flag[i]==0)
        {
            c++;
        }
    }
    return c;
}

int sort()
{
    int a[10],i,j,k=0,bmax=0;
    for(i=0;i<n;i++)
    {
        if(flag[i]==0)
        {
            a[k++]=bt[i];
            if(bt[i]>bmax)
            {
                bmax=bt[i];
            }
        }
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
        m=(a[k-1/2]+a[(k+1)/2])/2;
    }
    else
    {
        m=a[(k)/2];
    }
    return (bmax+m)/2;
}

void main()
{
    int p[10],at[10],up[10],sp[10],tt[10],pid[10],sum=0,wt[10],td[10],cs=0,rt[10];
    float spf[10],spf1[10],tat=0;
    int i,j;
    int tq;
    float avgwt;
    printf("Enter number of processes");
    scanf("%d",&n);
    for(i=0;i<n;i++)
    {
        printf("Enter process id");
        scanf("%d",&pid[i]);
        printf("Enter burst time and user priority");
        scanf("%d%d",&bt[i],&up[i]);
        at[i]=0;
        flag[i]=0;
        tt[i]=bt[i];
        sum+=bt[i];
        rt[i]=bt[i];
    }

    for(i=0;i<n;i++)
    {
        for(j=0;j<n;j++)
        {
            if(tt[i]<tt[j])
            {
                int t=tt[i];
                tt[i]=tt[j];
                tt[j]=t;
            }
        }
    }
    
    int k=n;
    for(i=0;i<n;i++)
    {
        for(j=0;j<n;j++)
        {
            if(tt[i]==bt[j])
            {
                sp[j]=k--;
            }
        }
    }
    
    for(i=0;i<n;i++)
    {
        spf[i]=(sp[i]*0.45)+(up[i]*0.55);
        spf1[i]=spf[i];
    }
    
    for(i=0;i<n;i++)
    {
        printf("%0.2f ",spf[i]);
    }
    
    for(i=0;i<n;i++)
    {
        for(j=0;j<n;j++)
        {
            if(spf1[i]>spf1[j])
            {
                int t=pid[i];
                pid[i]=pid[j];
                pid[j]=t;
                int u=bt[i];
                bt[i]=bt[j];
                bt[j]=u;
                float z=spf1[i];
                spf1[i]=spf1[j];
                spf1[j]=z;
                int x=rt[i];
                rt[i]=rt[j];
                rt[j]=x;
            }
        }
    }
    
    for(i=0;i<n;i++)
    {
        printf("%0.2f ",spf1[i]);
    }
    /*for(i=0;i<n;i++)
    {
        printf("%d ",pid[i]);
    }*/
    enqueue(0);
    k=1;
    int time;
    for(time=0;time<sum;)
    {
        tq=sort();
        int tot=tr();
        for(k=0;k<tot;k++)
        {
        i=dequeue();
        if(bt[i]<=tq)
        {                          
            time+=bt[i];
            flag[i]=1;
            if(preid!=pid[i])
            wt[i]=time-rt[i];
            else wt[i]=first[i];
            td[i]=time;      
            for(j=0;j<n;j++)                
            {
                if(flag[j]!=1 && isInQueue(j)!=1)
                {
                    enqueue(j);
                }
            }
            cs++;
        }
        else               
        {
            first[i]=time;
            time+=tq;
            bt[i]-=tq;
            for(j=0;j<n;j++)    
            {
                if(flag[j]!=1 && i!=j && isInQueue(j)!=1)
                {
                    enqueue(j);
                }
            }
            enqueue(i); 
            cs++;
        }
        preid=pid[i];
        }
    }
    for(i=0;i<n;i++)
    {
        printf("%d ",wt[i]);
        avgwt+=wt[i];
        tat+=td[i];
    }
    printf("\nAverage waiting time:%f\n",avgwt/n);
    printf("\nAverage turn around time:%f\n",tat/n);
	printf("Number of context switches:%d",cs-1);
}
