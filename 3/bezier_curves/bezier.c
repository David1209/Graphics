/* Computer Graphics, Assignment, Bezier curves
 * Filename ........ bezier.c
 * Description ..... Bezier curves
 * Date ............ 22.07.2009
 * Created by ...... Paul Melis
 *
 * Student name ....
 * Student email ...
 * Collegekaart ....
 * Date ............
 * Comments ........
 *
 *
 * (always fill in these fields before submitting!!)
 */

#include <math.h>
#include "bezier.h"
#include <stdio.h>
#include <stdlib.h>

/* Calculate the factorial of n
 */
int factorial(int n) {
    int answer = 1;
    for (int i = 2; i <= n; i++) {
        answer *= i;
    }
    return answer;
}

/* Calculate n over k
 */
float binomial(int n, int k) {
    return factorial(n) / (float) (factorial(k) * factorial(n - k));
}

/* Calculate the ith Bernstein polynomial of degree n
 */
float bernstein(int n, int i, float u) {
    return binomial(n, i) * pow(u, i) * pow(1 - u, n - i);
}

/* Given a Bezier curve defined by the 'num_points' control points
 * in 'p' compute the position of the point on the curve for parameter
 * value 'u'.
 *
 * Return the x and y values of the point by setting *x and *y,
 * respectively.
 */

void evaluate_bezier_curve(float *x, float *y, control_point p[], int num_points, float u)
{
    *x = 0.0;
    *y = 0.0;

    for (int i = 0; i < num_points; i++) {
        float bern = bernstein(num_points - 1, i, u);
        *x += bern * p[i].x;
        *y += bern * p[i].y;
    }

}

/* Draw a Bezier curve defined by the control points in p[], which
 * will contain 'num_points' points.
 *
 * Draw the line segments you compute directly on the screen
 * as a single GL_LINE_STRIP. This is as simple as using
 *
 *      glBegin(GL_LINE_STRIP);
 *      glVertex2f(..., ...);
 *      ...
 *      glEnd();
 *
 * DO NOT SET ANY COLOR!
 *
 * The 'num_segments' parameter determines the "discretization" of the Bezier
 * curve and is the number of straight line segments that should be used
 * to approximate the curve.
 *
 * Call evaluate_bezier_curve() to compute the necessary points on
 * the curve.
 */

void draw_bezier_curve(int num_segments, control_point p[], int num_points)
{
    float x, y;

    glBegin(GL_LINE_STRIP);

    // start line
    glVertex2f(p[0].x, p[0].y);

    // calculate and draw points in the middle
    for (int i = 1; i < num_segments; i++) {
        evaluate_bezier_curve(&x, &y, p, num_points, i / (float) num_segments);
        glVertex2f(x, y);
    }

    // end line
    glVertex2f(p[num_points - 1].x, p[num_points - 1].y);
    glEnd();

}

/* Find the intersection of a cubic Bezier curve with the line X=x.
   Return 1 if an intersection was found and place the corresponding y
   value in *y.
   Return 0 if no intersection exists.
*/

int intersect_cubic_bezier_curve(float *y, control_point p[], float x)
{
    return 0;
}

