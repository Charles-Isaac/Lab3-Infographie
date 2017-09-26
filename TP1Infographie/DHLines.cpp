#include "DHLines.h"

namespace Drawing
{
	void DHLines::Draw(GLuint* buffers, GLuint program)
	{
		for (int i = 0; i < tableau.size(); i++)
		{
			if (tableau[i].size() > 1 * 4)
			{
				createDrawing(tableau[i], couleur[i], translation[i], buffers, program, creationTime[i]);
				glDrawArrays(GL_LINE_STRIP, 0, tableau[i].size() / 4/*4*/);
			}
		}
	}
	DrawingHandler* DHLines::getNew()
	{
		return new DHLines();
	}
}