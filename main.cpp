#include <GL/glut.h>
#include <cmath>
#include <vector>
#include <cstdlib>

#define PI 3.1415926535f

/* ================== CAMERA ================== */
float camDist = 15.0f;
float rotX = 20.0f, rotY = -30.0f;
int lastX, lastY;
bool rotating = false;

/* ================== ANGLES ================== */
float aMercury=0,aVenus=0,aEarth=0,aMoon=0,aMars=0;
float aJupiter=0,aSaturn=0,aUranus=0,aNeptune=0;

/* ================== MATERIALS ================== */
GLfloat sun[]={1,0.7f,0.2f,1};
GLfloat mercury[]={0.6f,0.6f,0.6f,1};
GLfloat venus[]={0.9f,0.6f,0.2f,1};
GLfloat earth[]={0.1f,0.3f,0.9f,1};
GLfloat moon[]={0.8f,0.8f,0.8f,1};
GLfloat mars[]={0.8f,0.3f,0.1f,1};
GLfloat jupiter[]={0.8f,0.6f,0.4f,1};
GLfloat saturn[]={0.9f,0.8f,0.5f,1};
GLfloat uranus[]={0.5f,0.8f,0.9f,1};
GLfloat neptune[]={0.2f,0.3f,0.9f,1};

/* ================== ASTEROID BELT ================== */
struct Asteroid {
    float radius;
    float angle;
    float z;
};
std::vector<Asteroid> belt;

/* ================== LIGHTING ================== */
void initLighting()
{
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    GLfloat pos[]={0,0,0,1};
    GLfloat amb[]={0.15f,0.15f,0.15f,1};
    GLfloat dif[]={1,1,1,1};

    glLightfv(GL_LIGHT0,GL_POSITION,pos);
    glLightfv(GL_LIGHT0,GL_AMBIENT,amb);
    glLightfv(GL_LIGHT0,GL_DIFFUSE,dif);

    glEnable(GL_DEPTH_TEST);
    glShadeModel(GL_SMOOTH);
}

/* ================== ORBIT ================== */
void orbit(float r)
{
    glDisable(GL_LIGHTING);
    glColor3f(0.45f,0.45f,0.45f);
    glBegin(GL_LINE_LOOP);
    for(int i=0;i<360;i++)
        glVertex3f(cos(i*PI/180.0f)*r, 0, sin(i*PI/180.0f)*r);
    glEnd();
    glEnable(GL_LIGHTING);
}

/* ================== SATURN RING ================== */
void ring(float inner, float outer)
{
    glDisable(GL_LIGHTING);
    glColor3f(0.85f,0.8f,0.65f);
    glBegin(GL_TRIANGLE_STRIP);
    for(int i=0;i<=360;i++)
    {
        float a=i*PI/180.0f;
        glVertex3f(cos(a)*inner,0,sin(a)*inner);
        glVertex3f(cos(a)*outer,0,sin(a)*outer);
    }
    glEnd();
    glEnable(GL_LIGHTING);
}

/* ================== DRAW ================== */
void draw()
{
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    gluLookAt(0,0,camDist, 0,0,0, 0,1,0);
    glRotatef(rotX,1,0,0);
    glRotatef(rotY,0,1,0);

    /* ORBITS */
    orbit(1.2f);   // Mercury
    orbit(1.6f);   // Venus
    orbit(2.1f);   // Earth
    orbit(2.6f);   // Mars
    orbit(3.3f);   // Asteroid belt
    orbit(4.1f);   // Jupiter
    orbit(5.1f);   // Saturn
    orbit(6.0f);   // Uranus
    orbit(6.8f);   // Neptune

    /* -------- SUN -------- */
    glPushMatrix();
    GLfloat emit[]={1,0.6f,0.2f,1};
    glMaterialfv(GL_FRONT,GL_EMISSION,emit);
    glMaterialfv(GL_FRONT,GL_AMBIENT_AND_DIFFUSE,sun);
    glutSolidSphere(0.6,60,60);
    GLfloat noE[]={0,0,0,1};
    glMaterialfv(GL_FRONT,GL_EMISSION,noE);
    glPopMatrix();

    /* MERCURY */
    glPushMatrix();
    glRotatef(aMercury,0,1,0);
    glTranslatef(1.2f,0,0);
    glMaterialfv(GL_FRONT,GL_AMBIENT_AND_DIFFUSE,mercury);
    glutSolidSphere(0.05,30,30);
    glPopMatrix();

    /* VENUS */
    glPushMatrix();
    glRotatef(aVenus,0,1,0);
    glTranslatef(1.6f,0,0);
    glMaterialfv(GL_FRONT,GL_AMBIENT_AND_DIFFUSE,venus);
    glutSolidSphere(0.09,30,30);
    glPopMatrix();

    /* EARTH + MOON */
    glPushMatrix();
    glRotatef(aEarth,0,1,0);
    glTranslatef(2.1f,0,0);
    glMaterialfv(GL_FRONT,GL_AMBIENT_AND_DIFFUSE,earth);
    glutSolidSphere(0.1,40,40);

    glRotatef(aMoon,0,1,0);
    glTranslatef(0.25f,0,0);
    glMaterialfv(GL_FRONT,GL_AMBIENT_AND_DIFFUSE,moon);
    glutSolidSphere(0.03,20,20);
    glPopMatrix();

    /* MARS */
    glPushMatrix();
    glRotatef(aMars,0,1,0);
    glTranslatef(2.6f,0,0);
    glMaterialfv(GL_FRONT,GL_AMBIENT_AND_DIFFUSE,mars);
    glutSolidSphere(0.07,30,30);
    glPopMatrix();

    /* ASTEROID BELT */
    glDisable(GL_LIGHTING);
    glPointSize(2);
    glBegin(GL_POINTS);
    for(const auto& a : belt)
        glVertex3f(cos(a.angle)*a.radius, a.z, sin(a.angle)*a.radius);
    glEnd();
    glEnable(GL_LIGHTING);

    /* JUPITER */
    glPushMatrix();
    glRotatef(aJupiter,0,1,0);
    glTranslatef(4.1f,0,0);
    glMaterialfv(GL_FRONT,GL_AMBIENT_AND_DIFFUSE,jupiter);
    glutSolidSphere(0.28,50,50);
    glPopMatrix();

    /* SATURN + RING */
glPushMatrix();
glRotatef(aSaturn,0,1,0);
glTranslatef(5.1f,0,0);

glMaterialfv(GL_FRONT,GL_AMBIENT_AND_DIFFUSE,saturn);
glutSolidSphere(0.24,40,40);

/* EQUATORIAL RINGS */
glRotatef(27, 0, 0, 1);   // axial tilt (NOT poles)
ring(0.35f,0.5f);

glPopMatrix();


    /* URANUS (NO RING) */
    glPushMatrix();
    glRotatef(aUranus,0,1,0);
    glTranslatef(6.0f,0,0);
    glMaterialfv(GL_FRONT,GL_AMBIENT_AND_DIFFUSE,uranus);
    glutSolidSphere(0.16,30,30);
    glPopMatrix();

    /* NEPTUNE */
    glPushMatrix();
    glRotatef(aNeptune,0,1,0);
    glTranslatef(6.8f,0,0);
    glMaterialfv(GL_FRONT,GL_AMBIENT_AND_DIFFUSE,neptune);
    glutSolidSphere(0.15,30,30);
    glPopMatrix();

    glutSwapBuffers();
}

/* ================== UPDATE ================== */
void update(int)
{
    aMercury+=2.2f;
    aVenus+=1.6f;
    aEarth+=1.0f;
    aMoon+=4.0f;
    aMars+=0.8f;
    aJupiter+=0.4f;
    aSaturn+=0.3f;
    aUranus+=0.2f;
    aNeptune+=0.15f;

    glutPostRedisplay();
    glutTimerFunc(20,update,0);
}

/* ================== MOUSE ================== */
void mouse(int btn,int state,int x,int y)
{
    if(btn==GLUT_LEFT_BUTTON)
    {
        rotating = (state==GLUT_DOWN);
        lastX=x; lastY=y;
    }
    if(btn==3) camDist-=0.5f;
    if(btn==4) camDist+=0.5f;
}

void motion(int x,int y)
{
    if(rotating)
    {
        rotY += (x-lastX);
        rotX += (y-lastY);
        lastX=x; lastY=y;
    }
}

/* ================== RESHAPE ================== */
void reshape(int w,int h)
{
    if(h==0) h=1;
    glViewport(0,0,w,h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60,(float)w/h,1,200);
    glMatrixMode(GL_MODELVIEW);
}

/* ================== MAIN ================== */
int main(int argc,char** argv)
{
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGB|GLUT_DEPTH);
    glutInitWindowSize(900,900);
    glutCreateWindow("Solar System - Clean Orbits");

    initLighting();
    glClearColor(0,0,0,1);

    /* ASTEROID BELT INIT (CLEAR GAP BEFORE JUPITER) */
    for(int i=0;i<500;i++)
    {
        float radius = 3.1f + ((float)rand()/RAND_MAX)*0.4f;
        float angle  = ((float)rand()/RAND_MAX)*2.0f*PI;
        float z      = ((float)(rand()%100-50))/250.0f;
        belt.push_back({radius,angle,z});
    }

    glutDisplayFunc(draw);
    glutReshapeFunc(reshape);
    glutMouseFunc(mouse);
    glutMotionFunc(motion);
    glutTimerFunc(20,update,0);

    glutMainLoop();
    return 0;
}
