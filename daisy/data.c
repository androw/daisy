//
//  data.c
//  daisy
//
//  Created by Nicolas LORIN on 03/04/11.
//  Copyright 2011 AndrowCorp. All rights reserved.
//

#include "data.h"

Data* ajoutFin(Data* teteliste, float t, float black, float white, float rabbit, float solar) {
	Data* q = (Data*) malloc(sizeof(Data));
	q->t = t;
	q->white = white;
	q->black = black;
	q->solar = solar;
    q->rabbit = rabbit;
	q->next = NULL;
	if (teteliste == NULL) {
		return q;
	} else {
		Data* l = teteliste;
		while (l->next != NULL) {
			l = l->next;
		}
		l->next = q;
		return teteliste;  
	}
}

int lenght(Data* teteliste) {
	int acc = 0;
	Data* l = teteliste;
	while (l != NULL) {
		acc++;
		l = l->next;
	}
	return acc;
}

void show(Data* tete) {
	Data* l = tete;
	while (l != NULL) {
		printf("Solar = %f Tmp = %f White = %f Black = %f Rabbit = %f\n\n", l->solar, l->t, l->white, l->black, l->rabbit);
		l = l->next;
	}
}