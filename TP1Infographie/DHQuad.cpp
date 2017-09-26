#include "DHQuad.h"
namespace Drawing
{
	void DHQuad::Click(float x, float y)
	{
		if (tableau.size() > 0 && tableau.back().size() < 4 * 4)
		{
			DrawingHandler::NewPosition(x, y, 0.f, 0.5f);
		}
		else
		{
			DrawingHandler::Click(x, y);
		}
	}

	void DHQuad::NewPosition(float x, float y, float z, float w)
	{
		//Do nothing! :D
	}

	void DHQuad::Draw(GLuint* buffers, GLuint program)
	{
		for (int i = 0; i < tableau.size(); i++)
		{
			if (tableau[i].size() >= 4 * 4)
			{
				vector<float> tempTable = vector<float> {  tableau[i][0], tableau[i][1], tableau[i][2], tableau[i][3],
														   tableau[i][4], tableau[i][5], tableau[i][6], tableau[i][7],
														   tableau[i][8], tableau[i][9], tableau[i][10], tableau[i][11],
														   tableau[i][0], tableau[i][1], tableau[i][2], tableau[i][3],
														   tableau[i][8], tableau[i][9], tableau[i][10], tableau[i][11],
														   tableau[i][12], tableau[i][13], tableau[i][14], tableau[i][15]
				};																		 
				createDrawing(tableau[i], couleur[i], translation[i], buffers, program, creationTime[i]);
				glDrawArrays(GL_TRIANGLE_STRIP, 0, tableau[i].size() / 4);
			}
		}
	}
	DrawingHandler * DHQuad::getNew()
	{
		return new DHQuad;
	}
}