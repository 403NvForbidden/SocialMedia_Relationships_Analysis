// Dijkstra ADT interface for Ass2 (COMP2521)
#include "Dijkstra.h"
#include "PQ.h"
#include "Graph.h"
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#define INFINITY 1000000

typedef struct PredNode *predList;

typedef struct GraphRep{
	int nV;
	int nE;
	AdjList *edges;
}GraphRep;


static predList insertPredList(Vertex v);
static int findWeight(Graph g, Vertex src, Vertex dest);

static int findWeight(Graph g, Vertex src, Vertex dest) {
	if (!adjacent(g,src,dest)) return -1;
	AdjList curr;
	for (curr = g->edges[src];curr;curr=curr->next){
		if (curr->w == dest) return curr->weight;
	}

	return -1;
}


ShortestPaths dijkstra(Graph g, Vertex v) {
	int index,i;
	Vertex j;
	ShortestPaths throwAway = {0};
	throwAway.src = v;
	throwAway.pred = malloc(g->nV*sizeof(PredNode));
	throwAway.dist = malloc(g->nV*sizeof(int));
	throwAway.noNodes = g->nV;

	//initialise the PQ and dist matrix
	PQ TODO = newPQ();
	ItemPQ source = {v,0};

	for (i = 0;i < g->nV;i++){
		throwAway.dist[i] = INFINITY;
		throwAway.pred[i] = NULL;
	}
	addPQ(TODO,source);


	while(!PQEmpty(TODO)) {
		ItemPQ current_item = dequeuePQ(TODO);
		for (j = 0; j<throwAway.noNodes;j++) {
			//checking neighbours 
			if (adjacent(g, current_item.key, j)){
				//find the weight 
				int w = findWeight(g, current_item.key, j) + current_item.value;
				if (w <= throwAway.dist[j]) {
					//relaxation
					if (j!=v) {
						predList new = insertPredList(current_item.key);
						//weight = but not same vertex
						if (w == throwAway.dist[j] && throwAway.pred[j]->v != new->v) {
							//append this new node at the end (equivalent path)
							predList curr = throwAway.pred[j];
							while (curr->next) curr = curr->next;
							curr->next = new;
						} else {
							throwAway.pred[j] = new;
						}
						throwAway.dist[j] = w;
						ItemPQ element = {j,w};
						addPQ(TODO,element);
					}
				}
			}
		}
	}

	for (index = 0;index < g->nV;index++){
		if (throwAway.dist[index] == INFINITY) throwAway.dist[index] = 0;
	}
	return throwAway;
}

static predList insertPredList(Vertex v) {
	PredNode *new = calloc(1,sizeof(PredNode));
	assert(new != NULL); 
	new->v = v;
	new->next = NULL;
	return new;
}

void showShortestPaths(ShortestPaths paths) {
	// for shortest path from every vertex to src
	for (int dest = 0; dest< paths.noNodes;dest++){
		printf("Path from %d to %d:\n",paths.src,dest);

		int *p = malloc(paths.noNodes*sizeof(int)); 
		int curr,counter;
		curr = dest;
		for(counter = 0;curr != paths.src;counter++) {
			if (!paths.pred[curr]) break;
			p[counter] = curr;
			curr = paths.pred[curr]->v;
		}
		p[counter] = paths.src;

		for (int j =0;j < counter; j++) {
			printf("%d->",p[counter-j]);
		}
		printf("%d\n",dest);
		free(p);
	}
}

void  freeShortestPaths(ShortestPaths paths) {
	// 
	for(int i=0;i< paths.noNodes;i++){
		predList curr,prev;
		//also free list
		curr = paths.pred[i];
		while(curr){
			prev = curr;
			curr = curr->next;
			free(prev);
	   }
	}
	free(paths.dist);
	free(paths.pred);
}