#include "PQ.h"
#include <stdlib.h>
#include <stdio.h>

int main(){

	PQ temp = newPQ();
	ItemPQ element = {1,1};
	ItemPQ element1 = {2,2};
	ItemPQ element2 = {5,12};
	ItemPQ element3 = {4,5};
	ItemPQ element4 = {10,4};
	ItemPQ element5 = {10,9};
	ItemPQ element6 = {22,1};
	int i,j;
	for(i=0; i<10;i++) {
		ItemPQ new = {i,i+1};
		addPQ(temp, new);
	}

	addPQ(temp, element);
	ItemPQ largest = dequeuePQ(temp);
	addPQ(temp, element2);
	addPQ(temp, element3);
	addPQ(temp, element4);
	addPQ(temp, element5);
	addPQ(temp, element6);
	showPQ(temp);
	printf("--------------test-----------------\n");
	ItemPQ c = dequeuePQ(temp);
	showPQ(temp);

	for(j=0; j<5;j++) {
		ItemPQ zzzz = dequeuePQ(temp);
		printf("-------\n");
		showPQ(temp);
	} 

	free(temp);

	return EXIT_SUCCESS;
} 
