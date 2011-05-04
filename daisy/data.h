//
//  data.h
//  daisy
//
//  Created by Nicolas LORIN on 03/04/11.
//  Copyright 2011 AndrowCorp. All rights reserved.
//



#include <stdio.h>
#include <stdlib.h>

#ifndef HAS_DATA_H
#define HAS_DATA_H



typedef struct Data{
	float black;
	float white;
	float t;
    float rabbit;
	float solar;
    float grey;
	struct Data* next;
} Data;

Data* ajoutFin(Data* teteliste, float t, float black, float white, float rabbit, float solar, float grey);
int lenght(Data* teteliste);
void show(Data* tete);

#endif
