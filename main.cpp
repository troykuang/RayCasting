#ifdef __APPLE__
#  include <OpenGL/gl.h>
#  include <OpenGL/glu.h>
#  include <GLUT/glut.h>
#else
#  include <GL/gl.h>
#  include <GL/glu.h>
#  include <GL/freeglut.h>
#endif
#include <stdio.h>
#include <stdlib.h>
#include "SceneObject.h"
#include <list>

#define WINDOW_SIZE_WIDTH 700
#define WINDOW_SIZE_HEIGHT 700
#define groundSize 100



int mouseX = 0, mouseY = 0; //global vars to save mouse x/y coord
int SceneAngleY = 0;
int SceneAngleZ = 0;

//Globals
//float camPos[] = {39,34,33};	//where the camera is
float camPos[] = {23,18,33};

int materialCurrent =2;
int lightState = 1;	//for turning on and off the lights (2 lights)

std::list<SceneObject> shapes;
std::list<SceneObject>::iterator it;

float m_ambS[] = {0.0,0.0,0.0,1};
float m_diffS[] = {0.01,0.01,0.01,1};
float m_specS[] = {0.5,0.5,0.5,1.0};
float shinyS = 0.25;

//nature white light
float amb0[4]  = {0.1, 1, 0.4, 1}; 
float diff0[4] = {1, 0.3, 0, 1};
float spec0[4] = {0, 0, 0.6, 1}; 

float light_pos0[] = {10, 185, -140,1};
float light_pos1[] = {20, 195, -130, 1};

//material 0
//turquoise
float m_amb[] = {0.1, 0.18725, 0.1745, 1}; 
float m_diff[] = {0.396, 0.74151, 0.69102, 1}; 
float m_spec[] = {0.297254, 0.30829, 0.306678, 1}; 
float shiny = 0.1; 

//material 1
//cyan rubber
float m_amb1[] = {0.0, 0.05, 0.05, 1}; 
float m_diff1[] = {0.4, 0.5, 0.5, 1}; 
float m_spec1[] = {0.04, 0.7, 0.7, 1}; 
float shiny1 = 0.078125; 

//material 2
//gold
float m_amb2[] = {0.24725, 0.1995, 0.0745, 1}; 
float m_diff2[] = {0.75164, 0.60648, 0.22648, 1}; 
float m_spec2[] = {0.628281, 0.555802, 0.366065, 1}; 
float shiny2 = 0.4; 

//material 3
//jade
float m_amb3[] = {0.135, 0.2225, 0.1575, 1}; 
float m_diff3[] = {0.54, 0.89, 0.63, 1}; 
float m_spec3[] = {0.316228, 0.316228, 0.316228, 1}; 
float shiny3 = 0.1; 

//material 4
//brass
float m_amb4[] = {0.329412, 0.223529, 0.027451, 1}; 
float m_diff4[] = {0.780392, 0.568627, 0.113725, 1}; 
float m_spec4[] = {0.992157, 0.941176, 0.807843, 1}; 
float shiny4 = 0.21794872; 



void drawScene(){	//for drawing with smooth
	glShadeModel(GL_SMOOTH);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	// glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, m_amb); 
	// glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, m_diff); 
	// glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, m_spec); 
	// glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shiny);

	// // RIGHT
	// glColor3f(1,0,0);
	// glBegin(GL_POLYGON);
	// 	glVertex3f(0,0,0);
	// 	glVertex3f(20,0,0);
	// 	glVertex3f(20,20,0);
	// 	//glNormal3fv(norm);
	// 	glVertex3f(0,20,0);
	// glEnd();

	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, m_amb1); 
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, m_diff1); 
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, m_spec1); 
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shiny1);
	//FLOOR
	glColor3f(0,1,0);
	glBegin(GL_POLYGON);		
		glVertex3f(-groundSize/2,0,-groundSize/2);
		glVertex3f(-groundSize/2,0,groundSize/2);
		glVertex3f(groundSize/2,0,groundSize/2);

		float norm[3]={0,1,0};
		glNormal3fv(norm);
		glVertex3f(groundSize/2,0,-groundSize/2);
	glEnd();

	// glEnd();
	// glColor3f(0,0,1);
	// glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, m_ambS); 
	// glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, m_diffS); 
	// glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, m_specS); 
	// glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shinyS);
	// glBegin(GL_POLYGON);
	// 	glVertex3f(0,0,0);
	// 	glVertex3f(0,20,0);
	// 	glVertex3f(0,20,20);
	// 	//glNormal3fv(norm);
	// 	glVertex3f(0,0,20);
	// glEnd();

}



void drawObj(SceneObject s){
	s.updateBounds();
	glPushMatrix();

	cout<<"obj material: "<<s.materialState<<endl;
	

    switch(s.materialState){
		case 0:
			//cout<<"here"<<endl;
			glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, m_amb); 
			glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, m_diff); 
			glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, m_spec); 
			glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shiny);
			break;
		case 1:
			glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, m_amb1); 
			glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, m_diff1); 
			glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, m_spec1); 
			glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shiny1);
			break;
		case 2:
			//cout<<"here2"<<endl;
			glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, m_amb2); 
			glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, m_diff2); 
			glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, m_spec2); 
			glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shiny2);
			break;
		case 3:
			glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, m_amb3); 
			glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, m_diff3); 
			glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, m_spec3); 
			glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shiny3);
			break;
		case 4:
			glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, m_amb4); 
			glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, m_diff4); 
			glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, m_spec4); 
			glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shiny4);
			break;
	}



	glTranslatef(s.position[0],s.position[1],s.position[2]);
	glRotatef(s.orientation[0],1,0,0);
	glRotatef(s.orientation[1],0,1,0);
	glRotatef(s.orientation[2],0,0,1);
	glScalef(s.scale[0], s.scale[1], s.scale[2]);
	
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	// glDisable(GL_LIGHT0);
	// glDisable(GL_LIGHT1);
	//glColor3f(0.45,0.366,0.3434);
    switch(s.getType()){
    	case 1:
    		glutSolidCube(1);
    		break;
    	case 2:	//sphere
    		glutSolidSphere(0.5,100,100);
    		break;
    	case 3: 	//cone
    		glutSolidCone(0.5,1,100,100);
    		break;
    	case 4:	//teapot
    		glutSolidTeapot(1);
    		break;
    	case 5:
    		glutSolidTorus(0.15,0.3,100,100);
    		break; 	//torus
    }

 //    glEnable(GL_LIGHT0);
	// glEnable(GL_LIGHT1);
     glPopMatrix();

     printf("%d\n",s.selected);

     if(s.selected){
    	/*cout<<"HERE"<<endl;*/

    	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    	glColor3f(1.0f, 1.0f, 1.0f); 
    	
    	glDisable(GL_LIGHT0);
    	glDisable(GL_LIGHT1);
     	for(int i=0; i< 6; i++){ //go through the faces
    			glBegin(GL_TRIANGLE_FAN);
    			
    			// cout<<s.boundingVertices[s.boundingFaces[i][0]][0]<<" ";
    			// cout<<s.boundingVertices[s.boundingFaces[i][0]][1]<<" ";
    			// cout<<s.boundingVertices[s.boundingFaces[i][0]][2]<<endl;

    			// cout<<s.boundingVertices[s.boundingFaces[i][1]][0]<<" ";
    			// cout<<s.boundingVertices[s.boundingFaces[i][1]][1]<<" ";
    			// cout<<s.boundingVertices[s.boundingFaces[i][1]][2]<<endl;


    			// cout<<s.boundingVertices[s.boundingFaces[i][2]][0]<<" ";
    			// cout<<s.boundingVertices[s.boundingFaces[i][2]][1]<<" ";
    			// cout<<s.boundingVertices[s.boundingFaces[i][2]][2]<<endl;


    			// cout<<s.boundingVertices[s.boundingFaces[i][3]][0]<<" ";
    			// cout<<s.boundingVertices[s.boundingFaces[i][3]][1]<<" ";
    			// cout<<s.boundingVertices[s.boundingFaces[i][3]][2]<<endl;

    			glVertex3f(s.boundingVertices[s.boundingFaces[i][0]][0],s.boundingVertices[s.boundingFaces[i][0]][1],s.boundingVertices[s.boundingFaces[i][0]][2]);
    			glVertex3f(s.boundingVertices[s.boundingFaces[i][1]][0],s.boundingVertices[s.boundingFaces[i][1]][1],s.boundingVertices[s.boundingFaces[i][1]][2]);
    			glVertex3f(s.boundingVertices[s.boundingFaces[i][2]][0],s.boundingVertices[s.boundingFaces[i][2]][1],s.boundingVertices[s.boundingFaces[i][2]][2]);
    			glVertex3f(s.boundingVertices[s.boundingFaces[i][3]][0],s.boundingVertices[s.boundingFaces[i][3]][1],s.boundingVertices[s.boundingFaces[i][3]][2]);
    			glEnd();
    	}
    	glEnable(GL_LIGHT0);
    	glEnable(GL_LIGHT1);
    	

    }
}

void drawObjects(){
	//go through the list and then use the draw obj function
	for (std::list<SceneObject>::iterator it=shapes.begin(); it != shapes.end(); ++it){
		//printf("type:%i\n",it->getType());
		drawObj(*it);

	}

}
void special(int key, int x, int y)
{
	/* arrow key presses move the camera */
	int mod = glutGetModifiers();

	switch(key)
	{
		case GLUT_KEY_LEFT:
		if (mod == GLUT_ACTIVE_SHIFT){
			for (std::list<SceneObject>::iterator it=shapes.begin(); it != shapes.end(); ++it){
				if (it->selected){
					it->position[0] -= 1;
				}
			}

		}
		else{ 
			camPos[0] -= 1;
		}
			break;

		case GLUT_KEY_RIGHT:
		if (mod == GLUT_ACTIVE_SHIFT){
			for (std::list<SceneObject>::iterator it=shapes.begin(); it != shapes.end(); ++it){
				if (it->selected){
					it->position[0] += 1;
				}
			}
		}
		else{ 
			camPos[0] += 1;
		}
			break;

		case GLUT_KEY_UP:
		if (mod == GLUT_ACTIVE_SHIFT){
			for (std::list<SceneObject>::iterator it=shapes.begin(); it != shapes.end(); ++it){
				if (it->selected){
					it->position[2] -= 1;
				}
			}
		}
		else{ 
			camPos[1] += 1;
		}
			break;

		case GLUT_KEY_DOWN:
		if (mod == GLUT_ACTIVE_SHIFT){
			for (std::list<SceneObject>::iterator it=shapes.begin(); it != shapes.end(); ++it){
				if (it->selected){
					it->position[2] += 1;
				}
			}
		}
		else{ 
			camPos[1] -= 1;
		}
			break;
		case GLUT_KEY_F1:
			light_pos0[1] -= 5;
			light_pos1[1] -= 5;
			glutPostRedisplay();
			break;
		case GLUT_KEY_F2:
			light_pos0[1] += 5;
			light_pos1[1] += 5;
			glutPostRedisplay();
			break;
		case GLUT_KEY_F3:
			light_pos0[2] += 5;
			light_pos1[2] += 5;
			glutPostRedisplay();
		break;
		case GLUT_KEY_F4:
			light_pos0[2] -= 5;
			light_pos1[2] -= 5;
			glutPostRedisplay();
		break;

	}
	glutPostRedisplay();
}

void drawAxis()
{
    glPushMatrix();
    glBegin(GL_LINES);
    glColor3f(1, 0, 0);
    glVertex3f(-1000,0,0);
    glVertex3f(1000,0,0);
    glColor3f(0,1,0);
    glVertex3f(0,-1000,0);
    glVertex3f(0,1000,0);
    glColor3f(0,0,1);
    glVertex3f(0,0,-1000);
    glVertex3f(0,0,1000);
    glEnd();
    
    glPopMatrix();
}


//calculate weather an intersection of our ray hits the teapot
void CalcIntersections(SceneObject &s){
	//---Construct ray-----------------------------------------------------
	//construct Ray
	GLdouble R0[3], R1[3], Rd[3];
	GLdouble modelMat[16], projMat[16];
	GLint viewMat[4];

	//populate mpv matricies
	glGetDoublev(GL_MODELVIEW_MATRIX, modelMat);
	glGetDoublev(GL_PROJECTION_MATRIX, projMat);
	glGetIntegerv(GL_VIEWPORT, viewMat);

	//calculate near point
	gluUnProject(mouseX, mouseY, 0.0, modelMat, projMat, viewMat, &R0[0], &R0[1], &R0[2]);
	//calculate far point
	gluUnProject(mouseX, mouseY, 1.0, modelMat, projMat, viewMat, &R1[0], &R1[1], &R1[2]);

	//calcualte our ray from R0 and R1
	Rd[0] = R1[0] - R0[0];
	Rd[1] = R1[1] - R0[1];
	Rd[2] = R1[2] - R0[2];

	//turn ray Rd into unit ray 
	GLdouble m = sqrt(Rd[0]*Rd[0] + Rd[1]*Rd[1] + Rd[2]*Rd[2]);
	Rd[0] /= m;
	Rd[1] /= m;
	Rd[2] /= m;

	printf("R0: %f, %f, %f | ", R0[0], R0[1], R0[2]);
	printf("R1: %f, %f, %f | ", R1[0], R1[1], R1[2]);
	printf("Rd: %f, %f, %f | ", Rd[0], Rd[1], Rd[2]);

	//---calculate intersection point now-----------------------------------
	//approx the teapot with a box of radius 1 centered around the teapot centered
	//goes against the xy plane to test the Intersection
	//NOTE: this is not the code from slides, but rather proof of concept
	//using assumtions which are true for this example only. 

	//calculate t value from z dir;
	double t = (((double)s.position[2]) - R0[2])/Rd[2];

		printf("t: %f | ", t);

		//use t value to find x and y of our intersection point
		double pt[3];
		pt[0] = R0[0] + t * Rd[0];
		pt[1] = R0[1] + t * Rd[1];
		pt[2] = s.position[2];
		
		printf("pt: %f, %f, %f | ", pt[0], pt[1], pt[2]);

		//now that we have our point on the xy plane at the level of the teapot,
		//use it to see if this point is inside a box centered at the teapots
		//location
		// if(pt[0] > s.position[0] - BOUND_OFFSET && pt[0] < s.position[0] + BOUND_OFFSET &&
		// 	pt[1] > s.position[1]- BOUND_OFFSET && pt[1] < s.position[1]+ BOUND_OFFSET &&
		// 	pt[2] > s.position[2] - BOUND_OFFSET && pt[2] < s.position[2] + BOUND_OFFSET){
		// 	s.intersected = true;
		// 	printf("YAAAAAS\n");
		// }
		if(pt[0] > s.xMin && pt[0] < s.xMax &&
			pt[1] > s.yMin && pt[1] < s.yMax &&
			pt[2] > s.zMin && pt[2] < s.zMax){
			s.intersected = true;
			printf("YAAAAAS\n");
		}

	

	
}

//display function, also calls the position update and ray calc
void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glLightfv(GL_LIGHT0, GL_POSITION, light_pos0);
	glLightfv(GL_LIGHT1, GL_POSITION, light_pos1);

	
	
	gluLookAt(camPos[0], camPos[1], camPos[2], 0, 0, 0, 0,1,0);
	printf("%f,%f,%f\n",camPos[0], camPos[1], camPos[2]);
	printf("light_pos0: %f,%f,%f\n",light_pos0[0],light_pos0[1],light_pos0[2]);
	printf("light_pos1: %f,%f,%f\n",light_pos1[0],light_pos1[1],light_pos1[2]);
	
	glPushMatrix();

		glRotatef(SceneAngleY,0,1,0);
		glRotatef(SceneAngleZ,0,0,1);

		drawAxis();
		drawScene();
		drawObjects();
	glPopMatrix();
	
	
	//switch our buffers for a smooth animation
	glutSwapBuffers();
}

//keyboard for exiting when q or escape is pressed
void keyboard(unsigned char key, int xIn, int yIn)
{
	int mod = glutGetModifiers();
	switch (key)
	{	
		case 91: // [
			SceneAngleY --;
			glutPostRedisplay();
			break;
		case 93: // ]
			SceneAngleY ++;
			glutPostRedisplay();
			break;
		case 57:
			SceneAngleZ --;
			glutPostRedisplay();
			break;
		case 48:
			SceneAngleZ ++;
			glutPostRedisplay();
			break;
		case 49:
			materialCurrent = 0;
			cout<<"material 0"<<endl;
			break;
		case 50:
			materialCurrent = 1;
			cout<<"material 1"<<endl;
			break;
		case 51:
			materialCurrent = 2;
			cout<<"material 2"<<endl;
			break;
		case 52:
			materialCurrent = 3;
			cout<<"material 3"<<endl;
			break;
		case 53:
			materialCurrent = 4;
			cout<<"material 4"<<endl;
			break;
		case 'q':
		case 27:	//27 is the esc key
			exit(0);
			break;
		case 'C':
		case 'c':
			{
			SceneObject c; //cube
			c.setType(1);
			c.materialState = materialCurrent;
			shapes.insert(shapes.end(), c);
			glutPostRedisplay();
			break;
		}
		case 'S':
		case 's': 
			{
			SceneObject c; //sphere
			c.setType(2);
			c.materialState = materialCurrent;
			shapes.insert(shapes.end(), c);
			glutPostRedisplay();
			break;
		}
		case 'T':
		case 't':
			{
			SceneObject c; // teapot
			c.setType(4);
			c.materialState = materialCurrent;
			shapes.insert(shapes.end(), c);
			glutPostRedisplay();
			break;
		}
		case 'N':
		case 'n':
			{
			SceneObject c; // cone
			c.setType(3);
			c.materialState = materialCurrent;
			shapes.insert(shapes.end(), c);
			glutPostRedisplay();
			break;
		}
		case 'D':
		case 'd':
		{
			if (mod == GLUT_ACTIVE_SHIFT){
				for (std::list<SceneObject>::iterator it=shapes.begin(); it != shapes.end(); ++it){
				if (it->selected){
					it->orientation[1] += 4;
				}
				}
				glutPostRedisplay();
				break;
		}
			else{
				SceneObject c; 
				c.setType(5); 	//torus
				c.materialState = materialCurrent;
				shapes.insert(shapes.end(), c);
				glutPostRedisplay();
				break;
			}
			
		}
		case 'M':
		case 'm':
			for (std::list<SceneObject>::iterator it=shapes.begin(); it != shapes.end(); ++it){
				if (it->selected){
					it->changeMaterial(materialCurrent);
				}
			}
			glutPostRedisplay();
			break;
		case 'R':
		case 'r':
		{
			camPos[0]=23;
			camPos[1]=18;
			camPos[2]=33;
			shapes.clear();
			glutPostRedisplay();
			break;
		}
		case 'l':
		case 'L':
			switch(lightState){
				case 1:	//light are all on
					glDisable(GL_LIGHT0);
					lightState = 2;
					glutPostRedisplay();
					break;
				case 2:
					glDisable(GL_LIGHT1);
					lightState = 3;
					glutPostRedisplay();
					break;
				case 3:	//they are both disables
					glEnable(GL_LIGHT0);
					lightState = 4;
					glutPostRedisplay();
					break;
				case 4:
					glEnable(GL_LIGHT1);
					lightState = 1;
					glutPostRedisplay();
					cout<<"here"<<endl;
					break;
			}
		case 'A':
		case 'a':
		{
			if (mod == GLUT_ACTIVE_SHIFT){
				for (std::list<SceneObject>::iterator it=shapes.begin(); it != shapes.end(); ++it){
				if (it->selected){
					it->orientation[1] -= 4;
				}
			}
		}
			
			glutPostRedisplay();
			break;

		}
		




	}
}

//initialize values
void init(void)
{
	glClearColor(0.118, 0.565, 1.000, 1);
	glColor3f(1, 1, 1);

	
	//glEnable(GL_COLOR_MATERIAL);
	glFrontFace(GL_CCW);
	glCullFace(GL_BACK);
	glEnable(GL_CULL_FACE);


	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45, 1, 1, 100);


	//ENABLING THE LIGHTING YAY
	glEnable(GL_LIGHTING); 
	glEnable(GL_DEPTH_TEST);
	
	//initially lightstate 1
	glEnable(GL_LIGHT0); 
	glEnable(GL_LIGHT1); 

	glLightfv(GL_LIGHT0, GL_AMBIENT, amb0); 
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diff0); 
	glLightfv(GL_LIGHT0, GL_SPECULAR, spec0);

	glLightfv(GL_LIGHT1, GL_AMBIENT, amb0); 
	glLightfv(GL_LIGHT1, GL_DIFFUSE, diff0); 
	glLightfv(GL_LIGHT1, GL_SPECULAR, spec0);
}
void Change2False(SceneObject &s){
	s.selected = false;
	s.intersected = false;
}

//save our mouse coords when they change
void mouse(int btn, int state, int x, int y){
	mouseX = x;
	mouseY = WINDOW_SIZE_HEIGHT - y;
	for (std::list<SceneObject>::iterator it=shapes.begin(); it != shapes.end(); ++it){
				Change2False(*it);
			}
	for (std::list<SceneObject>::iterator it=shapes.begin(); it != shapes.end(); ++it){
				CalcIntersections(*it);
			}
	
	
	if (btn == GLUT_LEFT_BUTTON){
		
		if (state == GLUT_UP){
			for (std::list<SceneObject>::iterator it=shapes.begin(); it != shapes.end(); ++it){
				if (it->intersected){
					it->selected = true;
				}
			}	
		}
	}
	if (btn == GLUT_RIGHT_BUTTON){
		if (state == GLUT_DOWN){
			for (std::list<SceneObject>::iterator it=shapes.begin(); it != shapes.end(); ++it){
				if (it->intersected){
					it = shapes.erase(it);
				}
			}
		}
	}
	glutPostRedisplay();
}

void motion(int x, int y){
	mouseX = x;
	mouseY = WINDOW_SIZE_HEIGHT - y;
	}

void passive(int x, int y){
	mouseX = x;
	mouseY = WINDOW_SIZE_HEIGHT - y;
}

//change the viewport
void reshape(int w, int h)
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	//gluOrtho2D(0, w, 0, h);
	gluPerspective(45, (float)((w+0.0f)/h), 1, 100);

	glMatrixMode(GL_MODELVIEW);
	glViewport(0, 0, w, h);
}

//make our animation run at 60fps
// void FPS(int val){
// 	glutPostRedisplay();
// 	glutTimerFunc(17, FPS, 0); // 1sec = 1000, 60fps = 1000/60 = ~17
// }


//callbacks registry
void callBackInit(){
	glutDisplayFunc(display);
	glutKeyboardFunc(keyboard);
	glutSpecialFunc(special);
	glutMouseFunc(mouse);
	glutMotionFunc(motion);
	glutPassiveMotionFunc(passive);
	glutReshapeFunc(reshape);

	//glutTimerFunc(0, FPS, 0);
}

//main program entry point
int main(int argc, char** argv)
{
	glutInit(&argc, argv);		//starts up GLUT
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

	glutInitWindowSize(WINDOW_SIZE_WIDTH, WINDOW_SIZE_HEIGHT);
	glutInitWindowPosition(50, 50);

	glutCreateWindow("3GC3 Lecture Code Ray Picking");	//creates the window

	callBackInit();

	init();

	// SceneObject cube1;
	// cube1.setType(1);
	// cube1.size=1;
	// cube1.position[0]=3;
	// cube1.position[1]=0;
	// cube1.position[2]=6;
	// shapes.insert(shapes.end(), cube1);

	glutMainLoop();				//starts the event glutMainLoop
	return(0);					//return may not be necessary on all compilers
}
