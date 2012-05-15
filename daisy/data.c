//
//  data.c
//  daisy
//Copyright (C) 2011  Nicolas Lorin

//This program is free software: you can redistribute it and/or modify
//it under the terms of the GNU General Public License as published by
//the Free Software Foundation, either version 3 of the License, or
//(at your option) any later version.

//This program is distributed in the hope that it will be useful,
//but WITHOUT ANY WARRANTY; without even the implied warranty of
//MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//GNU General Public License for more details.

//You should have received a copy of the GNU General Public License
//along with this program.  If not, see <http://www.gnu.org/licenses/>.

#include "data.h"

Data* ajoutFin(Data* teteliste, float t, float black, float white, float rabbit, float solar, float grey) {
	Data* q = (Data*) malloc(sizeof(Data));
	q->t = t;
	q->white = white;
	q->black = black;
	q->solar = solar;
    q->rabbit = rabbit;
    q->grey = grey;
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
		printf("Solar = %f Tmp = %f White = %f Black = %f Rabbit = %f Grey = %f\n\n", l->solar, l->t, l->white, l->black, l->rabbit, l->grey);
		l = l->next;
	}
}