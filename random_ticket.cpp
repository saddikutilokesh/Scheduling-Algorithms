#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
int main()
{
	int n,i,j,k,temp=65,flag=0;
	char process[20];
	int brust[20],priority[20],pos,t,wait[20],ta[20],rs[20],first[20];
	int time=0,quantom,tbt=0;
	int z=0,lottery[20],ticket[20][20],q=0;
	printf("Enter Number Of Process: ");
	scanf("%d",&n);
	if(n<=0)
	{
		printf("\n\n Invalid Value Of Number Of Process");
		exit(0);
	}
	for(i=0;i<n;i++)
	{
		process[i] = temp;
		wait[i]=0;
		ta[i]=0;
		temp+=1;
	}
	for(i=0;i<n;i++)
	{
		printf("\nEnter The Brust Time For Process %c: ",process[i]);
		scanf("%d",&brust[i]);
		printf("Enter The Priority For Process %c(b/w 1 to %d): ",process[i],n);
		scanf("%d",&priority[i]);
		first[i]=0;
	}
	
	printf("%\nEnter time qunatum",quantom);
	scanf("%d",&quantom);
    for(i=0;i<n;i++)
    {
        pos=i;
        for(j=i+1;j<n;j++)
        {
            if(priority[j]<priority[pos])
                pos=j;
        }
 
        temp=process[i];
        process[i]=process[pos];
        process[pos]=temp;
 
        temp=brust[i];
        brust[i]=brust[pos];
        brust[pos]=temp;
 
        temp=priority[i];
        priority[i]=priority[pos];
        priority[pos]=temp;
        
        if(brust[i]<0)
		{
			flag = 1;
		}
    }
    
    if(flag==1)
    {
    	printf("\n\n  Invalid Time Entered \n");
    	exit(0);
	}
    
    printf("\n |Priority |  Process   |  Brust |");
	
	for(i=0;i<n;i++)
	{
		printf("\n |   %d \t   |    %c    \t|   %d    |",priority[i],process[i],brust[i]);
		tbt = tbt + brust[i];
	}
	

	int p=1,m_ticket=0;
	printf("\n\n\nPriority  process  Brust  Lottery  Tickets");
	for(i=0;i<n;i++)
	{
		lottery[i] =  priority[i];
		for (z=0;z<lottery[i];z++) 
		{
            ticket[i][z] = p++;
            m_ticket = p;
        }
      			
		printf("\n  %d\t    %c\t    %d \t    %d\t",priority[i],process[i],brust[i],lottery[i]);
		for(z=0;z<lottery[i];z++)
		{
			if(ticket[i][z]<10)
				printf("  %d ",ticket[i][z]);
			else
				printf("  %d",ticket[i][z]);
    	}   
	}
	
	while(time<tbt)
	{
	
	int winner = (rand()%m_ticket)+ 1;
    for(i =0;i<n;i++)
        for(z=0;z<lottery[i];z++)
            if(ticket[i][z]==winner)
                q=i;
                
    printf("\n\n-------------------------------------");
    printf("<<<<   Winner: %d   >>>>",winner);
    printf("-------------------------------------\n");
    if(first[q]==0)
    {
    	rs[q]=time;
    	first[q]=1;
	}
	
	if(brust[q]>0 && brust[q]>=quantom)
	{
		brust[q]-=quantom;
		time+=quantom;
		for(t=0;t<n;t++)
		{
			if(brust[t]>0 && t!=q)
			{
				wait[t]+=quantom;
			}
		}
		if(brust[q]==0)
		{
			ta[q]=time;
		}
		printf("\n\t\t\t\t  Process That Are Running Is: %c",process[q]);
	    printf("\n\t   (Total Time << Remaining Brust Time Of This Process << process ):  ( %d  <<  %d  <<  %c )\n",time,brust[q],process[q]);
      
	}
	else if(brust[q]>0 && brust[q]<quantom)
	{
		time+=brust[q];
		brust[q]=0;
		for(t=0;t<n;t++)
		{
			if(brust[t]>0 && t!=q)
			{
				wait[t]+=brust[q];
			}
		}
		if(brust[q]==0)
		{
			ta[q]=time;
		}
		printf("\n\t\t\t\t  Process That Are Running Is: %c",process[q]);
	    printf("\n\t   (Total Time << Remaining Brust Time Of This Process << process ):  ( %d  <<  %d  <<  %c )\n",time,brust[q],process[q]);
      
	}
    else
    {
    	printf("\n\t\t Related Process With This Ticket Has Been Completed");
	}
	printf("\n%d\n",time);
    
 }
 float avg_wait=0,avg_ta=0,avg_rs=0;
 for(i=0;i<n;i++)
 {
 	avg_wait+=wait[i];
 	avg_ta+=ta[i];
 	avg_rs+=rs[i];
 }
 printf("Waiting Time :");
 for(i=0;i<n;i++)
 {
 	printf("%d ",wait[i]);
 }
 printf("\n");
 printf("Turnaround Time :");
 for(i=0;i<n;i++)
 {
 	printf("%d ",ta[i]);
 }
 printf("\n");
 printf("Response Time :");
 for(i=0;i<n;i++)
 {
 	printf("%d ",rs[i]);
 }
 printf("\n");
 printf("\nAverage waiting time is %f\nAverage turn around time is %f\nAverage Response time is %f",avg_wait/n,avg_ta/n,avg_rs/n);
	
}
