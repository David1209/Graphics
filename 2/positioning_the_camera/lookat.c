/* Computer Graphics, Assignment 4, Positioning the camera
 *
 * Filename ........ lookat.c
 * Description ..... Contains the re-programmed lookAt function
 * Created by ...... Jurgen Sturm
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
#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <math.h>


/* ANSI C/ISO C89 does not specify this constant (?) */
#ifndef M_PI
#define M_PI           3.14159265358979323846  /* pi */
#endif

void normalize(GLdouble *x, GLdouble *y, GLdouble *z) {
    GLdouble length = sqrt(*x**x + *y**y + *z**z);
    *x /= length;
    *y /= length;
    *z /= length;
}

void cross_product(GLdouble *x, GLdouble *y, GLdouble *z,
                   GLdouble ax, GLdouble ay, GLdouble az,
                   GLdouble bx, GLdouble by, GLdouble bz) {
    *x = ay*bz - az*by;
    *y = az*bx - ax*bz;
    *z = ax*by - ay*bx;
}


void myLookAt(GLdouble eyeX, GLdouble eyeY, GLdouble eyeZ,
              GLdouble centerX, GLdouble centerY, GLdouble centerZ,
              GLdouble upX, GLdouble upY, GLdouble upZ) {
    GLdouble cxx, cxy, cxz, cyx, cyy, cyz, czx, czy, czz;

    czx = centerX - eyeX;
    czy = centerY - eyeY;
    czz = centerZ - eyeZ;

    normalize(&czx, &czy, &czz);

    cross_product(&cxx, &cxy, &cxz,
                  czx, czy, czz,
                  upX, upY, upZ);
    normalize(&cxx, &cxy, &cxz);

    cross_product(&cyx, &cyy, &cyz,
                  cxx, cxy, cxz,
                  czx, czy, czz);

    GLdouble R[16] = {
        cxx, cyx, -czx, 0.0,
        cxy, cyy, -czy, 0.0,
        cxz, cyz, -czz, 0.0,
        0.0, 0.0, 0.0, 1.0

    };

    glMultMatrixd(R);

    glTranslated(-eyeX, -eyeY, -eyeZ);

}

