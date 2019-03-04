#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <assert.h>
#ifndef GRAPH
	#define GRAPH
	#include "Graph.h"
#endif
#include "GraphVis.h"
#include "Dijkstra.h"
#include "PQ.h"
#include "LanceWilliamsHAC.h"

void showDendrogram(Dendrogram temp){
    if(!temp) return;
	printf("%d ",temp->vertex);
    showDendrogram(temp->left);
    showDendrogram(temp->right);
}

Graph readGraph(char* file) {
	// ugly count
	FILE * f = fopen(file , "r");
	if(!f){
		fprintf(stderr, "ERROR READING FILE %s\n", file);
		return NULL;
	}
	int lines = 0;
	char ch = 0;
	while(!feof(f)){ch = fgetc(f); if(ch == '\n')lines++;}
	fclose(f);

	//ugly parse
	f = fopen(file , "r");
	if(!f){
		fprintf(stderr, "ERROR READING FILE %s\n", file);
		return NULL;
	}
	int a=0;
	int b=0;
	int c=0;
	int i = 0;
	int maxVert = -1;
	int **nums = malloc(sizeof(int*)*lines);
	for(i=0;i<lines;i++) nums[i] = malloc(sizeof(int)*3);
	i=0;
	while(i < lines) {
		fscanf(f, "%d,", &a);
		fscanf(f, "%d,", &b);
		fscanf(f, "%d", &c);
		if (a > maxVert) maxVert = a;
		if (b > maxVert) maxVert = b;
		nums[i][0] = a;
		nums[i][1] = b;
		nums[i][2] = c;
		i++;
	}
	fclose(f);

	Graph g = newGraph(maxVert+1);
	i = 0;
	while(i < lines) {
		insertEdge(g,nums[i][0],nums[i][1],nums[i][2]);
		i++;
	}
	for(i=0;i<lines;i++) free(nums[i]);
	free(nums);
	return g;
}

int main(int argc, char* argv[]){
	if(argc < 2) {
		printf("Usage: ./testDijkstra [file]\n");
		return EXIT_FAILURE;
	}


    Graph g = readGraph(argv[1]);
    Dendrogram temp = LanceWilliamsHAC(g,2);
	// assert(temp!=NULL);
	printf("tree:\n");
    showDendrogram(temp);
	printf("\n");
	freeDendrogram(temp);
    return EXIT_SUCCESS;
}


