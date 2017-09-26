#include "DHBoringLines.h"
#include <iostream>
namespace Drawing
{
	void DHBoringLines::Click(float x, float y)
	{
		
		if (tableau.size() > 0 && tableau.back().size() < 2 * 4)
		{
			DrawingHandler::NewPosition(x, y, 0.f, 0.5f);
		}
		else
		{
			DrawingHandler::Click(x, y);
		}
	}

	void DHBoringLines::NewPosition(float x, float y, float z, float w)
	{
		//Do nothing! :D
	}

	void Drawing::DHBoringLines::Draw(GLuint* buffers, GLuint program)
	{
		for (int i = 0; i < tableau.size(); i++)
		{
			if (tableau[i].size() >= 2 * 4)
			{
				createDrawing(tableau[i], couleur[i], translation[i], buffers, program, creationTime[i]);
				glDrawArrays(GL_LINES, 0, tableau[i].size() / 4);
			}
		}
	}

	DrawingHandler*  DHBoringLines::getNew()
	{
		return new DHBoringLines();
	}
}