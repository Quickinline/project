#include<stdlib.h>
#include<stdio.h>
#include<math.h>
#include<string.h>
#include<stdbool.h>


/*
	To Compile In terminal:
	use 'gcc -o' and then,
	the name of the executable you want to generate
	and finally the source code name..
	example gcc -o program prog.c
*/


// Every node of a list is an AdjListNode
typedef struct AdjListNode AdjListNode;
struct AdjListNode
{
	int dest;
	AdjListNode* next;
};


//First Node of each Adjacency List
typedef struct AdjList AdjList;
struct AdjList
{
	int length;
	AdjListNode* start;
	int name;
};

//Graph is an Array of Adjacency Lists
typedef struct Graph Graph;
struct Graph
{
	AdjList* Array;
	int V;
};

bool isConnected (Graph* graph)
{
	//unfinished
}

void addAdjListNode (AdjList* list, int dest)
{
	if(list->start == NULL)
	{
		list->start=malloc(sizeof(AdjListNode));
		list->start->next = NULL;
		list->start->dest = dest;
		list->length = 1;
		return;
	}
	AdjListNode* pointer=list->start;

	while(pointer->next != NULL)
	{
		pointer = pointer->next;
	}

	pointer->next = malloc(sizeof(AdjListNode));
	pointer= pointer->next;
	pointer->dest = dest;
	pointer->next = NULL;

	list->length = list->length +1;

	return;
}

Graph* initGraph (int V)
{
	Graph* p = malloc(sizeof(Graph));
	p->V = V;
	p->Array = malloc(sizeof(AdjList)*(V+1));
	int i;
	for(i=0;i<V;i++)
	{
		p->Array[i].length = 0;
		p->Array[i].start = NULL;
		p->Array[i].name = 0;
	}

	return p;
}


Graph* CreateGraph (int V,int* names)
{
	Graph* p=initGraph(V);
	int i;
	for(i=0;i<V;i++)
	{
		p->Array[i].name = names[i];
	}
	return p;
}



void addEdge (Graph* graph, int source,int dest)
{
	int i=0;
	bool s=true,d=true, b =true;
	int sourceIndex,destIndex;
	while(i<graph->V && b)
	{
		if(graph->Array[i].name == source)
		{
			s=false;
			sourceIndex=i;
		}
		if(graph->Array[i].name == dest)
		{
			d=false;
			destIndex = i;
		}

		b = s||d;
		i++;
	}
	if(b) return;

	addAdjListNode(&(graph->Array[sourceIndex]),destIndex);
}

Graph* addVertex (Graph* graph, int name)
{
	int* names= malloc(sizeof(int)*(graph->V)+1);
	names[graph->V +1]=name;
	int i;
	for(i=0;i<graph->V;i++)
	{
		names[i]=graph->Array[i].name;
	}

	Graph* result = CreateGraph(graph->V,names);

	for(i=0;i<graph->V;i++)
	{
		result->Array[i].start = graph->Array[i].start;
		free(graph->Array);
		free(graph);
	}

	return result;
}

void listVertecies (Graph* graph)
{
	int i;
	printf("\nVertecies Listing: ");
	for(i=0;i<graph->V;i++)
	{
		printf("\n%d. vertex: %c",i+1,graph->Array[i].name);
	}
}

void listEdges (Graph* graph)
{
	int i,j;
	printf("\nEdge listing: " );

	for(i=0;i<graph->V;i++)
	{
		printf("\nEdges From: %c",graph->Array[i].name);
		AdjListNode* pointer = graph->Array[i].start;
		j=1;
		while(pointer != NULL)
		{
			printf("\n\t%d. From %c To: %c",j,graph->Array[i].name,graph->Array[pointer->dest].name);
			j++;
			pointer= pointer->next;
		}
	}
}



int main ()
{
	int names [5];
	int i;
	for(i=0;i<5;i++)
	{
		names[i]='A'+i;
	}
	Graph* p=CreateGraph(5,names);
	addEdge(p,'A','B');
	addEdge(p,'A','D');
	addEdge(p,'A','C');
	addEdge(p,'C','B');
	addEdge(p,'D','E');

	listVertecies(p);
	listEdges(p);

	p=addVertex(p,'H');
	printf("Adding vertex H\n");


	listVertecies(p);

	printf("\n");
	return 0;
}


