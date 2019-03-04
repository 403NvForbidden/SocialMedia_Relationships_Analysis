 // PQ ADT interface for Ass2 (COMP2521)
#include "PQ.h"
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

typedef struct PQRep {
	ItemPQ *items;
	int nitems;
	int nslots;
}PQRep;

static void fixUp(ItemPQ a[], int i);
static bool inPQ(PQ pq, ItemPQ element);
static void swap(ItemPQ a[],int i, int j);
static void fixdown(ItemPQ *a, int i, int N);

//checked
PQ newPQ() {
	PQ new = calloc(1,sizeof(PQRep));
	new->items = calloc(1000,sizeof(ItemPQ)); /////////////////
	new->nitems = new->nslots = 0;
	return new;
}

int PQEmpty(PQ p){
	if(p->nitems==0) return 1;
	return 0;
}

//checked
void addPQ(PQ pq, ItemPQ element) {
	assert(pq != NULL);
	// if element exist
	if (inPQ(pq,element)) {
		updatePQ(pq,element);
	} else {
		pq->nitems++;
		pq->items[pq->nitems] = element;
		fixUp(pq->items,pq->nitems);
	}
}
//checked
static bool inPQ(PQ pq, ItemPQ element) {
	int i;
	for(i=1;i<pq->nitems+1;i++){
		if(pq->items[i].key == element.key) return true;
	}
	return false;
}
//checked
static void fixUp(ItemPQ *a, int i) {
	while (i>1 && a[i/2].value > a[i].value) {
		swap(a,i,i/2);
		i/=2;
	}
}
//checked
ItemPQ dequeuePQ(PQ pq) {
	ItemPQ throwAway = {0};
	// last 
	throwAway = pq->items[1];
	pq->items[1] = pq->items[pq->nitems];
	pq->nitems--;
	//rearrange
	fixdown(pq->items,1,pq->nitems);
	return throwAway;
} 
//checked
static void fixdown(ItemPQ *a, int i, int N) {
	while (2*i<=N) {
		//left 
		int j = 2*i;
		//choose smaller of two children
		if (j < N && a[j].value > a[j+1].value) j++;
		if (a[i].value < a[j].value) break;
		swap(a,i,j);
		i = j;
	}
}

//checked
static void swap(ItemPQ a[],int i, int j) {
	ItemPQ tmp = a[i];
	a[i] = a[j];
	a[j] = tmp;
}
//checked
void updatePQ(PQ pq, ItemPQ element) {
	int i;
	for(i=1;i<pq->nitems+1;i++){
		if(pq->items[i].key == element.key) pq->items[i].value = element.value;
	}
}
//checked
void showPQ(PQ pq) {
	int i;
	for(i=1;i<pq->nitems+1;i++){
		printf("key is %d\tvalue is %d\n",pq->items[i].key,pq->items[i].value);
	}
}

void  freePQ(PQ pq) {
	free(pq->items);
	free(pq);
}
