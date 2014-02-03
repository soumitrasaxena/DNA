#include <windows.h>  // for MS Windows
#include <GL/glut.h>  // GLUT, include glu.h and gl.h
#include <stdio.h>
#include <stdlib.h>
#include <math.h>   //to use sin and cos
//#include <math3d.h>
#include "vec3f.cpp"
#include "imageloader.cpp"

		

#define GL_PI 3.1415f

#ifndef GL_BGR
#define GL_BGR 0x80E0
#endif

using namespace std;

GLuint textureID;

GLfloat xRot = 0.0f , yRot = -0.0f , angle = 0.0f , zoom_out = -400.0f;
bool* keySpecialStates = new bool[256];

GLboolean pan =0 , rot = 1;

GLint modifier;

bool* keyNormalStates = new bool[256];

GLfloat xInitial=0 , yInitial=0 , xFinal=0 , yFinal=0 , x_trans=0.0f , y_trans=0.0f , light_z = 50.0f;


void keyOperations(void)
{
	if(keySpecialStates[GLUT_KEY_LEFT] == 1)
	{
		printf("left \n");
		yRot = yRot+1;
	}
	if(keySpecialStates[GLUT_KEY_RIGHT] ==1)
	{
		printf("right \n");
		yRot = yRot-1;
	}
	if(keySpecialStates[GLUT_KEY_UP] ==1)
	{
		printf("up \n");
		xRot = xRot-1;
	}
	if(keySpecialStates[GLUT_KEY_DOWN] ==1)
	{
		printf("down \n");
		xRot = xRot+1;
	}
	if(keyNormalStates['z'] == 1)
	{
		printf("z \n");
		zoom_out = zoom_out + 10;
	}

	if(keyNormalStates['x'] == 1)
	{
		printf("x \n");
		zoom_out = zoom_out - 10;
	}

	if(keyNormalStates['o'] == 1)
	{
		printf("o \n");
		light_z = light_z + 10;
	}

	if(keyNormalStates['l'] == 1)
	{
		printf("l \n");
		light_z = light_z - 10;
	}
}

void SetupRC(void)
{
	glClearColor(0.0f , 0.0f , 0.0f , 1.0f);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHT1);
	glEnable(GL_NORMALIZE);
	//glDisable(GL_LIGHTING);
	//glEnable(GL_CULL_FACE);
	glShadeModel(GL_SMOOTH);
	//glPolygonMode(GL_FRONT , GL_FILL);
	//glPolygonMode(GL_BACK , GL_LINE);
	
}

void computeNormals(float x1 , float z1 , float x2 , float z2)
{


}



void RenderScene( void )
{

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	
	glPushMatrix();	

	glTranslatef(x_trans, y_trans , zoom_out);	
	glRotatef(xRot , 1.0f , 0.0f , 0.0f);
	glRotatef(yRot , 0.0f , 1.0f , 0.0f);

	glColor3f(1.0f , 1.0f , 1.0f);
	
	glBegin(GL_LINES);

	glNormal3f(0.0f , 0.0f , 1.0f);

	glVertex2f(-1000.0f , 0.0f);
	glVertex2f(1000.0f , 0.0f );

	glVertex2f(0.0f , 1000.0f);
	glVertex2f(0.0f , -1000.0f );

	glNormal3f( 1.0f , 1.0f , 0.0f);
	
	glVertex3f(0.0f , 0.0f , -1000.0f);
	glVertex3f(0.0f , 0.0f , 1000.0f);

	glEnd();

	

	GLfloat light0_ambient[] = {1.0f, 1.0f , 1.0f , 1.0f};
	GLfloat light0_diffuse[] = {1.0f , 1.0f , 1.0f , 1.0};
	//GLfloat light0_specular[] = {0.43f , 0.3f , 0.4f , 1.0};

	GLfloat light0_position[] = { 0.0f , 0.0f , light_z , 1.0f};

	glLightfv(GL_LIGHT0 , GL_AMBIENT , light0_ambient);
	glLightfv(GL_LIGHT0 , GL_DIFFUSE , light0_diffuse);
	//glLightfv(GL_LIGHT0 , GL_SPECULAR , light0_specular);

	glLightfv(GL_LIGHT0 , GL_POSITION , light0_position);

	
	//glutSolidSphere(20 , 30 , 30);

	//This is where the DNA Starts.

	//glColor3f(1.0f , 0.0f , 0.0f);

	float x1 = 0 , z1 = 0 , x2 = 0 , z2= 0 , yOld1 = -200 , yNew1 = 0 , yOld2 = -200 , yNew2 = 0 ;
	int angle2;
	
	struct strand
	{
		float x ;
		float y;
		float z;
	};

		float rem1 , rem2 , rem3 , rem4;
		strand s1[100] , s2[100] , s3[100] , s4[100];
		int index1 = 0  , index2 =0 , index3 = 0 , index4 = 0;
		
	for (int angle = 0 ; angle<=(360*5-10) ; angle=angle+10)
	{
		angle2 = angle+180;

		GLfloat material_diffuse_front[] = { 1.0f, 0.0f , 0.0f , 1.0f};
		glMaterialfv(GL_FRONT , GL_DIFFUSE , material_diffuse_front);


		glBegin(GL_QUADS);
		
		x1 = 40*cos(angle*GL_PI/180);
		z1 = 40*sin(angle*GL_PI/180);
		
		x2 = 40*cos((angle+10)*GL_PI/180);
		z2 = 40*sin((angle+10)*GL_PI/180); 
		
		yNew1 = yOld1+3;

		glNormal3f(0.0f , 0.0f , 1.0f);

		glVertex3f(x1 , yOld1 , z1);
		glVertex3f(x1 , yOld1+10 , z1);
		glVertex3f(x2 , yNew1+10 , z2);
		glVertex3f(x2 , yNew1 , z2);

		rem1 = (angle-60)%360;
		rem3 = (angle-120)%360;
		

		if(rem1 == 0)
		{
			s1[index1].x = x1;
			s1[index1].y = yOld1;
			s1[index1].z = z1;
			index1 = index1+1;
		}

		if(rem3 == 0)
		{
			
			s3[index3].x = x1;
			s3[index3].y = yOld1;
			s3[index3].z = z1;
			index3 = index3+1;
		}		


		yOld1 = yNew1;

		glEnd();
				
		GLfloat material_diffuse_front2[] = { 0.0f, 1.0f , 0.0f , 1.0f};
		glMaterialfv(GL_FRONT , GL_DIFFUSE , material_diffuse_front2);

		glBegin(GL_QUADS);
		
		x1 = 40*cos(angle2*GL_PI/180);
		z1 = 40*sin(angle2*GL_PI/180);
		
		x2 = 40*cos((angle2+10)*GL_PI/180);
		z2 = 40*sin((angle2+10)*GL_PI/180); 
		
		yNew2 = yOld2+3;

		glNormal3f(0.0f , 0.0f , 1.0f);

		glVertex3f(x1 , yOld2 , z1);
		glVertex3f(x1 , yOld2+10 , z1);
		glVertex3f(x2 , yNew2+10 , z2);
		glVertex3f(x2 , yNew2 , z2);

		rem2 = (angle2-300)%360;
		rem4 = (angle2 -240)%360;


		if(rem2 == 0)
		{
			s2[index2].x = x1;
			s2[index2].y = yOld2;
			s2[index2].z = z1;
			index2 = index2+1;
		}		
		
		
		if(rem4 == 0)
		{
			
			s4[index4].x = x1;
			s4[index4].y = yOld2;
			s4[index4].z = z1;
			index4 = index4+1;
		}		
				
		yOld2 = yNew2;

		glEnd();
	}
	
	GLfloat material_diffuse_front3[] = { 0.0f, 0.0f , 1.0f , 1.0f};
	glMaterialfv(GL_FRONT , GL_DIFFUSE , material_diffuse_front3);
	
	glBegin(GL_QUADS);
		
	for(int i = 0 ; i<index1 ; i++)
	{
		glVertex3f(s1[i].x , s1[i].y , s1[i].z);
		glVertex3f(s1[i].x , s1[i].y+10 , s1[i].z);
		glVertex3f(s2[i].x , s2[i].y+10 , s2[i].z);
		glVertex3f(s2[i].x , s2[i].y , s2[i].z);
	}
	glEnd();

	GLfloat material_diffuse_front4[] = { 0.0f, 0.0f , 1.0f , 1.0f};
	glMaterialfv(GL_FRONT , GL_DIFFUSE , material_diffuse_front4);
	
	glBegin(GL_QUADS);
		
	for(int i = 0 ; i<index3 ; i++)
	{
		glVertex3f(s3[i].x , s3[i].y , s3[i].z);
		glVertex3f(s3[i].x , s3[i].y+10 , s3[i].z);
		glVertex3f(s4[i].x , s4[i].y+10 , s4[i].z);
		glVertex3f(s4[i].x , s4[i].y , s4[i].z);
	}
	glEnd();
	
	for(int i = 0 ; i< index1 ; i++)
	{
		printf("%f \t %f \t %f \t \n" , s1[i].x , s1[i].y , s1[i].z);
	}

	for(int i = 0 ; i< index2 ; i++)
	{
		printf("%f \t %f \t %f \t \n" , s2[i].x , s2[i].y , s2[i].z);
	}

	
	/*
	
	y = -200;
		
	GLfloat material_diffuse_front_2[] = { 0.0f, 1.0f , 0.0f , 1.0f};
	glMaterialfv(GL_FRONT , GL_DIFFUSE , material_diffuse_front_2);

	glBegin(GL_QUAD_STRIP);
	glNormal3f(0.0f , 0.0f , 1.0f);

	for(int angle = 180 ; angle<=(360*5-10) ; angle=angle+10)
	{
		x1 = 40*cos(angle*GL_PI/180);
		z1 = 40*sin(angle*GL_PI/180);

	
		glVertex3f(x1 , y , z1);
		glVertex3f(x1 , y+10 , z1);
		
		y = y+3;

	}
	glEnd();
	*/
	printf("Render scene working \n");
	
	glPopMatrix();
	glutSwapBuffers();


}

void ChangeSize(GLsizei w , GLsizei h)
{
	GLfloat aspectRatio;

	if(h==0)
	{
		h=1;
	}

	glViewport(0,0,w,h);

	//Resetting coordinate system
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	aspectRatio = (GLfloat) w / (GLfloat) h ;

	gluPerspective(60.0f , aspectRatio , 1.0f , 1800.0f );
	
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void processSpecialKeys( int key , int x , int y)
{
	keySpecialStates[key] = true;
	printf("Special Keys DOWN registered \n");	
	printf("%d \t %d \n",x,y);
	keyOperations();
	glutPostRedisplay();
}

void processSpecialKeysUp( int key , int x , int y)
{
	keySpecialStates[key] = false;
	printf("Special Keys UP registered \n");	
	printf("%d \t %d \n",x,y);
	//glutPostRedisplay();
}

void processKeyboardKeys( unsigned char key , int x , int y)
{
	keyNormalStates[key] = true;
	printf("Normal Keys DOWN registered \n");	
	printf(" %f \t %f \t %f \n" , xRot , yRot , zoom_out);
	keyOperations();
	glutPostRedisplay();
}

void processKeyboardKeysUP( unsigned char key , int x , int y)
{
	keyNormalStates[key] = false;
	printf("Normal Keys UP registered \n");	
	printf(" %f \t %f \t %f \n" , xRot , yRot , zoom_out);
	keyOperations();
	glutPostRedisplay();
}

void processMouse(int button , int state , int x , int y)
{
	if ( state == GLUT_DOWN)
	{
		printf("mouse DOWN captured \n");
		xInitial = x;
		yInitial = y;
	}

	if(keyNormalStates['c'] == 1 && state == GLUT_DOWN)
	{
		pan = 1;
		rot = 0;
	}
	
	if( state == GLUT_UP )
	{
		pan = 0;
		rot = 1;
	}
	
}

void processActiveMotion( int x , int y)
{
	xFinal=x;
	yFinal=y;

	if(rot == 1)
	{
	xRot = xRot + (yFinal-yInitial)/50;
	yRot = yRot + (xFinal-xInitial)/50;
	}

	printf(" xRot = %f and yRot = %f \n " , xRot , yRot);

	if(pan == 1 )
	{
		x_trans = x_trans+(xFinal - xInitial)/50;
		y_trans = y_trans-(yFinal - yInitial)/50;

	}


	glutPostRedisplay();
}

int main( int argc , char* argv[])
{
	glutInit(&argc , argv);
	glutInitDisplayMode( GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	
	glutCreateWindow("DNA");
	
	glutKeyboardFunc(processKeyboardKeys);
	glutKeyboardUpFunc(processKeyboardKeysUP);
	
	glutSpecialFunc(processSpecialKeys);
	glutSpecialUpFunc(processSpecialKeysUp);
	
	glutMouseFunc(processMouse);
	glutMotionFunc(processActiveMotion);

	glutDisplayFunc(RenderScene);
	//glutIdleFunc(RenderScene);
	glutReshapeFunc(ChangeSize);
	//glutTimerFunc(33 , Timer , 1 );
	

	SetupRC();
	
	glutMainLoop();
	return 0;

}