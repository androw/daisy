//
//  data.h
//  daisy
//
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
