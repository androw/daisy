//
//  main.c
//  daisy
//
//  Created by Nicolas LORIN on 03/04/11.
//  Copyright 2011 AndrowCorp. All rights reserved.
//

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "/opt/local/include/plplot/plplot.h"
#include "/opt/local/include/plplot/plevent.h"
#include "data.h"

Data* calcDaisy(float t_min, float t_max, float t_opti, float alb_white, float are_white, float alb_black, float are_black, float alb_ground, float S, float death, float solar_min, float solar_max, float solar_step, int rab, float are_rabbit, int gre, float alb_grey, float are_grey);
void plot(Data* values, int whi, int bla, int temp, int rab, int gre);


Data* calcDaisy(float t_min, float t_max, float t_opti, float alb_white, float are_white, float alb_black, float are_black, float alb_ground, float S, float death, float solar_min, float solar_max, float solar_step, int rab, float are_rabbit, int gre, float alb_grey, float are_grey) {
	Data* tete = NULL;
	float solar;
	float are_ground;
	float dare_black;
	float dare_white;
    float dare_rabbit;
    float dare_grey;
	float alb_globe;
	float t;
	float t_black;
	float t_white;
    float t_rabbit;
    float t_grey;
	float b_white;
	float b_black;
    float b_rabbit;
    float b_grey;
	int i;
	int So = 1000;
	float sigma = 5.67032*pow(10,-8);
	for (solar = solar_min; solar <= solar_max; solar = solar + solar_step) {
        if ((are_white < 0.01) && (are_white != 0)) {
            are_white = 0.01;
        }
        if ((are_black < 0.01) && (are_black != 0)) {
            are_black = 0.01;
        }
        if ((are_rabbit < 0.003) && (are_rabbit != 0)) {
            are_rabbit = 0.003;
        }
        if (!rab) are_rabbit = 0;
        
        if ((are_grey < 0.01) && (are_grey != 0)) {
            are_grey = 0.01;
        }
        if (!gre) are_grey = 0;
        
        are_ground = 1 - (are_white + are_black + are_rabbit + are_grey);
        
        i = 1;
        while (i <= 1000) {
            // Calc Global Albedo
            alb_globe = are_white * alb_white + are_black * alb_black + are_grey * alb_grey + are_ground * alb_ground;
            // Calc Global and Local Temperatures
            t = pow((solar * So * (1 - alb_globe) / sigma), 0.25);
            t_black = S * (alb_globe - alb_black) + t;
            t_white = S * (alb_globe - alb_white) + t;
            t_grey = S * (alb_globe - alb_grey) + t;
            t_rabbit = t;
            // Calc birthrate
            if ((rab) && (t_rabbit >= 273.15 + 5) && (t_rabbit <= 40 + 273.15) && (are_rabbit <= (are_white + are_black + are_grey)/3)) {
                b_rabbit = 1 - 0.003265 * pow(t_opti - t_rabbit, 2);
            } else {
                b_rabbit = 0;
            }
            if ((t_black >= t_min) && (t_black <= t_max) && (are_black >= 0.009)) {
                b_black = 1 - 0.003265 * pow(t_opti - t_black, 2) - b_rabbit/100;
            } else {
                b_black = 0;
            }
            if ((t_white >= t_min) && (t_white <= t_max) && (are_white >= 0.009)) {
                b_white = 1 - 0.003265 * pow(t_opti - t_white, 2) - b_rabbit/100;
            } else {
                b_white = 0;
            }
            
            if ((gre) && (t_grey >= t_min) && (t_grey <= t_max) && (are_grey >= 0.009)) {
                b_grey = 1 - 0.003265 * pow(t_opti - t_grey, 2) - b_rabbit/100;
            } else {
                b_grey = 0;
            }
            // Save Data
            //if (rab && gre) {
                tete = ajoutFin(tete, t, are_black, are_white, are_rabbit, solar, are_grey);
            //} else {
            //    tete = ajoutFin(tete, t, are_black, are_white, 0, solar, 0);
            //}
            // Calc changes
            dare_black = are_black*(b_black * are_ground - death);
            dare_white = are_white*(b_white * are_ground - death);
            if (rab) {
                dare_rabbit = are_rabbit*(b_rabbit * are_ground - 0.03);
            } else {
                dare_rabbit = 0;
            }
            if (gre) {
                dare_grey = are_grey*(b_grey * are_ground - death);
            } else {
                dare_grey = 0;
            }
            
            // Does it converge ?
            if ((fabs(dare_white) < 0.000001) && (fabs(dare_black) < 0.000001) && (fabs(dare_rabbit) < 0.1) && (fabs(dare_grey) < 0.000001)) {
                are_black = are_black + dare_black;
                are_white = are_white + dare_white;
                are_rabbit = are_rabbit + dare_rabbit;
                are_grey = are_grey + dare_grey;
                are_ground = 1 - (are_black + are_white + are_rabbit + are_grey);
                break;
            } else {
                are_black = are_black + dare_black;
                are_white = are_white + dare_white;
                are_rabbit = are_rabbit + dare_rabbit;
                are_grey = are_grey + dare_grey;
                are_ground = 1 - (are_black + are_white + are_rabbit + are_grey);
                //printf("DEBUG");
            }
            i++;
        }
	}
	return tete;
    
}

void plot(Data* values, int whi, int bla, int temp, int rab, int gre) {
	int i;
    PLFLT x[1000], y[1000], w[1000], z[1000], t[1000], g[1000];
	PLFLT xmin, xmax, ymin, ymax, tmin, tmax;
	
	Data* l = values;
	//int le = lenght(values);
	int le = 500;
	for (i = 0; i<le; i++) {
		
		x[i] = l->solar;
        
		while ((x[i] == l->solar) && (l != NULL)) {
            w[i] = l->rabbit;
            g[i] = l->grey;
            z[i] = l->black;
            y[i] = l->white;
            t[i] = l->t;
			l = l->next;
		}
	}
	
	xmin = x[0];
	xmax = x[le-1];
	ymin = 0;
	ymax = 1;
	tmin = t[0];
	tmax = t[le-1];
	
	if (whi) {
        plcol0( 1 );
        plenv(xmin, xmax, ymin, ymax, 0, 0);
        plcol0( 2 );
        pllab( "Solar luminosity", "White daisies", "#frWhite daisies coverage over time" );
	
        plcol0(3);
        plline(le, x, y);
    }
	
	if (bla) {
        plcol0( 1 );
        plenv(xmin, xmax, ymin, ymax, 0, 0);
        plcol0( 2 );
        pllab( "Solar luminosity", "Black daisies", "#frBlack daisies coverage over time" );
	
        plcol0(3);
        plline(le, x, z);
    }
    
    if (gre) {
        plcol0( 1 );
        plenv(xmin, xmax, ymin, ymax, 0, 0);
        plcol0( 2 );
        pllab( "Solar luminosity", "Grey daisies", "#frGrey daisies coverage over time" );
        
        plcol0(3);
        plline(le, x, g);
    }
    
    if (rab) {
        plcol0( 1 );
        plenv(xmin, xmax, ymin, ymax , 0, 0);
        plcol0( 2 );
        pllab( "Solar luminosity", "Rabbits", "#frRabbits coverage over time" );
	
        plcol0(3);
        plline(le, x, w);
    }
	
	if (temp) {
        plcol0( 1 );
        plenv(xmin, xmax, tmin, tmax, 0, 0);
        plcol0( 2 );
        pllab( "Solar luminosity", "Temperature", "#frGlobal temperature over time" );
	
        plcol0(3);
        plline(le, x, t);
    }
}



int main (int argc, const char * argv[])
{
    int grey = 1;
    int rabb = 1;
    Data* values = calcDaisy(5+273.15, 40+273.15, 22.5+273.15, 0.75, 0.01, 0.25, 0.01, 0.5, 20, 0.3, 0.5, 1.6, 0.002, rabb, 0.003, grey, 0.5, 0.01);
	//show(values);
	
	char  ver[80];
	plgver( ver );
    printf("PLplot library version: %s\n", ver );
    
    plstar(1, 3+rabb+grey);
    
    plot(values, 1, 1, 1, rabb, grey);
    
    plend();
    return 0;
}

