#include "DHTriangles.h"

namespace Drawing
{
	void DHTriangles::Click(float x, float y)
	{
		if (tableau.size() > 0 && tableau.back().size() < 3*4)
		{
			DrawingHandler::NewPosition(x, y, 0.f, 0.5f);
		}
		else
		{
			DrawingHandler::Click(x, y);
		}
	}

	void DHTriangles::NewPosition(float x, float y, float z, float w)
	{
		//Do nothing! :D
	}


	void DHTriangles::Draw(GLuint* buffers, GLuint program)
	{
		for (int i = 0; i < tableau.size(); i++)
		{
			if (tableau[i].size() >= 3 * 4)
			{
				createDrawing(tableau[i], couleur[i], translation[i], buffers, program, creationTime[i]);
				glDrawArrays(GL_TRIANGLES, 0, tableau[i].size() / 4);
			}
		}
	}
	DrawingHandler * DHTriangles::getNew()
	{
		return new DHTriangles;
	}
}