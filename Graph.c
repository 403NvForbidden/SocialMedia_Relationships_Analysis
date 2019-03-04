// Graph ADT interface for Ass2 (COMP2521)
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "Graph.h"

typedef struct GraphRep{
	int nV;
	int nE;
	AdjList *edges;
}GraphRep;

typedef adjListNode* AdjListNode;

static AdjList insertAdjList(AdjListNode L, Vertex dest, int weight);
static void delAdjList(Graph g, Vertex src, Vertex dest);
static AdjListNode copyNode(AdjListNode N);
static AdjList copyList(AdjList L);

// checked
Graph newGraph(int noNodes) {
	int i;
	Graph new = calloc(1,sizeof(GraphRep));
	new->nV = noNodes; new->nE = 0;
	new->edges = calloc(noNodes,sizeof(AdjListNode));
	
	for(i=0;i<noNodes;i++) {
		new->edges[i] = NULL;
	}
	return new;
}
// checked
int numVerticies(Graph g) {
	return g->nV;
}
// checked
void insertEdge(Graph g, Vertex src, Vertex dest, int weight) {
	assert(g != NULL);

	if(!adjacent(g,src,dest)) {
		g->edges[src] = insertAdjList(g->edges[src],dest,weight);
		g->nE++;
	}
}
// checked
bool adjacent(Graph g, Vertex src, Vertex dest) {
	assert(g != NULL);
	AdjListNode curr;
	for(curr = g->edges[src]; curr; curr = curr->next) {
		if (curr->w == dest) return true;
	} 
	return false;
}
// checked
static AdjList insertAdjList(AdjListNode first, Vertex dest, int weight) {
	AdjListNode new = calloc(1,sizeof(AdjListNode));
	assert(new != NULL);
	new->w = dest;
	new->weight = weight;
	new->next = first;
	return new;
}

//checked
void removeEdge(Graph g, Vertex src, Vertex dest) {
	if(adjacent(g,src,dest)) {
		delAdjList(g,src,dest);
		g->nE--;
	}
}

//checked 
static void delAdjList(Graph g, Vertex src, Vertex dest) {
	AdjListNode curr,prev;
	for(curr=g->edges[src]; curr; curr = curr->next) {
		if (curr->w == dest){
			if (curr == g->edges[src]) {
				g->edges[src] = curr->next;
				free(curr);break;
			} else {
				prev->next = curr->next;
				free(curr);break;
			}
		}
		prev = curr;
	}
}

// checked
AdjList outIncident(Graph g, Vertex v) {
	assert(g!=NULL);
	AdjList first = copyList(g->edges[v]);
	return first;
}
static AdjList copyList(AdjList L) {
	if (!L) return NULL;

	AdjListNode new = malloc(sizeof(AdjListNode));
	new->w = L->w;
	new->weight = L->weight;
	new->next = copyList(L->next);
	return new;
}

//checked
AdjList inIncident(Graph g, Vertex v) {
	int i;
	AdjListNode temp;
	AdjList curr,first;
	first = NULL;

	for (i = 0; i < g->nV; i++){
		for(curr = g->edges[i]; curr; curr = curr->next) {
			if (curr->w == v && i != v) {
				// found, add to list
				if(!first) {
					first = temp = copyNode(curr);
				} else {
					temp->next = copyNode(curr);
					temp = temp->next;
				}
				temp->w = i;// change the vertex 
			}
		}
	}
	return first;
}

// checked
static AdjListNode copyNode(AdjListNode N){
	AdjListNode new = malloc(sizeof(AdjListNode));
	new->w = N->w;
	new->weight = N->weight;
	new->next = NULL;
	return new;
}

// checked
void  showGraph(Graph g) {
	if(!g)return;
	int i;
	for (i = 0; i < g->nV; i++) {
		AdjListNode curr = g->edges[i];
		printf("-----------------------\n");
		while(curr){
			printf("%d is connected to %d\n",i,curr->w);
			curr = curr->next;
		}
	}
}

void  freeGraph(Graph g) {
	int i;
	AdjListNode curr,prev;
    for (i = 0; i < g->nV; i++){
	   curr = g->edges[i];
	   while(curr){
		   prev = curr;
		   curr = curr->next;
		   free(prev);
	   }
    }
	free(g->edges);
	free(g);
}
