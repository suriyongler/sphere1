/* sphere1.c    */

/* E. Angel, Interactive Computer Graphics */
/* A Top-Down Approach with OpenGL, Third Edition */
/* Addison-Wesley Longman, 2003 */

/* Recursive subdivision of cube (Chapter 6). Three display
modes: wire frame, constant, and interpolative shading */

/*Program also illustrates defining materials and light sources
in myiit() */

/* mode 0 = wire frame, mode 1 = constant shading,
mode 3 = interpolative shading */

#include <stdlib.h>
#include <GL/glut.h>


typedef float point[3];

/* initial tetrahedron */

point v[]={
	{0.0, 0.0, 1.0}, 
	{0.0, 0.942809, -0.33333},
    {-0.816497, -0.471405, -0.333333}, 
	{0.816497, -0.471405, -0.333333}
};

static GLfloat theta[] = {0.0,0.0,0.0};

int n;

void triangle( point a, point b, point c){
	//display one triangle using a line loop for wire frame,

 	glBegin(GL_LINE_LOOP);
		glVertex3fv(a);
		glVertex3fv(b);
		glVertex3fv(c);
	glEnd();
  }

void normal(point p) {

	/* normalize a vector */

    double sqrt();
    float d =0.0;
    int i;

    for(i=0; i<3; i++)			// d = p0*p0 + p1*p1 + p2*p2
		d+=p[i]*p[i];
    d=sqrt(d);					//	get vertices manitude value
    if(d>0.0) 
		for(i=0; i<3; i++) 
			p[i]/=d;
}

void tetrahedron(){

	/* Apply triangle subdivision to faces of tetrahedron */

    triangle(v[0], v[1], v[2]);
    triangle(v[3], v[2], v[1]);
    triangle(v[0], v[3], v[1]);
    triangle(v[0], v[2], v[3]);
}

void display(void){

/* Displays all three modes, side by side */

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
    tetrahedron();
    glFlush();
}


void myReshape(int w, int h){
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    if (w <= h)
        glOrtho(-1.0, 1.0, -1.0 * (GLfloat) h / (GLfloat) w,
            1.0 * (GLfloat) h / (GLfloat) w, -10.0, 10.0);
    else
        glOrtho(-1.0 * (GLfloat) w / (GLfloat) h,
            1.0 * (GLfloat) w / (GLfloat) h, -1.0, 1.0, -10.0, 10.0);
    glMatrixMode(GL_MODELVIEW);
    display();
}

void myinit(){
	// place program here
    glClearColor (1.0, 1.0, 1.0, 1.0);
    glColor3f (0.0, 0.0, 0.0);
}

void main(int argc, char **argv){
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(500, 500);
    glutCreateWindow("sphere tetrahedron");
    myinit();
    glutReshapeFunc(myReshape);
    glutDisplayFunc(display);
    glutMainLoop();
}
