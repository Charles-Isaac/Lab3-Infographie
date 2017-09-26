#include "DHLigneContinue.h"
namespace Drawing
{
	void DHLigneContinue::Click(float x, float y)
	{
		DrawingHandler::NewPosition(x, y, 0.f, 0.5f);
	}

	void DHLigneContinue::NewPosition(float x, float y, float z, float w)
	{
		DrawingHandler::NewPosition(x, y, 0.f, 0.5f);
	}

	void DHLigneContinue::Draw(GLuint* buffers, GLuint program)
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
	DrawingHandler * DHLigneContinue::getNew()
	{
		return new DHLigneContinue();
	}
}