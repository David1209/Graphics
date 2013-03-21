/* Computer Graphics and Game Technology, Assignment Box2D game
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

#include <cstdio>

#include <GL/gl.h>
#include <GL/glut.h>
#include <Box2D/Box2D.h>
#include <math.h>

#include "levels.h"

unsigned int reso_x = 800, reso_y = 600; // Window size in pixels
const float world_x = 8.f, world_y = 6.f; // Level (world) size in meters

int last_time;
int frame_count;

// Information about the levels loaded from files will be available in these.
unsigned int num_levels;
level_t *levels;

const b2Vec2 gravity(0, -9.8);
b2World m_world(gravity);
b2Body* ball;


/*
 * Load a given world, i.e. read the world from the `levels' data structure and
 * convert it into a Box2D world.
 */
void load_world(unsigned int level)
{
    if (level >= num_levels)
    {
        // Note that level is unsigned but we still use %d so -1 is shown as
        // such.
        printf("Warning: level %d does not exist.\n", level);
        return;
    }

    // Create a Box2D world and populate it with all bodies for this level
    // (including the ball).

    // 
    level = 1;

 

   
/*
 * Every vertex has a 2D position.

typedef struct {
    float x, y;
} point_t;

*
 * A polygon has a bunch of vertices.
 *
typedef struct {
    unsigned int num_verts;
    point_t *verts;
} poly_t;

*
 * Represents a level with start and end positions, and a bunch of polygons.
 *
typedef struct {
    unsigned int num_polygons;
    poly_t *polygons;
    point_t start, end;
} level_t; */

    unsigned int i, j;
    b2PolygonShape *shapes = new b2PolygonShape[levels[level].num_polygons];
    b2BodyDef *bodyDefs = new b2BodyDef[levels[level].num_polygons];
    b2FixtureDef *fixtureDefs = new b2FixtureDef[levels[level].num_polygons];
    b2Body* theBody;
    printf("bodydefs: %d\n", levels[level].num_polygons);
    for(i = 0; i < levels[level].num_polygons; i++)
    {
        unsigned int num = levels[level].polygons[i].num_verts;
        b2Vec2 *vertices = new b2Vec2[num];
        printf("num = %d\n", num);
        for(j = 0; j < num; j++)
        {
            printf("in j\n");
            vertices[num] = b2Vec2(levels[level].polygons[i].verts[j].x, levels[level].polygons[i].verts[j].y);
            printf("uit j\n");
        }
        shapes[i].Set(vertices, num);
        bodyDefs[i].type = b2_staticBody;
        bodyDefs[i].position.Set(0,0);
        bodyDefs[i].angle = 0;
        b2BodyDef *bodyDefPtr = &bodyDefs[i];
        fixtureDefs[i].shape = &shapes[i];
        fixtureDefs[i].density = 1;
        // the following line segfaults
        theBody = m_world.CreateBody(bodyDefPtr);
        theBody->CreateFixture(&fixtureDefs[i]);
    }

// ---------------------------------------

    b2BodyDef ballBody;
    b2CircleShape ballShape;
    b2FixtureDef ballFixture;

    ballBody.type = b2_dynamicBody;
    ballBody.position.Set(4, 6);
    ballBody.angle = 40;

    ballShape.m_p.Set(0, 0);
    ballShape.m_radius = 0.1;

    ballFixture.shape = &ballShape;
    ballFixture.density = 1;

    ball = m_world.CreateBody(&ballBody);
    ball->CreateFixture(&ballFixture);
    
    
}


/*
 * Called when we should redraw the scene (i.e. every frame).
 * It will show the current framerate in the window title.
 */
void draw(void)
{
    int time = glutGet(GLUT_ELAPSED_TIME);
    int frametime = time - last_time;
    int circle_triangles = 30;
    double ballx = ball->GetPosition().x;
    double bally = ball->GetPosition().y;
    double ballr = ball->GetFixtureList()[0].GetShape()->m_radius;
    double twoPi = 2.0 * 3.14159;
    frame_count++;

    // Clear the buffer
    glColor3f(0, 0, 0);
    glClear(GL_COLOR_BUFFER_BIT);



    //
    // Do any logic and drawing here.
    //
    m_world.Step(1/60.0, 1, 1);

    // Draw the ball source: http://en.wikibooks.org/wiki/OpenGL_Programming/Basics/2DObjects
    glColor3f(1, 1, 1);
    printf("%f %f\n", ballx, bally);

    glBegin(GL_TRIANGLE_FAN);

    glVertex2f(ballx, bally);
    for (int i = 0; i <= circle_triangles; i++) {
        glVertex2f(ballx + ballr * cos(i * twoPi / circle_triangles),
                   bally + ballr * sin(i * twoPi / circle_triangles));
    }

    glEnd();





    // Show rendered frame
    glutSwapBuffers();

    // Display fps in window title.
    if (frametime >= 1000)
    {
        char window_title[128];
        snprintf(window_title, 128,
                "Box2D: %f fps, level %d/%d",
                frame_count / (frametime / 1000.f), -1, num_levels);
        glutSetWindowTitle(window_title);
        last_time = time;
        frame_count = 0;
    }
}

/*
 * Called when window is resized. We inform OpenGL about this, and save this
 * for future reference.
 */
void resize_window(int width, int height)
{
    glViewport(0, 0, width, height);
    reso_x = width;
    reso_y = height;
}

/*
 * Called when the user presses a key.
 */
void key_pressed(unsigned char key, int x, int y)
{
    switch (key)
    {
        case 27: // Esc
        case 'q':
            exit(0);
            break;
        // Add any keys you want to use, either for debugging or gameplay.
        default:
            break;
    }
}

/*
 * Called when the user clicked (or released) a mouse buttons inside the window.
 */
void mouse_clicked(int button, int state, int x, int y)
{

}

/*
 * Called when the mouse is moved to a certain given position.
 */
void mouse_moved(int x, int y)
{

}


int main(int argc, char **argv)
{
    // Create an OpenGL context and a GLUT window.
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowSize(reso_x, reso_y);
    glutCreateWindow("Box2D");

    // Bind all GLUT events do callback function.
    glutDisplayFunc(&draw);
    glutIdleFunc(&draw);
    glutReshapeFunc(&resize_window);
    glutKeyboardFunc(&key_pressed);
    glutMouseFunc(&mouse_clicked);
    glutMotionFunc(&mouse_moved);
    glutPassiveMotionFunc(&mouse_moved);

    // Initialise the matrices so we have an orthogonal world with the same size
    // as the levels, and no other transformations.
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, world_x, 0, world_y, 0, 1);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // Read the levels into a bunch of structs.
    num_levels = load_levels(&levels);
    printf("Loaded %d levels.\n", num_levels);

    // Load the first level (i.e. create all Box2D stuff).
    load_world(0);

    last_time = glutGet(GLUT_ELAPSED_TIME);
    frame_count = 0;
    glutMainLoop();

    return 0;
}
