/* Computer Graphics, Assignment 1, Bresenham's Midpoint Line-Algorithm
 *
 * Filename ........ mla.c
 * Description ..... Midpoint Line Algorithm
 * Created by ...... Jurgen Sturm
 *
 * Student name .... David van Erkelens & Jelte Fennema
 * Student email ... info@davidvanerkelens.nl, me@jeltef.nl
 * Collegekaart .... 10264019,
 * Date ............ 07/02/2013
 * Comments ........ Enjoy!
 *
 *
 *
 * (always fill in these fields before submitting!!)
 */

#include <stdlib.h>
#include "SDL.h"
#include "init.h"

int getValue(int x, int y, int x0, int x1, int y0, int y1);

/*
 * Midpoint Line Algorithm
 *
 * As you probably will have figured out, this is the part where you prove
 * your programming skills. The code in the mla function should draw a direct
 * line between (x0,y0) and (x1,y1) in the specified color.
 *
 * Until now, the example code below draws only a horizontal line between
 * (x0,y0) and (x1,y0) and a vertical line between (x1,y1).
 *
 * And here the challenge begins..
 *
 * Good luck!
 *
 *
 */
void mla(SDL_Surface *s, int x0, int y0, int x1, int y1, Uint32 colour) {    
    int ix,iy,tx,ty,ri;
    /* Calculate the slope */
    double rico = (double)((-1*y1)-(-1*y0))/(double)(x1-x0);
    tx = x0;
    ty = y0;
    /* Calculate if x and y need to be positive of negative iterated */
    if(y1>y0) iy=1; else iy=-1;
    if(x1>x0) ix=1; else ix=-1;
    /* Calculate if f(x,y) needs to be bigger or smaller than 0 to move on */
    if(rico < 0.0) ri=-1; else ri=1;
    /* If the slope is [0,1) */
    if(abs(rico) < 1.0 && abs(rico) >= 0.0)
    {
        for(tx=x0; tx!=x1; tx+=ix)
        {
            PutPixel(s,tx,ty,colour);
            if(ri*getValue(tx, ty, x0, x1, y0, y1) > 0)
                ty+=iy;

        }
    }
    /* If the slope is [1,inf) */
    else
    {   
        for(ty=y0; ty!=y1; ty+=iy)
        {
            PutPixel(s,tx,ty,colour);
            if(ri*getValue(tx,ty, x0, x1, y0, y1) < 0)
                tx+=ix;
        }
    }
    return;
}

/* Function to calculate f(x,y) */
int getValue(int x, int y, int x0, int x1, int y0, int y1)
{
    int val = ((y0-y1)*x)+((x1-x0)*y)+(x0*y1)-(x1*y0);
    return val;
}
