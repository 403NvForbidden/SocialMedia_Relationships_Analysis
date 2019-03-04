#ifndef GRAPH
	#define GRAPH
	#include "Graph.h"
#endif
#include "GraphVis.h"
#include "Dijkstra.h"
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

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
  Graph g = readGraph(argv[1]);

  // AdjList out = outIncident(g,2);

	// AdjList curr;
	// for(curr = out;curr;curr=curr->next){
	// 	printf("2 is following %d\n",curr->w);
	// }

  // AdjList in = inIncident(g,2);
	// AdjList cur;
	// for(cur = in;cur;cur=cur->next){
	// 	printf("2 is followed by %d\n",cur->w);
	// }
  
  graphVis(g,BETWEENNESS);
  free(g);
  return EXIT_SUCCESS;
}
/*
int main(){
	// some very simple code to show you
	// how to use graph vis

  Graph g = newGraph(5);
  insertEdge(g,1,2,1);
  insertEdge(g,2,1,10);
  insertEdge(g,4,2,60);
  insertEdge(g,3,2,6);
  showGraph(g);
  // free(g);
	// draws the graph
  // 
  // free(g);
  graphVis(g,DEFAULT);
  free(g);
  return EXIT_SUCCESS;
}
*/
// int main(int argc, char* argv[]){
// 	// some very simple code to show you
// 	// how to use graph vis

//   Graph g = newGraph(5);
// 	insertEdge(g,0,1,3);
//   insertEdge(g,1,2,1);
//   insertEdge(g,2,1,10);
// 	insertEdge(g,2,4,12);
// 	insertEdge(g,2,5,820);
//   insertEdge(g,4,2,60);
// 	insertEdge(g,3,2,6);
//   showGraph(g);

// 	printf("---------------test removeEdge----------------\n");
// 	removeEdge(g,2,5);
// 	removeEdge(g,2,1);
// 	showGraph(g);

// 	printf("---------------test in/out----------------\n");
// 	AdjList out = outIncident(g,2);

// 	AdjList curr;
// 	for(curr = out;curr;curr=curr->next){
// 		printf("2 is following %d\n",curr->w);
// 	}

// 	AdjList in = inIncident(g,2);
// 	AdjList cur;
// 	for(cur = in;cur;cur=cur->next){
// 		printf("2 is followed by %d\n",cur->w);
// 	}

// 	// draws the graph
// 	free(g);
	
//   // graphVis(g, DEGREE_IN);


// 	return EXIT_SUCCESS;
// }
