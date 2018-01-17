#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<GL/glut.h>
#define CLOUD 1
#define WINDOW 2
void front_view();
void far_view();
void side_view();
void station();
void train();
void run();
int ch=0,tran=0,movemany=0,farx=750,fary=750;
float s=0,open_door1=0,open_door2=0;//tran s and farx fary for tranlating train in side,front & far view
bool stop_front=false,stop_far=false,stop_side=false;
int arrival=0,arrival2=0,arrival3=0;// to check when to stop
//train coordinates for side view
float v[7][2]={{-230,-130},{-230,100},{-200,130},{620,130},{620,-100},{590,-130},{590,100}}; 
float door1[6][2]={{0,-130},{0,70},{30,70},{30,-130},{60,-130},{60,70}}; 
float door2[6][2]={{370,-130},{370,70},{400,70},{400,-130},{430,-130},{430,70}};
float windows[4][2]={{-200,70},{550,70},{550,0},{-200,0}};
int x=0,y=0,z=0;//keeping track of number of turns train took in side view,front and far respectively

void print(char *s)
{
	glColor3f(1,1,1);
    while(*s)
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *s++);
}
void mykey(unsigned char c,int x,int y)
{
	switch(c)
	{
		case '0':ch=0;glutPostRedisplay();break;
		case '1':ch=1;y=0;arrival2=0;s=0;glutPostRedisplay();break;
		case '2':ch=2;z=0;arrival3=0;farx=0;fary=0;glutPostRedisplay();break;
		case '3':ch=3;x=0;arrival=0;tran=0;glutPostRedisplay();break;
	}
	glutPostRedisplay();
}
void front_train()
{
	//outer polygon front
	glLineWidth(1);
	glColor3f( 0.4, 0.4, 0.4);
	glBegin(GL_POLYGON);
		glVertex2f(-175,100);
		glVertex2f(180,100);
		glVertex2f(150,-400);
		glVertex2f(-150,-400);
	glEnd();
	//train bottom buldge
	glBegin(GL_POLYGON);
		glVertex2f(150,-400);
		glVertex2f(-150,-400);
		glVertex2f(-135,-475);
		glVertex2f(155,-475);
	glEnd();
	//border for outer polygon front
	glColor3f( 0,0,0);
	glBegin(GL_LINE_LOOP);
		glVertex2f(-175,100);
		glVertex2f(180,100);
		glVertex2f(150,-400);
		glVertex2f(-150,-400);
	glEnd();
	//train bottom buldge border
	glBegin(GL_LINE_LOOP);
		glVertex2f(150,-400);
		glVertex2f(-150,-400);
		glVertex2f(-135,-475);
		glVertex2f(155,-475);
	glEnd();
	//inner polygon
	glColor3f(0.3, 0.3 ,0.858824);
	glBegin(GL_POLYGON);
		glVertex2f(-120,50);
		glVertex2f(120,50);
		glVertex2f(100,-250);
		glVertex2f(-100,-250);
	glEnd();
	//border for inner polygon
	glColor3f( 0,0,0);
	glBegin(GL_LINE_LOOP);
		glVertex2f(-120,50);
		glVertex2f(120,50);
		glVertex2f(100,-250);
		glVertex2f(-100,-250);
	glEnd();
	//mans face
	glPushMatrix();
	glColor3f(0,0,0);
	glTranslatef(55,-125,0);
	glutSolidSphere(25,10,10);
	glPopMatrix();
	//mans eye
	glPushMatrix();
		glColor3f(1,1,1);
		glTranslatef(50,-120,0);
		glutSolidSphere(5,10,10);
	glPopMatrix();
	glPushMatrix();
		glColor3f(1,1,1);
		glTranslatef(65,-120,0);
		glutSolidSphere(5,10,10);
	glPopMatrix();
	//mans body
	glColor3f(0,0,0);
	glBegin(GL_POLYGON);
		glVertex2f(40,-150);
		glVertex2f(70,-150);
		glVertex2f(80,-250);
		glVertex2f(30,-250);
     glEnd();
	//head light 1
	glColor3f( 0.75, 0.2941, 0.1);
	glBegin(GL_POLYGON);
		glVertex2f(-100,-300);
		glVertex2f(-50,-300);
		glVertex2f(-50,-350);
		glVertex2f(-100,-350);
	glEnd();
	//border for headlight1
	glColor3f( 0,0,0);
	glBegin(GL_LINE_LOOP);
		glVertex2f(-100,-300);
		glVertex2f(-50,-300);
		glVertex2f(-50,-350);
		glVertex2f(-100,-350);
	glEnd();
	//head light 2
	glColor3f( 0.75, 0.2941, 0.1);
	glBegin(GL_POLYGON);
		glVertex2f(50,-300);
		glVertex2f(100,-300);
		glVertex2f(100,-350);
		glVertex2f(50,-350);
	glEnd();
    //border for headlight2
    glColor3f( 0,0,0);
	glBegin(GL_LINE_LOOP);
		glVertex2f(50,-300);
		glVertex2f(100,-300);
		glVertex2f(100,-350);
		glVertex2f(50,-350);
	glEnd();
}
void front_station()
{
	//platform left
	glColor3f(0.81,0.71,0.23);//front face
	glBegin(GL_POLYGON);
		glVertex2f(-500,-350);
		glVertex2f(-350,-350);
		glVertex2f(-350,-500);
		glVertex2f(-500,-500);
	glEnd();
	glColor3f(0.7,0.7,0.7);//floor
	glBegin(GL_POLYGON);
		glVertex2f(-500,-250);
		glVertex2f(-500,-350);
		glVertex2f(-350,-350);
		glVertex2f(0,0);
		glVertex2f(-150,-30);
	glEnd();
	glColor3f( 0.858824,  0.858824,0.439216 );//sidewall
	glBegin(GL_POLYGON);
		glVertex2f(-350,-350);
		glVertex2f(0,0);
		glVertex2f(-350,-500);
	glEnd();
	glColor3f(1,1,0);//donot cross line
	glBegin(GL_POLYGON);
		glVertex2f(-400,-350);
		glVertex2f(0,0);
		glVertex2f(-375,-350);
	glEnd();
	//platform right
	glColor3f(0.81,0.71,0.23);//front face
	glBegin(GL_POLYGON);
		glVertex2f(500,-350);
		glVertex2f(350,-350);
		glVertex2f(350,-500);
		glVertex2f(500,-500);
	glEnd();
	glColor3f(0.7,0.7,0.7);//floor
	glBegin(GL_POLYGON);
		glVertex2f(350,-350);
		glVertex2f(500,-350);
		glVertex2f(500,-250);
		glVertex2f(150,-30);
		glVertex2f(0,0);
	glEnd();
	glColor3f( 0.858824, 0.858824,0.439216 );//sidewall
	glBegin(GL_POLYGON);
		glVertex2f(350,-350);
		glVertex2f(0,0);
		glVertex2f(350,-500);
	glEnd();

	glColor3f(1,1,0);//donot cross line
	glBegin(GL_POLYGON);
		glVertex2f(375,-350);
		glVertex2f(400,-350);
		glVertex2f(0,0);
	glEnd();
	glPushMatrix();
		glColor3f(0,0,0);
		glTranslatef(-375,-150,0);
		glutSolidSphere(25,10,10);
	glPopMatrix();
	//body
	glColor3f(1,0,0);
	glBegin(GL_POLYGON);
		glVertex2f(-385,-170);
		glVertex2f(-365,-170);
		glVertex2f(-350,-220);
		glVertex2f(-400,-220);
	glEnd();
	//hands
	glColor3f(0,0,0);
	glBegin(GL_LINES);
		glVertex2f(-365,-170);
		glVertex2f(-335,-190);
	glEnd();
	glColor3f(0,0,0);
	glBegin(GL_LINES);
		glVertex2f(-385,-170);
		glVertex2f(-415,-190);
	glEnd();
	//legs
	glColor3f(0,0,0);
	glBegin(GL_LINES);
		glVertex2f(-365,-220);
		glVertex2f(-365,-250);
	glEnd();
	glColor3f(0,0,0);
	glBegin(GL_LINES);
		glVertex2f(-385,-220);
		glVertex2f(-385,-250);
	glEnd();
	glColor3f(0,0,0);
	glBegin(GL_POLYGON);//Board
		glVertex2f(340,250);
		glVertex2f(500,250);
		glVertex2f(500,100);
		glVertex2f(340,100);
	glEnd();
	glLineWidth(10);
	glBegin(GL_LINES);
		glVertex2f(425,100);
		glVertex2f(425,-220);
	glEnd();
	glLineWidth(1);
	glColor3f(1,1,1);
	glRasterPos2f(350,175);
	print("MG ROAD");
}
void front_view()
{ 
	glClearColor(0.496078,0.7,0.8,1);
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	glPushMatrix(); //clouds on left
		glTranslatef(-300,450,0);
		glCallList(1);
	glPopMatrix();
	glPushMatrix(); //clouds on right
		glTranslatef(300,450,0);
		glCallList(1);
	glPopMatrix();
	glColor3f(0,0,0);//track
	glBegin(GL_LINES);
		glVertex2f(0,0);
		glVertex2f(160,-500);
	glEnd();
	glBegin(GL_LINES);
		glVertex2f(0,0);
		glVertex2f(-150,-500);
	glEnd();
	glPushMatrix();
		glScalef(s,s,s);
		front_train();
	glPopMatrix();
	if(y==1)
	{
		front_station();
		glPushMatrix();
		glScalef(s,s,s);
		front_train();
		glPopMatrix();
		arrival++;
		if(arrival>=750)
		{
			glutIdleFunc(NULL);
			stop_front=true;
		}
	}
}
void far_train()
{
	glPushMatrix();
	glLineWidth(1);
	glTranslatef(30,0,0);
	//train top
	glColor3f(0.3,0.30,0.30);
	glBegin(GL_POLYGON);
		glVertex2f(210,210);
		glVertex2f(160,230);
		glVertex2f(-300,-50);
		glVertex2f(-250,-70);
		
	glEnd();
	//train front
	glColor3f( 0.6,0.6,0.6);
	glBegin(GL_POLYGON);
		glVertex2f(-300,-50);
		glVertex2f(-250,-70);
		glVertex2f(-275,-165);
		glVertex2f(-330,-150);
	glEnd();
	//train front window
	glColor3f( 0.196078, 0.196078,0.8);
	glBegin(GL_POLYGON);
		glVertex2f(-295,-70);
		glVertex2f(-260,-80);
		glVertex2f(-280,-145);
		glVertex2f(-320,-135);
	glEnd();
	//train front bottom
	glColor3f( 0.6,0.6,0.6);
	glBegin(GL_POLYGON);
		glVertex2f(-330,-150);
		glVertex2f(-275,-165);
		glVertex2f(-270,-180);
		glVertex2f(-320,-185);
	glEnd();
	//train side
	glColor3f( 0.5,0.5,0.5);
	glBegin(GL_POLYGON);
		glVertex2f(-250,-70);
		glVertex2f(-275,-165);
		glVertex2f(-270,-180);
		glVertex2f(210,150);
		glVertex2f(210,210);
	glEnd();
	glPopMatrix();
	//windows
	glColor3f(0.3, 0.3 ,0.858824);
	glBegin(GL_POLYGON);
		glVertex2f(-190,-70);
		glVertex2f(230,195);
		glVertex2f(230,160);
		glVertex2f(-190,-120);
	glEnd();
	//door
	glColor3f(1,1,1);
	glBegin(GL_POLYGON);
		glVertex2f(-100,10);
		glVertex2f(-60,30);
		glVertex2f(-50,-50);
		glVertex2f(-90,-75);
	glEnd();
	//door outline
	glColor3f(0,0,0);
	glBegin(GL_LINE_LOOP);
		glVertex2f(-100,10);
		glVertex2f(-80,20);
		glVertex2f(-70,-63);
		glVertex2f(-90,-75);
	glEnd();
	glBegin(GL_LINE_LOOP);	
		glVertex2f(-80,20);
		glVertex2f(-70,-63);
		glVertex2f(-50,-50);
		glVertex2f(-60,30); 
	glEnd();
	//door 2
	glColor3f(1,1,1);
	glBegin(GL_POLYGON);
		glVertex2f(150,155);
		glVertex2f(180,175);
		glVertex2f(180,105);
		glVertex2f(150,85);
	glEnd();
	//door 2 outline
	glColor3f(0,0,0);
	glBegin(GL_LINE_LOOP);
		glVertex2f(150,155);
		glVertex2f(165,165);
		glVertex2f(165,95);
		glVertex2f(150,85);
	glEnd();
	glBegin(GL_LINE_LOOP);	
		glVertex2f(165,165);
		glVertex2f(165,95);
		glVertex2f(180,105);
		glVertex2f(180,175);
	glEnd();
}
void far_view()
{
	glClearColor( 0.74902,  0.847059, 1,1);
	glClear(GL_COLOR_BUFFER_BIT);
	float cx=20,cy=20,r=160,dy=0.07,x1,y1;
	int i,theta,n=1200;
	glPushMatrix(); //clouds on left
		glTranslatef(-450,350,0);
		glCallList(1);
	glPopMatrix();
	glPushMatrix(); //clouds on middle
		glTranslatef(-50,450,0);
		glCallList(1);
	glPopMatrix();
	glColor3f(0.9,0.9,0.9);// the flyover
	glBegin(GL_POLYGON);
		glVertex2f(-500,-300);
		glVertex2f(-500,-200);
		glVertex2f(350,500);
		glVertex2f(500,500);
		glVertex2f(500,400);
		glVertex2f(300,200);
		glVertex2f(250,150);
		glVertex2f(150,50);
		glVertex2f(50,-50);
		glVertex2f(-50,-150);
		glVertex2f(-150,-250);
		glVertex2f(-250,-350);
		glVertex2f(-400,-500);
		glVertex2f(-500,-500);
	glEnd();// end of flyover
	glColor3f(0,0,0);
	glBegin(GL_POLYGON); // pillar for flyover
		glVertex2f(0,-95);
		glVertex2f(0,-500);
		glVertex2f(-50,-500);
		glVertex2f(-50,-145);
	glEnd();
	glBegin(GL_POLYGON); // pillar for flyover
		glVertex2f(300,200);
		glVertex2f(300,-300);
		glVertex2f(250,-300);
		glVertex2f(250,150);
	glEnd();
	//call train
	glPushMatrix();
		glTranslatef(farx,fary,0);
		far_train();
	glPopMatrix();
	//tunnel
	glPushMatrix();
		//tunnel shade
		glColor3f(0.196078, 0.8,0.196078);
		glTranslatef(150,200,0);
		for(i=0;i<n;i++)
		{
			glBegin(GL_POINTS);
			for(theta=0;theta<=180;theta++)
			{
				x1=cx+r*cos(3.14*theta/180);
				y1=cy+r*sin(3.14*theta/180);
				glVertex2f(x1,y1);
				glFlush();
			}
			glEnd();
			cy=cy+dy;
			cx=cx+dy;
		}
		//outline for tunnel
		glColor3f( 0.137255 , 0.556863, 0.137255);
		glPointSize(5);
		glBegin(GL_POINTS);
			for(theta=0;theta<=180;theta++)
			{
				x1=15+r*cos(3.14*theta/180);
				y1=15+r*sin(3.14*theta/180);
				glVertex2f(x1,y1);
				glFlush();
			}
		glEnd();
	glPopMatrix(); //end of tunnel
	//Sun
	glPushMatrix();
	glColor3f(1,0.25,0);
	glTranslatef(-300,400,0);
	glutSolidSphere(25,10,10);
	glPopMatrix();
	glBegin(GL_LINES);
		glVertex2f(-340,420);//sun ray 1
		glVertex2f(-265,375);
		glVertex2f(-300,440);//sun ray 2 mid
		glVertex2f(-300,360);
		glVertex2f(-340,395);//sun ray 3
		glVertex2f(-260,395);
		glVertex2f(-260,420);//sun ray 4
		glVertex2f(-340,380);
	glEnd();// end of sun 
	if(z==1)
	{
		arrival3++;
		if(arrival3==350)
		{
			glutIdleFunc(NULL);
			stop_far=true;
		}
	}

}

void door_open()
{
	glClearColor(0,1,1,1);
	glClear(GL_COLOR_BUFFER_BIT);
	if(ch==4)
	{
	glPushMatrix();
		station();
		glTranslatef(tran,0,0);//Translate the train to the last position when it stopped
		train();
	glPopMatrix();
	}
}
void train()
{
	//Train
	glColor3f( 0.752941, 0.752941, 0.752941);
	glBegin(GL_TRIANGLES);
		glVertex2fv(v[1]);
		glVertex2fv(v[0]);
		glVertex2f(v[0][0]-80,v[0][1]+30);
		glVertex2fv(v[0]);
		glVertex2f(v[0][0]-80,v[0][1]+30);
		glVertex2f(v[0][0]-80,v[0][1]);
	glEnd();
	glBegin(GL_POLYGON);
		glVertex2fv(v[0]);
		glVertex2fv(v[1]);
		glVertex2fv(v[2]);
		glVertex2fv(v[3]);
		glVertex2fv(v[4]);
		glVertex2fv(v[5]);
		glVertex2fv(v[6]);
	glEnd();
	//train back
	glBegin(GL_TRIANGLES);
		glVertex2fv(v[6]);
		glVertex2fv(v[5]);
		glVertex2f(v[5][0]+30,v[5][1]);

	glEnd();
	glColor3f(0.3,0.3,0.3);
	glBegin(GL_POLYGON);
		glVertex2fv(v[3]);
		glVertex2fv(v[6]);
		glVertex2f(v[5][0]+30,v[5][1]);
		glVertex2f(v[4][0]+45,v[4][1]+10);

	glEnd();
	//train top
	glColor3f(0.4,0.4,0.4);
	glBegin(GL_POLYGON);
	glVertex2fv(v[1]);
		glVertex2fv(v[2]);
		glVertex2fv(v[3]);
		glVertex2fv(v[6]);
	glEnd();
	//window 1
	glColor3f(0.3, 0.3 ,0.858824);
	glBegin(GL_POLYGON);
		glVertex2fv(windows[0]);
		glVertex2fv(windows[1]);
		glVertex2fv(windows[2]);
		glVertex2fv(windows[3]);
	glEnd();
	//door 1 and door 2 background when door opens
	glColor3f(1,1,1);
	glBegin(GL_POLYGON);
		glVertex2fv(door1[0]);
		glVertex2fv(door1[1]);
		glVertex2fv(door1[5]);
		glVertex2fv(door1[4]);
	glEnd();
	glBegin(GL_POLYGON);
		glVertex2fv(door2[0]);
		glVertex2fv(door2[1]);
		glVertex2fv(door2[5]);
		glVertex2fv(door2[4]);
	glEnd();
	//door 1 left side
	glPushMatrix();
	glTranslatef(open_door1,0,0);/*open door to left, open_door1 will be > 0, 
								only after it arrives to station, ch=4 */
	glColor3f(1,1,1);
	glBegin(GL_POLYGON);
		glVertex2fv(door1[0]);
		glVertex2fv(door1[1]);
		glVertex2fv(door1[2]);
		glVertex2fv(door1[3]);
	glEnd();
	glColor3f(0,0,0);
	glBegin(GL_LINE_LOOP);
		glVertex2fv(door1[0]);
		glVertex2fv(door1[1]);
		glVertex2fv(door1[2]);
		glVertex2fv(door1[3]);
	glEnd();
	glPopMatrix();
	//door 1 right side
	glPushMatrix();
	glTranslatef(open_door2,0,0);/* open door to right, open_door2 will be > 0, 
								only after it arrives to station, ch=4*/
	glColor3f(1,1,1);
	glBegin(GL_POLYGON);
		glVertex2fv(door1[3]);
		glVertex2fv(door1[2]);
		glVertex2fv(door1[5]);
		glVertex2fv(door1[4]);
	glEnd();
	glColor3f(0,0,0);
	glBegin(GL_LINE_LOOP);
		glVertex2fv(door1[3]);
		glVertex2fv(door1[2]);
		glVertex2fv(door1[5]);
		glVertex2fv(door1[4]);
	glEnd();
	glPopMatrix();
	//door 2 left side
	glPushMatrix();
	glTranslatef(open_door1,0,0);//open door to left, open_door1 will be > 0, only when ch=4
	glColor3f(1,1,1);
	glBegin(GL_POLYGON);
		glVertex2fv(door2[0]);
		glVertex2fv(door2[1]);
		glVertex2fv(door2[2]);
		glVertex2fv(door2[3]);
	glEnd();
	glColor3f(0,0,0);
	glBegin(GL_LINE_LOOP);
		glVertex2fv(door2[0]);
		glVertex2fv(door2[1]);
		glVertex2fv(door2[2]);
		glVertex2fv(door2[3]);
	glEnd();
	glPopMatrix();
	//door 2 right side
	glPushMatrix();
	glTranslatef(open_door2,0,0);// open door to right, open_door2 will be > 0, 
								//only after it arrives to station, ch=4
	glColor3f(1,1,1);
	glBegin(GL_POLYGON);
		glVertex2fv(door2[3]);
		glVertex2fv(door2[2]);
		glVertex2fv(door2[5]);
		glVertex2fv(door2[4]);
	glEnd();
	glColor3f(0,0,0);
	glBegin(GL_LINE_LOOP);
		glVertex2fv(door2[3]);
		glVertex2fv(door2[2]);
		glVertex2fv(door2[5]);
		glVertex2fv(door2[4]);
	glEnd();
	glPopMatrix();
}
void station()
{
	glClearColor(0,1,1,1);
	int counter=1000;//timer
	char s[10];// for displaying time as string
	//Plat form front 
	glColor3f(0.25,0.25,0.25);
	glBegin(GL_LINES);
		glVertex2f(-500,-90);
		glVertex2f(500,-90);
	glEnd();
	glColor3f(0.9,0.9,0.9); //Floor
	glBegin(GL_POLYGON);
			glVertex2f(-500,-130);
			glVertex2f(500,-130);
			glVertex2f(500,-500);
			glVertex2f(-500,-500);
	glEnd();
	//Dont cross line
	glColor3f(1,1,0);
	glBegin(GL_POLYGON);
			glVertex2f(-500,-150);
			glVertex2f(500,-150);
			glVertex2f(500,-170);
			glVertex2f(-500,-170);
	glEnd(); //End of platform front
	//plat form back
	glColor3f( 0.858824,  0.858824,0.439216 );//side wall
	glBegin(GL_POLYGON);
			glVertex2f(-450,130);
			glVertex2f(500,130);
			glVertex2f(500,200);
			glVertex2f(-450,200);
	glEnd();
	//floor
	glColor3f(	0.7,0.7,0.7);
		glBegin(GL_POLYGON);
			glVertex2f(-450,200);
			glVertex2f(500,200);
			glVertex2f(500,250);
			glVertex2f(-400,250);
	glEnd();
	//dont cross line
	glColor3f(	1,1,0);
		glBegin(GL_POLYGON);
			glVertex2f(-450,210);
			glVertex2f(500,210);
			glVertex2f(500,220);
			glVertex2f(-420,220);
	glEnd(); //end of platform back
		//Board
        glColor3f(0.137255,0.137255,0.556863);
		glBegin(GL_POLYGON);
			glVertex2f(-350,320);
			glVertex2f(150,320);
			glVertex2f(150,400);
			glVertex2f(-350,400);
		glEnd();
		//text on the Board
		glColor3f(1,0.5,0);
		glRasterPos2f(-330,365);
		print("Arrival/destination : MG Road");
		glColor3f(1,0.5,0);
		glRasterPos2f(-330,335);
		print("Train will come in :");
		while(counter)
		{
			if(counter==1000&&arrival==10)
			{
				
				glRasterPos2f(-80+(counter/100),335);
				_itoa_s(counter/100,s,10);
				print(s);
			}
			if(counter==900&&arrival==100)
			{
				
				glRasterPos2f(-80+(counter/100),335);
				_itoa_s(counter/100,s,10);
				print(s);
	
			}
			if(counter==800&&arrival==200)
			{
				
				glRasterPos2f(-80+(counter/100),335);
				_itoa_s(counter/100,s,10);
				print(s);
			}
			if(counter==700&&arrival==300)
			{
				
				glRasterPos2f(-80+(counter/100),335);
				_itoa_s(counter/100,s,10);
				print(s);
			}
			if(counter==600&&arrival==400)
			{
				
				glRasterPos2f(-80+(counter/100),335);
				_itoa_s(counter/100,s,10);
				print(s);
			}
			if(counter==500&&arrival==500)
			{
				
				glRasterPos2f(-80+(counter/100),335);
				_itoa_s(counter/100,s,10);
				print(s);
			}
			if(counter==400&&arrival==600)
			{
				
				glRasterPos2f(-80+(counter/100),335);
				_itoa_s(counter/100,s,10);
				print(s);
			}
			if(counter==300&&arrival==700)
			{
				
				glRasterPos2f(-80+(counter/100),335);
				_itoa_s(counter/100,s,10);
				print(s);
			}
			if(counter==200&&arrival==800)
			{
				glRasterPos2f(-80+(counter/100),335);
				_itoa_s(counter/100,s,10);
				print(s);
			}
			if(counter==100&&arrival==900)
			{
				
				glRasterPos2f(-80+(counter/100),335);
				_itoa_s(counter/100,s,10);
				print(s);
			}
			counter--;
		}
		//board holders
         glColor3f(0.184314,0.184314,0.309804);
		glBegin(GL_POLYGON);
			glVertex2f(-250,400);
			glVertex2f(-230,400);
			glVertex2f(-230,500);
			glVertex2f(-250,500);
		glEnd();
		 glColor3f(0.184314,0.184314,0.309804);
		glBegin(GL_POLYGON);
			glVertex2f(30,400);
			glVertex2f(50,400);
			glVertex2f(50,500);
			glVertex2f(30,500);
		glEnd();
		//seats 1
	   glColor3f(1,0.5,0);
	   glBegin(GL_POLYGON);
	       glVertex2f(-440,-380);
			glVertex2f(-360,-380);
			glVertex2f(-380,-320);
	    	glVertex2f(-420,-320);
		glEnd();
        glColor3f(0,1,0.4);
	   glBegin(GL_POLYGON);
	       glVertex2f(-360,-380);
			glVertex2f(-340,-320);
			glVertex2f(-300,-320);
	    	glVertex2f(-280,-380);
		glEnd();
		glColor3f(0.7,0.65,0.25);
	   glBegin(GL_POLYGON);
	       glVertex2f(-280,-380);
			glVertex2f(-260,-320);
			glVertex2f(-220,-320);
	    	glVertex2f(-200,-380);
		glEnd();
		glColor3f(0.7,0.65,0.25);
		glBegin(GL_POLYGON);
	       glVertex2f(-200,-380);
			glVertex2f(-180,-355);
			glVertex2f(-235,-355);
		glEnd();
		glColor3f(0,0,0);
		glBegin(GL_LINE_LOOP);
	       glVertex2f(-440,-380);
			glVertex2f(-440,-430);
		glEnd();
		glColor3f(0,0,0);
		glBegin(GL_LINE_LOOP);
	       glVertex2f(-200,-380);
			glVertex2f(-200,-430);
		glEnd();
		glColor3f(0,0,0);
		glBegin(GL_LINE_LOOP);
	       glVertex2f(-180,-355);
			glVertex2f(-180,-430);
		glEnd();
		//seats 2
		glPushMatrix();
		glTranslatef(0,-60,0);
		glColor3f(1,0,0);
		glBegin(GL_POLYGON);
			glVertex2f(300,350);
			glVertex2f(310,410);
			glVertex2f(350,410);
			glVertex2f(360,350);
		glEnd();
		glColor3f(1,0,0);
		glBegin(GL_POLYGON);
			glVertex2f(300,350);
			glVertex2f(280,330);
			glVertex2f(340,330);
			glVertex2f(360,350);
		glEnd();
		glColor3f(1,1,0);
		glBegin(GL_POLYGON);
			glVertex2f(360,350);
			glVertex2f(370,410);
			glVertex2f(410,410);
			glVertex2f(420,350);
		glEnd();
		glColor3f(1,1,0);
		glBegin(GL_POLYGON);
			glVertex2f(360,350);
			glVertex2f(340,330);
			glVertex2f(400,330);
			glVertex2f(420,350);
		glEnd();
		glColor3f(1,0,1);
		glBegin(GL_POLYGON);
			glVertex2f(420,350);
			glVertex2f(430,410);
			glVertex2f(470,410);
			glVertex2f(480,350);
		glEnd();
		glColor3f(1,0,1);
		glBegin(GL_POLYGON);
			glVertex2f(420,350);
			glVertex2f(400,330);
			glVertex2f(460,330);
			glVertex2f(480,350);
		glEnd();
		//seat legs
		glColor3f(0,0,0);
		glBegin(GL_LINES);
			glVertex2f(480,350);
			glVertex2f(480,300);
		glEnd();
		glColor3f(0,0,0);
		glBegin(GL_LINES);
			glVertex2f(460,330);
			glVertex2f(460,300);
		glEnd();
		glColor3f(0,0,0);
		glBegin(GL_LINES);
			glVertex2f(280,330);
			glVertex2f(280,280);
		glEnd();
		glColor3f(0,0,0);
		glBegin(GL_LINES);
			glVertex2f(300,330);
			glVertex2f(300,300);
		glEnd();
		glPopMatrix();
		//person 1
		glPushMatrix();
		glColor3f(0,0,0);
			glTranslatef(59,-350,0);
			glutSolidSphere(25,10,10);
		glPopMatrix(); 
		//body
		glColor3f(1,0,0);
		glBegin(GL_POLYGON);
			glVertex2f(56,-370);
			glVertex2f(65,-370);
			glVertex2f(81,-450);
			glVertex2f(40,-450);
		glEnd();
		//hands
		glColor3f(0,0,0);
		glBegin(GL_LINES);
			glVertex2f(65,-370);
			glVertex2f(95,-410);
		glEnd();
		glColor3f(0,0,0);
		glBegin(GL_LINES);
			glVertex2f(56,-370);
			glVertex2f(26,-410);
		glEnd();
		 //legs
		glColor3f(0,0,0);
		glBegin(GL_LINES);
			glVertex2f(48,-450);
			glVertex2f(48,-490);
		glEnd();
		glColor3f(0,0,0);
		glBegin(GL_LINES);
			glVertex2f(73,-450);
			glVertex2f(73,-490);
		glEnd(); // end of person 1
		if(ch==5) // after the door opens, train disappears, to make it reappear
		{
			glPushMatrix();
				glTranslatef(tran,0,0);
				movemany=170;
				train();
			glPopMatrix();
		}
		// if train stopped, doors opened, move the man inside train
		glPushMatrix();
			glTranslatef(50,150+movemany,0);
			//person 2
			//head
			glPushMatrix();
				glColor3f(0,0,0);
				glTranslatef(245,-325,0);
				glutSolidSphere(25,10,10);
			glPopMatrix(); 
			//hand
			glBegin(GL_LINES);
				glVertex2f(245,-400);
				glVertex2f(265,-375);
			glEnd();
			glBegin(GL_LINES);
				glVertex2f(235,-390);
				glVertex2f(225,-375);
			glEnd();
			//shirt
			glColor3f( 0.858824,0.439216, 0.576471);
			glBegin(GL_POLYGON);
				glVertex2f(235,-400);
				glVertex2f(255,-400);
				glVertex2f(255,-350);
				glVertex2f(235,-350);
			glEnd();
			//leg
			glColor3f(0,0,1);
			glBegin(GL_POLYGON);
				glVertex2f(235,-400);
				glVertex2f(245,-400);
				glVertex2f(235,-450);
				glVertex2f(225,-450);
			glEnd();
			//leg
			glBegin(GL_POLYGON);
				glVertex2f(245,-400);
				glVertex2f(255,-400);
				glVertex2f(265,-450);
				glVertex2f(255,-450);
			glEnd(); // end of second person
		glPopMatrix();
}
void draw_window(float x,float y)
{
	glPushMatrix();
	glTranslatef(x,y,0);
	glCallList(2);
	glPopMatrix();
}

void side_view()
{
	glClearColor(0,1,1,1);
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	glLineWidth(5);
	glPushMatrix(); //clouds on left
		glTranslatef(-200,400,0);
		glCallList(1);
	glPopMatrix();
	glPushMatrix();//clouds in middle
		glTranslatef(0,200,0);
		glCallList(1);
	glPopMatrix();
	glPushMatrix();//clouds in right
		glTranslatef(300,400,0);
		glCallList(1);
	glPopMatrix();
	glColor3f(0,0,0);
	glBegin(GL_LINES);//tracks
		glVertex2f(-500,-90);
		glVertex2f(500,-90);
		glVertex2f(-500,-135);
		glVertex2f(500,-135);
	glEnd();
	glColor3f(0.9,0.9,0.9);
	glBegin(GL_POLYGON);//tracks background
		glVertex2f(-500,-90);
		glVertex2f(500,-90);
		glVertex2f(500,-130);
		glVertex2f(-500,-130);
	glEnd();
	glColor3f(0,0,0);//building1
	glColor3f(0,0,1);
	glBegin(GL_POLYGON);
		glVertex2f(-500,-90);
		glVertex2f(-400,-90);
		glVertex2f(-400,170);
		glVertex2f(-500,170);
	glEnd();
	draw_window(-490,100);
	draw_window(-450,100);
	draw_window(-490,30);
	draw_window(-450,30);
	draw_window(-490,-50);
	draw_window(-450,-50);
	glColor3f(0,0,0);
	glColor3f(1,0,0);//building 2
	glBegin(GL_POLYGON);
		glVertex2f(-400,-90);
		glVertex2f(-400,400);
		glVertex2f(-250,400);
		glVertex2f(-250,-90);
	glEnd();
	draw_window(-390,330);
	draw_window(-350,330);
	draw_window(-310,330);
	draw_window(-390,260);
	draw_window(-350,260);
	draw_window(-310,260);
	draw_window(-390,190);
	draw_window(-350,190);
	draw_window(-310,190);
	draw_window(-390,120);
	draw_window(-350,120);
	draw_window(-310,120);
	glColor3f(1,1,0);//building 6
	glBegin(GL_POLYGON);
		glVertex2f(500,-90);
		glVertex2f(400,-90);
		glVertex2f(400,300);
		glVertex2f(500,300);
	glEnd();
	draw_window(410,230);
	draw_window(410,160);
	draw_window(410,90);
	draw_window(410,20);
	draw_window(450,230);
	draw_window(450,160);
	draw_window(450,90);
	draw_window(450,20);
	glColor3f(1,0,0);// building 5
	glBegin(GL_POLYGON);
		glVertex2f(400,-90);
		glVertex2f(400,175);
		glVertex2f(300,175);
		glVertex2f(300,-90);
	glEnd();
	draw_window(310,105);
	draw_window(350,105);
	draw_window(310,35);
	draw_window(350,35);
	draw_window(310,-35);
	draw_window(350,-35);
	glColor3f(0,0,0.5);// building 4
	glBegin(GL_POLYGON);
		glVertex2f(300,-90);
		glVertex2f(300,290);
		glVertex2f(200,290);
		glVertex2f(200,-90);
	glEnd();
	draw_window(210,220);
	draw_window(250,220);
	draw_window(210,150);
	draw_window(250,150);
	draw_window(210,80);
	draw_window(250,80);
	draw_window(210,10);
	draw_window(250,10);
	glColor3f(0,0.5,0.5);//building 3
	glBegin(GL_POLYGON);
		glVertex2f(75,190);
		glVertex2f(200,190);
		glVertex2f(200,-90);
		glVertex2f(75,-90);
	glEnd();
	draw_window(85,120);
	draw_window(125,120);
	draw_window(165,120);
	draw_window(85,50);
	draw_window(125,50);
	draw_window(165,50);
	draw_window(85,-20);
	draw_window(125,-20);
	draw_window(165,-20);
	glLineWidth(2);
	glPushMatrix();
		glTranslatef(tran,0,0);//translating of train, tran increments in run()
		train();
	glPopMatrix();
	
	if(x==1) //after it roams enough, goes to station.
	{
		glClearColor(0,1,1,1);
		glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
		station();
		glPushMatrix();
			glTranslatef(tran,0,0);// train is still translating, tran increments in run()
			train();
		glPopMatrix();
		arrival++;// to keep track of when to stop the train in station
		if(arrival==1000)
		{
			glutIdleFunc(NULL);// stop the train
			stop_side=true;
			ch=4;//door open choice
			glutIdleFunc(run);// run the idle function for choice ch=4
		}
	}
	
}
void welcome()
{
	glBegin(GL_POLYGON);
			glColor3f(0.5,0.5,1);
			glVertex2f(-500,-500);
			glVertex2f(-500,500);
			glColor3f(0,0,1);
			glVertex2f(500,500);
			glVertex2f(500,-500);
	glEnd();
	glColor3f(1,1,1);
	glRasterPos2f(-150,450);
		print("R.N.S. Institute of Technology");
	glRasterPos2f(-100,350);
		print("Namma Metro");
	glColor3f(0,0,0);
	glRasterPos2f(-270,290);
		print("Instructions : Click on one of the keyboard inputs");
	glRasterPos2f(-270,250);
		print("Train coming from Far(Front View):  1");
	glRasterPos2f(-270,210);
	 print("Tunnel and the Train(Far View):  2");
	glRasterPos2f(-270,170);
	 print("Train and the Station(Side View):  3");
	glRasterPos2f(-270,130);
		print("Wait till each of the animation is completed,before you");
	glRasterPos2f(-270,90);
		print("choose next");
	glRasterPos2f(-450,-100);
		print("Project members : ");
	glRasterPos2f(-450,-200);
		print("Sheethal B.U. Gupta. (1RN11CS096)");
	glRasterPos2f(50,-200);
		print("&");
		glRasterPos2f(100,-200);
		print("Vijetha P.V.(1RN11CS120)");
	glFlush();
}
void display()
{
	
	glClear(GL_COLOR_BUFFER_BIT);
	glutIdleFunc(run);
	if(ch==0) welcome();
	else if(ch==1) //front view
	{
		if(stop_front)
			glutIdleFunc(NULL);
		front_view();
	}
	else if(ch==2) //far view
	{
		if(stop_far)
			glutIdleFunc(NULL);
		far_view();
	}
	else if(ch==3) //side view
	{
			if(stop_side)
			glutIdleFunc(NULL);
			side_view();
	}
	else if(ch==4)//open door
	{
			door_open();
	}
	else if(ch==5)//move person after door opens
	{
			station();
	}
	glNewList(CLOUD,GL_COMPILE);// definition of cloud
		glPushMatrix();
		glColor3f(1,1,1);
		glutSolidSphere(25,10,10);//left circle
		glTranslatef(40,0,0);
		glutSolidSphere(25,10,10);//right circle
		glTranslatef(-25,25,0);
		glutSolidSphere(25,10,10);//middle circle
		glPopMatrix();
	glEndList();
	glNewList(WINDOW,GL_COMPILE);// definition of window
		glColor3f(1,1,1);
		glBegin(GL_POLYGON);
			glVertex2f(10,10);
			glVertex2f(30,10);
			glVertex2f(30,50);
			glVertex2f(10,50);
		glEnd();
	glEndList();
	glutSwapBuffers();
	glFlush();
}
void myinit()
{
	//glMatrixMode(GL_PROJECTION);
	//glLoadIdentity();
	glClearColor(1,1,1,1);
	glColor3f(1.0,0.0,0.0);
	glOrtho(-500,500,-500,500,-500,500);
	//glMatrixMode(GL_MODELVIEW);
}
void run()
{
	int i,j=0;
	if(ch==1) //front view
	{
		s=s+0.001;
		if(s>=1)
		{
			s=0;
			y++;
		}
		for(i=0;i<1000000;i++);
	}
	if(ch==2)//far view
	{
		farx--;
		fary--;
		if(farx==-750 && fary==-750)
		{
			farx=750;fary=750;
			z++;
		}
		//for(i=0;i<6000;i++);
	}
	if(ch==3) //side view
	{
		tran-=1;
		if(tran<-1200)
		{
			tran=900;
			x++;
			
		}
		for(i=0;i<6000000;i++);
	}
	if(ch==4) //open door
	{
		open_door1=open_door1-0.01;
		if(open_door1<=-20) 
		{
			glutIdleFunc(NULL);
			ch=5;//set choice for man moving inside train
			glutIdleFunc(run);
		}
		open_door2=open_door2+0.01;
		if(open_door2>=20) 
		{
			glutIdleFunc(NULL);
		}
	}
	glutPostRedisplay(); 
}
void main()
{
	glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB|GLUT_DEPTH);
	glutInitWindowSize(800,600);
	glutInitWindowPosition(100,100);
	glutCreateWindow("Namma Metro");
	glutDisplayFunc(display);
	glutKeyboardFunc(mykey);
	glutIdleFunc(run);
	myinit();
	glutMainLoop();
}