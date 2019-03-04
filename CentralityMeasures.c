// Graph ADT interface for Ass2 (COMP2521)
#include "CentralityMeasures.h"
#include "Dijkstra.h"
#include "PQ.h"
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

typedef struct GraphRep{
	int nV;
	int nE;
	AdjList *edges;
}GraphRep;

// struct used to store both number of shortest paths 
//and the number of time through V
typedef struct Sigma {
   double	shortestPaths;
   double   throughV;
} Sigma;

typedef struct PredNode *predList;

static Sigma countShortestPaths (ShortestPaths paths, Vertex src, Vertex dest, int special);

NodeValues outDegreeCentrality(Graph g){
	NodeValues throwAway = {0};
	throwAway.noNodes = g->nV;
	throwAway.values = malloc(g->nV*sizeof(double));

	int i, count;
	AdjList curr;
	for(i = 0; i < g->nV; i++){
		count = 0;
		for(curr = outIncident(g,i);curr;curr=curr->next) count++;
		throwAway.values[i] = count;
	}
	return throwAway;
}

NodeValues inDegreeCentrality(Graph g){
	NodeValues throwAway = {0};
	throwAway.noNodes = g->nV;
	throwAway.values = malloc(g->nV*sizeof(double));

	int i, count;
	AdjList curr;
	count = 0;
	for(i = 0; i < g->nV; i++){
		count = 0;
		for(curr = inIncident(g,i);curr;curr=curr->next) count++;
		throwAway.values[i] = count;
	}
	return throwAway;
}

NodeValues degreeCentrality(Graph g) {

	NodeValues throwAway = {0};
	throwAway.noNodes = g->nV;
	throwAway.values = malloc(g->nV*sizeof(double));

	NodeValues in = inDegreeCentrality(g);
	NodeValues out = outDegreeCentrality(g);
	int i;
	for(i = 0; i < g->nV; i++){
		throwAway.values[i] = in.values[i] + out.values[i];
	}
	return throwAway;
}

NodeValues closenessCentrality(Graph g){
	NodeValues throwAway = {0};
	throwAway.noNodes = g->nV;
	throwAway.values = malloc(g->nV*sizeof(double));
	int i,j;
	double sum, reachNodes;
	double totalNodes = g->nV-1;

	for (i = 0; i < g->nV; i++){
		sum = reachNodes = 0;
		ShortestPaths paths = dijkstra(g, i);
		for(j = 0; j < g->nV; j++){
			//add up all the shortest paths
			sum += paths.dist[j];
			if (paths.dist[j] != 0)reachNodes++;
		}
		sum = (reachNodes/totalNodes)*(reachNodes/sum);
		if (reachNodes == 0) sum = 0;
		throwAway.values[i] = sum;
	}
	return throwAway;
}

static Sigma countShortestPaths(ShortestPaths paths, Vertex src, Vertex dest, int special) {
	Sigma pathsCount = {0};
	Sigma temp;

	if (paths.pred[dest] == NULL && src != dest) {
		pathsCount.shortestPaths = pathsCount.throughV = 0;
		return pathsCount;
	}
	
	if (paths.pred[dest] == NULL && src == dest) {
		pathsCount.shortestPaths = 1;
	} else {
		predList curr = paths.pred[dest];
		while(curr) {
			Vertex w = curr->v;
			temp = countShortestPaths(paths, src, w,special);
			pathsCount.shortestPaths += temp.shortestPaths;
			if (w==special) {
				pathsCount.throughV++;
				// if multiple child should count path many times
				pathsCount.throughV *= temp.shortestPaths;
			} 
			pathsCount.throughV += temp.throughV;
			curr = curr->next;
		}
	}
	return pathsCount;			
}

NodeValues betweennessCentrality(Graph g){
	NodeValues throwAway = {0};
	throwAway.noNodes = g->nV;
	throwAway.values = malloc(g->nV*2*sizeof(double));
	int src, dest,c;
	double denominator,numerator,sum;

	// c is the node that the path went through 
	for (c = 0; c <g->nV; c++) {
		sum = 0;
		for(src = 0; src <g->nV; src++){
			for(dest = 0; dest <g->nV; dest++){
				ShortestPaths paths = dijkstra(g,src);
				denominator = numerator = 0;
				if (src != dest && c != dest && c!=src) {
					Sigma temp = countShortestPaths(paths,src,dest,c);
					denominator = temp.shortestPaths;
					numerator = temp.throughV;
					if(denominator!=0) sum += numerator /denominator;
				}
			}
		}
		throwAway.values[c] = sum;
	}

	return throwAway;
}
 
NodeValues betweennessCentralityNormalised(Graph g){
	NodeValues throwAway = betweennessCentrality(g);
	throwAway.noNodes = g->nV;
	int c;
	for (c = 0; c <g->nV; c++) {
		throwAway.values[c] = throwAway.values[c]/(g->nV-1)/(g->nV-2);
	}
	return throwAway;
}


void showNodeValues(NodeValues values){
	int i;
	for(i=0;i<values.noNodes;i++){
		printf("%d: %f\n",i,values.values[i]);
	}
}

void freeNodeValues(NodeValues values){
	free(values.values);
}
