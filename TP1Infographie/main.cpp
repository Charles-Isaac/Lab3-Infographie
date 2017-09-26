

#include "Dependencies\glew\glew.h"
#include "Dependencies\freeglut\freeglut.h"
#include "ShaderLoader.h"
#include "DrawingHandler.h"
#include "DHLines.h"
#include "DHPoints.h"
#include "DHTriangles.h"
#include "DHQuad.h"
#include "DHLigneContinue.h"
#include "DHBoringLines.h"
#include "DHCircle.h"

Drawing::DrawingHandler* dh = new Drawing::DHLines();

GLuint prog;
GLint colorLocation;
float* backColor = new float[4]{1,1,1,1};

GLuint buffer[3];

bool awesomeMode = false;
std::vector<Drawing::DrawingHandler*> dhVect = std::vector<Drawing::DrawingHandler*>{ new Drawing::DHPoints(),new Drawing::DHBoringLines(), new Drawing::DHTriangles(), new Drawing::DHQuad(),  new Drawing::DHLigneContinue(),  new Drawing::DHLines(), new Drawing::DHCircle()};

void createDrawing(vector<float> tbl)
{
	GLuint buffer;

	glGenBuffers(1, &buffer);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, buffer);
	glBufferData(GL_ARRAY_BUFFER, tbl.size()*sizeof(float), tbl.data(), GL_STREAM_DRAW);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, 0);
}

void mouseButtonEvent(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		float w = glutGet(GLUT_WINDOW_WIDTH);
		float h = glutGet(GLUT_WINDOW_HEIGHT);
		dh->Click((x - w / 2) / w, -(y - h / 2) / h);
	}
}

void mouseEvent(int x, int y)
{
	float w = glutGet(GLUT_WINDOW_WIDTH);
	float h = glutGet(GLUT_WINDOW_HEIGHT);
	dh->NewPosition((x - w / 2) / w, -(y - h / 2) / h, 0.f, 0.5f);
	glutPostRedisplay();

}

void MouseEvent(unsigned char k, int i, int j)
{
	if ('\x1a' == k) // Ctrl + Z
	{
		dh->Undo();
		glutPostRedisplay();
	}
}

void couleurMenu(int choice)
{
	switch (choice)
	{
	case 10:
		dh->setColorFunc = []()->std::vector<float> { return std::vector<float> { 1.0f, 0.0f, 0.0f, 1.0f }; };//Rouge
		break;
	case 20:
		dh->setColorFunc = []()->std::vector<float> { return std::vector<float> { 0.0f, 0.0f, 1.0f, 1.0f }; };//Bleu
		break;
	case 30:
		dh->setColorFunc = []()->std::vector<float> { return std::vector<float> { 0.0f, 1.0f, 0.0f, 1.0f }; };//Vert
		break;
	case 40:
		dh->setColorFunc = []()->std::vector<float> { return std::vector<float> { 0.0f, 0.0f, 0.0f, 1.0f }; };//Noir
		break;
	case 50:
		dh->setColorFunc = []()->std::vector<float> { 
			return std::vector<float> { (float)rand() / RAND_MAX, (float)rand() / RAND_MAX, (float)rand() / RAND_MAX, 1.0f }; 
		};//Random
		break;
	default:
		break;
	}
	//glProgramUniform4fv(prog, colorLocation, 1, color);
	//glutPostRedisplay();
}

void couleurMenuBackground(int choice)
{
	delete backColor;
	switch (choice)
	{
	case 10:
		backColor = new float[4]{ 1.0f, 0.0f, 0.0f, 1.0f };//Rouge
		break;
	case 20:
		backColor = new float[4]{ 0.0f, 0.0f, 1.0f, 1.0f };//Bleu
		break;
	case 30:
		backColor = new float[4]{ 0.0f, 1.0f, 0.0f, 1.0f };//Vert
		break;
	case 40:
		backColor = new float[4]{ 0.0f, 0.0f, 0.0f, 1.0f };//Noir
		break;
	case 50:
		backColor = new float[4]{ (float)rand() / RAND_MAX, (float)rand() / RAND_MAX, (float)rand() / RAND_MAX, 1.0f };//Random
		break;

	default:
		break;
	}
	glutPostRedisplay();
}


void traitementMenu(int choice)
{
	switch (choice)
	{
	case 10:
	{
		Drawing::DrawingHandler* dh2 = dh->getNew();
		dh2->setColorFunc = dh->setColorFunc;
		dh = dh2; 
	}
		break;
	case 42:
		glutChangeToMenuEntry(1, "Boring Mode", 43);
		awesomeMode = true;
		break;
	case 43:
		glutChangeToMenuEntry(1, "Awesome Mode", 42);
		awesomeMode = false;
		break;
	case 87:
		glutLeaveMainLoop();
		break;
	default:
		break;
	}
	glutPostRedisplay();
}

void shapeMenu(int choice)
{
	std::vector<float>(*temp)() = dh->setColorFunc;
	dh = dhVect[(choice / 10) - 1];
	dh->setColorFunc = temp;
	glutPostRedisplay();
}


void creerMenu()
{
	int menuPrincipal, sousMenuCouleur, sousMenuShape, sousMenuCouleurBackground;
	
	sousMenuCouleur = glutCreateMenu(couleurMenu);


	glutAddMenuEntry("rouge", 10);
	glutAddMenuEntry("Bleu", 20);
	glutAddMenuEntry("Vert", 30);
	glutAddMenuEntry("Noir comme mon âme", 40);
	glutAddMenuEntry("Random", 50);



	sousMenuCouleurBackground = glutCreateMenu(couleurMenuBackground);
	
	glutAddMenuEntry("rouge", 10);
	glutAddMenuEntry("Bleu", 20);
	glutAddMenuEntry("Vert", 30);
	glutAddMenuEntry("Noir comme mon âme", 40);
	glutAddMenuEntry("Random", 50);



	sousMenuShape = glutCreateMenu(shapeMenu);

	glutAddMenuEntry("Points", 10);
	glutAddMenuEntry("Boring Lines", 20);
	glutAddMenuEntry("Triangles", 30);
	glutAddMenuEntry("Quads", 40);
	glutAddMenuEntry("Ligne continue", 50);
	glutAddMenuEntry("Awesome Lines", 60);
	glutAddMenuEntry("Circle", 70);




	menuPrincipal = glutCreateMenu(traitementMenu);

	glutAddMenuEntry("Awesome Mode",42);
	glutAddMenuEntry("Réinitialiser", 10);
	glutAddSubMenu("couleur", sousMenuCouleur);
	glutAddSubMenu("Fond", sousMenuCouleurBackground);
	glutAddSubMenu("shape", sousMenuShape);

	glutAddMenuEntry("exit", 87);
	glutAttachMenu(GLUT_RIGHT_BUTTON);


}

void AffichageFunc()
{
	glClearColor(backColor[0], backColor[1], backColor[2], backColor[3]);
	//glClearColor(1.f,0.5f,0.f,1.f);
	glClear(GL_COLOR_BUFFER_BIT);
	glLineWidth(3);
	glPointSize(15);


	if (awesomeMode)
	{
		for (int i = 0; i < dhVect.size(); i++)
		{
			dhVect[i]->Draw(buffer,prog);
		}
	}
	else
	{
		dh->Draw(buffer, prog);
	}

	
	glFlush();
}

void FonctionDeFermeture()
{
	glutLeaveMainLoop();

}





void My_timer_event(int te)
{
	//update_objects /// code to update your objects

		glutPostRedisplay(); // Redraw screen with new object data.
		
		glutTimerFunc(10, My_timer_event, 1);// timer is a one shoot must be reset after being called. By using a timed event, your application should run about the same speed on any machine.
}


int main(int argp, char** args)
{
	dh = new Drawing::DHPoints();
	glutInit(&argp, args);

	glutInitDisplayMode(GLUT_SINGLE|GLUT_RGBA);
	glutInitWindowSize(800, 600);
	glutCreateWindow("Zarathoustra");
	creerMenu();
	glutMouseFunc(mouseButtonEvent);
	glutMotionFunc(mouseEvent);
	glutKeyboardFunc(MouseEvent);


	glutDisplayFunc(AffichageFunc);

	glScalef(5, 5, 5);


	glewInit();
	glGenBuffers(2, buffer);

	ShaderLoader sl;
	prog = sl.CreateProgram("VertexShader.glsl", "FragmentShader.glsl");
	colorLocation = glGetUniformLocation(prog, "setColor");
	couleurMenu(30);

	glUseProgram( prog);
	
	for (int i = 0; i < dhVect.size(); i++)
	{
		shapeMenu((i + 1) * 10);
		couleurMenu((i+1)*10);
		dhVect[i] = dh;
	}
	shapeMenu(10);
	couleurMenu(30);

	glutTimerFunc(10, My_timer_event, 1);
	glutMainLoop();

	glutCloseFunc(FonctionDeFermeture);

	return 0;
}



