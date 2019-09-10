#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
void pagerank(int **graph,double alpha,int total_itr,int no_of_vertices);
int grphedges(int** graph,int i,int no_of_vertices)
{
	int j=0;
	int count=0;
	while(j<no_of_vertices)
	{
		if(graph[j][i]==1)
		{
			count++;
		}
		j++;
	}
	return count;
}
int grphcolumn(int** graph,int i,int j,int no_of_vertices)
{
	int track;
	track=graph[i][j];
	return track;
}
int main(int argc,char *argv[])
{
	FILE *fr1;
	fr1=fopen(argv[1],"r");
	int v=atoi(argv[2]);

	FILE *fr;
	fr=fopen(argv[1],"r");
	int i,j,k;
	int **graph=malloc(sizeof(int*)*v);
	for(k=0;k<v;k++)
	{
		graph[k]=(int*)malloc(sizeof(int)*v);
	}
	char line[80];
	i=0;
	while(fgets(line,80,fr)!=NULL)
	{
		char* tok=strtok(line," ");
		j=-1;
		while(tok!=NULL)
		{
			j++;
			graph[j][i]=atoi(tok);
			tok=strtok(NULL," ");
		}
		i++;
	}
	clock_t start,en;
	start = clock();

	printf("*******************************************************************************************\n");
	printf("For file %s\n", argv[1]);
	printf("Total Number of Pages = %d\n",v);
	printf("*******************************************************************************************\n");
	printf("Page rank\n");
	printf("--------------------------------------------------------------------------------------------\n");
	pagerank(graph,0.85,3,v);
	en=clock();

	printf("--------------------------------------------------------------------------------------------\n");
	printf("********************************************************************************************\n");
	printf("Running Time = %f\n",(float)(en-start)/(float)CLOCKS_PER_SEC);
	printf("********************************************************************************************\n");


	return 0;
}

void pagerank(int **graph,double alpha,int total_itr,int no_of_vertices)
{
	double scale=1.0/no_of_vertices;
	double *pagerank=(double*)malloc(sizeof(double)*no_of_vertices);
	double *last=(double*)malloc(sizeof(double)*no_of_vertices);
	int i;
	int j;
	for(i=0;i<no_of_vertices;i++)
	{
		pagerank[i]=scale;
		last[i]=0.0;
	}
	int iter=0,id=0;
	while(iter<total_itr)
	{
	for(i=0;i<no_of_vertices;i++)
	{
		last[i]=pagerank[i];
		pagerank[i]=0.0;
	}
	for(i=0;i<no_of_vertices;i++)
	{
		double total=0;
		for(j=0;j<no_of_vertices;j++)
		{
			if(grphcolumn(graph,i,j,no_of_vertices)==1)
			{
				total=total+((last[j])/(grphedges(graph,j,no_of_vertices)));//printf("hi %f %d %d %d %d %f    ", last[j],grphedges(graph,j,no_of_vertices),grphcolumn(graph,i,j,no_of_vertices),i,j,total);
			}
		}
		pagerank[i]=(total);
		printf("\n");
		//track1 =grphcolumn(graph,i,no_of_vertices);//checking indexs of 1's at every column
	}
	int pr_var=0;
	printf("Iteration no: %d\n", total_itr);
	while(pr_var<no_of_vertices)
	{
		printf("\nPage %d : %f",(pr_var+1),pagerank[pr_var]);
		pr_var++;
	}
	printf("\n");
	total_itr--;
}
}
