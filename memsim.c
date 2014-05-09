/*
 *Copyright (C) 2013, Longsheng(lozhou@ucalgary.ca).
 *
 *Program that simulate page replacement algorithms-FIFO and LRU.
 */

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<time.h>
#include<string.h>
#include <getopt.h>

/*Traverse all physical frames*/
int Travel(int bc[],int frameCount,int x)   
{   
  int temp=0;   
  int i;   
  for(i=0;i<frameCount;i++)
    {   
      if(bc[i]==x){   
	temp=1;   
	break;   
      }   
    }   
  return temp;   
}   

/*When starting state is COLD*/
void FIFO(int pc[],int bc[],int pageCount,int frameCount)   
{    
  int i;   
  if(pageCount<=frameCount)
    {   
      printf("Page Faults:0\n");  
    }   
  else
    {   
      int noPage=0;   
      int p=0;   
      for(i=0;i<pageCount;i++)
	{      
	  if(!Travel(bc,frameCount,pc[i]))
	    {   
	      if(i<frameCount)  
		bc[i]=pc[i];      
	      else
		{   
		  if(p==frameCount)
		    {   
		      p=0;   
		    }   
		  bc[p]=pc[i];   
		  p++;  
		}   
	      noPage++;      
	    }   
	}   
      printf("Page Fault: %d\n",noPage);
    }   
} 

/*When starting state is HOT*/
void FIFO2(int pc[],int bc[],int pageCount,int frameCount)   
{    
  int i,j;  
  if(pageCount<=frameCount)
    {   
      printf("Page Faults:0\n");  
    }   
  else
    {   
      int noPage=0;   
      int p=0; 
      
      /*map virtal pages to physical before simulation*/
      for(j=0;j<frameCount;j++)
	{
	  bc[j]=pc[j];
	}
      
      for(i=frameCount;i<pageCount;i++)
	{      
	  if(!Travel(bc,frameCount,pc[i]))
	    {   
	      if(i<frameCount)  
		bc[i]=pc[i];      
	      else
		{   
		  if(p==frameCount)  
		      p=0;    
		  bc[p]=pc[i];   
		  p++;  
		}   
	      noPage++;      
	    }   
	}   
      printf("Page Fault: %d\n",noPage);
    }   
}  

int FoundMaxNum(int a[],int n)   
{   
  int i, k,j;   
  k=a[0];   
  j=0;   
  for(i=0;i<n;i++)
    {   
      if(a[i]>=k)
	{   
	  k=a[i];   
	  j=i;   
	}   
    }   
  return j;   
}   

/*When starting state is COLD*/
void LRU(int pc[],int bc[],int pageCount,int frameCount)   
{      
  if(pageCount<=frameCount)
    {   
      printf("Page Fault: 0\n");   
    }   
  else
    {   
      int noPage=0;   
      int i,j,m;   
      int bc1[frameCount];   
      for(i=0;i<frameCount;i++)
	{   
	  bc1[i]=0;   
	}   
      for(i=0;i<pageCount;i++)
	{     
	  if(!Travel(bc,frameCount,pc[i]))
	    {   
	      if(i<frameCount)
		{   
		  bc[i]=pc[i];
		  int p;   
		  for(p=0;p<=i;p++)
		    {   
		      bc1[p]++;   
		    }   
		}   
	      else
		{   
		  for(j=0;j<frameCount;j++)
		    {   
		      bc1[j]++;   
		    }   
		  int k=FoundMaxNum(bc1,frameCount);   
		  bc[k]=pc[i];   
		  bc1[k]=1;
		}   
	      noPage++;     
	    }
	  
	  else if(Travel(bc,frameCount,pc[i]))   
            {   
	      if(i<frameCount)   
                {   
		  for(j=0;j<=i;j++)   
                    {   
		      bc1[j]++;   
                    }   
		  for(m=0;m<=i;m++)   
                    {   
		      if(bc[m]==pc[i])   
                        {   
			  break;   
                        }   
                    }   
		  bc1[m]=1;   
		  bc[m]=pc[i];   
		  
                }   
	      else  
                {   
		  for(j=0;j<frameCount;j++)   
                    {   
		      bc1[j]++;   
                    }   
		  for(m=0;m<frameCount;m++)   
                    {   
		      if(bc[m]==pc[i])   
                        {   
			  break;   
                        }   
                    }   
		  bc1[m]=1;   
		  bc[m]=pc[i];   
                }   
            }   
        }   
      printf("Page Faults:%d\n",noPage);    
    }   
} 

/*When starting state is HHOT*/
void LRU2(int pc[],int bc[],int pageCount,int frameCount)   
{      
  if(pageCount<=frameCount)
    {   
      printf("Page Fault: 0\n");   
    }   
  else
    {   
      int noPage=0;   
      int i,j,m,k;   
      int bc1[frameCount];   
      for(i=0;i<frameCount;i++)
	{   
	  bc1[i]=0;   
	}
      
      /*map virtal pages to physical before simulation*/
      for(k=0;k<frameCount;k++)
	{
	  bc[k]=pc[k];
	}
      
      for(i=frameCount;i<pageCount;i++)
	{     
	  if(!Travel(bc,frameCount,pc[i]))
	    {   
	      if(i<frameCount)
		{   
		  bc[i]=pc[i];
		  int p;   
		  for(p=0;p<=i;p++)
		    {   
		      bc1[p]++;   
		    }   
		}   
	      else
		{   
		  for(j=0;j<frameCount;j++)
		    {   
		      bc1[j]++;   
		    }   
		  int k=FoundMaxNum(bc1,frameCount);   
		  bc[k]=pc[i];   
		  bc1[k]=1;
		}   
	      noPage++;     
	    }
	  
	  else if(Travel(bc,frameCount,pc[i]))   
            {   
	      if(i<frameCount)   
                {   
		  for(j=0;j<=i;j++)   
                    {   
		      bc1[j]++;   
                    }   
		  for(m=0;m<=i;m++)   
                    {   
		      if(bc[m]==pc[i])   
                        {   
			  break;   
                        }   
                    }   
		  bc1[m]=1;   
		  bc[m]=pc[i];   
		  
                }   
	      else  
                {   
		  for(j=0;j<frameCount;j++)   
                    {   
		      bc1[j]++;   
                    }   
		  for(m=0;m<frameCount;m++)   
                    {   
		      if(bc[m]==pc[i])   
                        {   
			  break;   
                        }   
                    }   
		  bc1[m]=1;   
		  bc[m]=pc[i];   
                }   
            }   
        }   
      printf("Page Faults:%d\n",noPage);    
    }   
}   
  

/*sequence ofmemory reference*/
static int pc[100000];

#define random(x) (rand()%x)

int main(int argc, char *argv[])   
{
  int opt = 0;
  char alg_FIFO[4]={'F','I','F','O'};
  char alg_LRU[3]={'L','R','U'};
  char HOT[3]={'H','O','T'};
  char COLD[4]={'C','O','L','D'};

  int pageSize;/*the size of virtual memory, in pages*/
  int frameCount;/*the number of available "physical page frames"*/
  int pageCount=100000;
  int bc[pageCount];
  char *alg;
  char *key;

  /*Options setting*/
  static struct option long_options[] = {
    {"virt",  required_argument, 0,  'v' },
    {"phy",   required_argument, 0,  'p' },
    {"alg",   required_argument, 0,  'a' },
    {"state", required_argument, 0,  's' }
  };
  
  int long_index =0;
  opt = getopt_long(argc,argv,"v:p:a:s:", long_options, &long_index);
  while(opt != -1)
    {
      switch(opt)
	{
	case 'v':
	  pageSize=atoi(optarg);
	  break;

	case 'p':
	  frameCount=atoi(optarg);
	  break;

	case 'a':
	  alg=strdup(optarg);
	  break;
	  
	case 's':
	  key=strdup(optarg);
	  break;	
	}
      opt = getopt_long(argc,argv,"v:p:a:s:", long_options, &long_index);  
    }

  /*producing a random sequence of memory reference*/
  srand((int)time(0));
 
  int i;
  for(i=0; i<pageCount; i++)
    {
      pc[i]=random(pageSize);
    }

  if(alg_FIFO[0]==alg[0]&&alg_FIFO[1]==alg[1]&&alg_FIFO[2]==alg[2]&&alg_FIFO[3]==alg[3])
    {
      if(key[0]==COLD[0])
	  FIFO(pc,bc,pageCount,frameCount);
      else if(key[0]==HOT[0])
	  FIFO2(pc,bc,pageCount,frameCount);
      else
	  printf("State error, please input the right state (HOT, COLD).");    
    }

  else if(alg_LRU[0]==alg[0]&&alg_LRU[1]==alg[1]&&alg_LRU[2]==alg[2])
    {
      if(key[0]==COLD[0])
	  LRU(pc,bc,pageCount,frameCount);
      else if(key[0]==HOT[0])
	  LRU2(pc,bc,pageCount,frameCount);
      else
	  printf("State error!\nPlease Choose the Right state (HOT, COLD).\n");     
    }

  else
    printf("Algorithm Error!\nPlease Choose the Right Algorithm (FIFO, LRU)!\n");

  return 0;
}
