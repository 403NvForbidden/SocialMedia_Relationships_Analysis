// LanceWilliamsHAC ADT interface for Ass2 (COMP2521)
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "Graph.h"
#include "Dijkstra.h"
#include "PQ.h"
#include "LanceWilliamsHAC.h"
#define INFINITY 1000000
#define min(k1,k2) ((k1>k2)*k2+(k1<k2)*k1)
#define max(k1,k2) ((k1<k2)*k2+(k1>k2)*k1)

typedef struct Cluster *Clusters;
typedef struct Cluster {
    int size;
    double **dist;
    Dendrogram *dendA;
} Cluster;

typedef struct GraphRep{
	int nV;
	int nE;
	AdjList *edges;
}GraphRep;

static Clusters Renew(Clusters old, int method);
static Clusters newCluster(int size);
static Dendrogram newDendrogram(int v);
static int findWeight(Graph g, Vertex src, Vertex dest);
static void freeCluster(Clusters throwaway);

Dendrogram LanceWilliamsHAC(Graph g, int method) {
    int src,dest;
    Clusters new;
    Clusters initial = newCluster(g->nV);
    double x,y;

    // initialise(tested)
    for(src=0;src<g->nV;src++){
        //create clusters for every vertex
        initial->dendA[src] = newDendrogram(src);
        //Calculate distances between each pair of vertices as described above.
        for (dest=src+1;dest<g->nV;dest++){
            x = findWeight(g,src,dest);
            y = findWeight(g,dest,src);
            if(x!=-1 || y!=-1) {
                if (x == y) {
                    initial->dist[src][dest] = 1/x;
                } else {
                    //pick the greater
                    initial->dist[src][dest] = 1/max(x,y);
                }
            }else{
                initial->dist[src][dest] = INFINITY;
            }
        }
    }

    //main loop
    int i;
    new = initial;
    for (i=1;i<g->nV-1;i++) { 
        new = Renew(new,method);
        assert(new != NULL);
    }

    Dendrogram finale = newDendrogram(-1);
    finale->left = new->dendA[0];
    finale->right = new->dendA[1];
    return finale;
}

static Clusters Renew(Clusters old, int method) {
    double min = INFINITY+1;
    int i,j,vertex1,vertex2,m,n;

    //find the smallest in array;
    for(i=0;i<old->size-1;i++){
        for (j=i+1;j<old->size;j++){
            if (min > old->dist[i][j]) {
                vertex1 = i;
                vertex2 = j;
                min = old->dist[i][j];
            } 
        }
    }
    //======================================================
    //vertex1 vertex2 will join a new cluster
    Clusters new = newCluster(old->size-1);

    // copy from old to new dist table
    m=0;
    for(i=0;i<old->size;i++){
        while(i==vertex1||i==vertex2)i++;
        if(!(i<old->size)) break;
        n=m+1;
        for (j=i+1;j<old->size;j++){
            while(j == vertex1 || j == vertex2)j++;
            if(!(j<old->size)) break;
            new->dist[m][n] = old->dist[i][j];
            n++;
        }
        // copy list
        new->dendA[m] = old->dendA[i];
        // old->dendA[vertex1];
        m++;
    }

    // leave the last of dendA and dist empty 
    //join two trees PS:m is the last index now
    new->dendA[m] = newDendrogram(-1);
    new->dendA[m]->left = old->dendA[vertex1];
    new->dendA[m]->right = old->dendA[vertex2];

    //deal with the rest of the dist table
    i = 0;
    for (j=0;j<old->size;j++){
        if(j == vertex1 || j == vertex2)continue;
        //compare 
        // if (i==vertex1 || i==vertex2) continue;
        double dist1 = old->dist[vertex1][j];
        double dist2 = old->dist[vertex2][j];
        if (old->dist[vertex1][j] == 0) dist1 = old->dist[j][vertex1];
        if (old->dist[vertex2][j] == 0) dist2 = old->dist[j][vertex2];
        
        if(dist1 == dist2) {
            new->dist[i][m] = dist1;
            i++;
        } else {
            //different method
            if (method ==1) {
                new->dist[i][m] = min(dist1,dist2);\
            } else if(method ==2){
                new->dist[i][m] = max(dist1,dist2);
            }
            i++;
        }

    }
    
    freeCluster(old);
    return new;
}

static Clusters newCluster(int size) {
    Clusters new = malloc(sizeof(Clusters));
    new->dist = malloc(size*sizeof(double));
    new->dendA = malloc(size*sizeof(Dendrogram));
    new->size = size;
    int i;
    for (i=0;i<size;i++){ 
        new->dist[i] = calloc(size,sizeof(double));
    }
    return new;
}

static void freeCluster(Clusters throwaway) {
    free(throwaway->dist);
    int i;
    // free(throwaway->dendA);
    // cannot free dendA later userd
    free(throwaway);
}

static Dendrogram newDendrogram(int v) {
    Dendrogram new = calloc(1,sizeof(Dendrogram));
    new->vertex = v;
    new->left = new->right = NULL;
    return new;
}

static int findWeight(Graph g, Vertex src, Vertex dest) {
	if (!adjacent(g,src,dest)) return -1;
	AdjList curr;
	for (curr = g->edges[src];curr;curr=curr->next){
		if (curr->w == dest) return curr->weight;
	}

	return -1;
}

void freeDendrogram(Dendrogram d) {
    if(!d) return; 
    freeDendrogram(d->left);
    freeDendrogram(d->right);
    free(d);
}
