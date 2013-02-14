/* Computer Graphics, Assignment, Translations, Rotations and Scaling
 *
 * Filename ........ transformations.c
 * Description ..... Contains the re-programmed translation, rotation and scaling functions
 * Student name .... David van Erkelens, Jelte Fennema
 * Student email ... info@davidvanerkelens.nl, me@jeltef.nl
 * Collegekaart .... 10264019
 * Date ............ 14/02/2013
 * Comments ........ Enjoy!
 *
 * Answers to the questions:
 * A) X, then Y, then Z
 * B) At the teapot rotated at 90 degrees, rotating around the X and Z axis
 *    has the same effect. This can be explained by a so called gimbal lock:
 *    << further explaination here >>
 *
 * (always fill in these fields before submitting!!)
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <GL/gl.h>
#include "transformations.h"

/* ANSI C/ISO C89 does not specify this constant (?) */
#ifndef M_PI
#define M_PI           3.14159265358979323846  /* pi */
#endif

// My own scale translation matix thingy
void myScalef(GLfloat x, GLfloat y, GLfloat z)
{
    GLfloat M[16] =
    {
        x, 0.0, 0.0, 0.0,
        0.0, y, 0.0, 0.0,
        0.0, 0.0, z, 0.0,
        0.0, 0.0, 0.0, 1.0
    };

    glMultMatrixf(M);
}

// My own translation matrix function thingy
void myTranslatef(GLfloat x, GLfloat y, GLfloat z)
{
    GLfloat M[16] =
    {
        1.0, 0.0, 0.0, 0.0,
        0.0, 1.0, 0.0, 0.0,
        0.0, 0.0, 1.0, 0.0,
        x, y, z, 1.0
    };

    glMultMatrixf(M);
}

// Calculate the crossproduct of a and b, returing it in out
void crossProduct(GLfloat a[3], GLfloat b[3], GLfloat *out)
{
        out[0] = a[1]*b[2]-a[2]*b[1];
        out[1] = a[2]*b[0]-a[0]*b[2];
        out[2] = a[0]*b[1]-a[1]*b[0];
}

// Calculate the dotproduct of two vectors, returning a float
GLfloat dotProduct(GLfloat a[3], GLfloat b[3])
{
    return a[0]*b[0]+a[1]*b[1]+a[2]*b[2];
}

// Divide each element of the vector by the total length, thus normalizing it
void normalize(GLfloat *a)
{
    int i = 0;
    GLfloat len = sqrt(dotProduct(a, a));
    for(; i < 3; i++)
    {
        a[i] /= len;
    }
}

void myRotatef(GLfloat angle, GLfloat x, GLfloat y, GLfloat z)
{
    GLfloat u[3], v[3], w[3], t[3], rad;

    // 1. Create the orthonormal basis
    // Store the incoming rotation axis in w and normalize w
    w[0] = x;
    w[1] = y;
    w[2] = z;
    normalize(w);

    // Compute the value of t, based on w
    t[0] = x + 1;
    t[1] = y;
    t[2] = z;

    // Compute u = t x w
    crossProduct(t, w, u);

    // Normalize u
    normalize(u);

    // Compute v = w x u
    crossProduct(w, u, v);

    // 2. Set up the three matrices making up the rotation
    // Specify matrix A (uwv -> xyz)
    GLfloat A[16] =
    {
        u[0], u[1], u[2], 0.0,
        v[0], v[1], v[2], 0.0,
        w[0], w[1], w[2], 0.0,
        0.0,  0.0,  0.0,  1.0
    };

    // Convert 'angle' to radians
    rad = angle * (M_PI/180);

    // Specify matrix B (the rotation matix)
    GLfloat B[16] =
    {
        cos(rad), sin(rad),   0.0, 0.0,
        -sin(rad), cos(rad),  0.0, 0.0,
        0.0,       0.0,       1.0, 0.0,
        0.0,       0.0,       0.0, 1.0
    };

    // Specify matrix C (xyz -> uvw)
    GLfloat C[16] =
    {
        u[0], v[0], w[0], 0.0,
        u[1], v[1], w[1], 0.0,
        u[2], v[2], w[2], 0.0,
        0.0,  0.0,  0.0,  1.0
    };

    // 3. Apply the matrices to get the combined rotation
    glMultMatrixf(A);
    glMultMatrixf(B);
    glMultMatrixf(C);
}

