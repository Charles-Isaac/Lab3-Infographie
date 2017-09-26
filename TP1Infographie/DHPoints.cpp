#include "DHPoints.h"
namespace Drawing
{
	void Drawing::DHPoints::Click(float x, float y)
	{
		DrawingHandler::Click(x, y);
	}

	void Drawing::DHPoints::NewPosition(float x, float y, float z, float w)
	{
		//Do nothing! :D
	}

	void Drawing::DHPoints::Draw(GLuint* buffers, GLuint program)
	{
		for (int i = 0; i < tableau.size(); i++)
		{
			if (tableau[i].size() >= 1)
			{
				createDrawing(tableau[i], couleur[i], translation[i], buffers, program, creationTime[i]);
				glDrawArrays(GL_POINTS, 0, tableau[i].size() / 4);
			}
		}
	}
	DrawingHandler * DHPoints::getNew()
	{
		return new DHPoints;
	}
}
