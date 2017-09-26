#include "DHCircle.h"

namespace Drawing
{
	void DHCircle::Click(float x, float y)
	{
		if (tableau.size() > 0 && tableau.back().size() == 4)
		{
			float dx = translation.back()[0] - x;
			float dy = translation.back()[1] - y;
			float rayon = sqrt(dx*dx + dy*dy);
			int nbrOfFaces = 25;
			for (int i = 0; i <= nbrOfFaces; i++)
			{
				DrawingHandler::NewPosition(translation.back()[0]+rayon * cosf((6.28318530718f / nbrOfFaces)*i), translation.back()[1]+rayon * sinf((6.28318530718f / nbrOfFaces)*i), 0.f, 0.5f);
			};
		}
		else
		{
			DrawingHandler::Click(x, y);
		}
	}

	void DHCircle::NewPosition(float x, float y, float z, float w)
	{
		//Do nothing! :D
	}

	void DHCircle::Draw(GLuint * buffers, GLuint program)
	{
		for (int i = 0; i < tableau.size(); i++)
		{
			if (tableau[i].size() > 1 * 4)
			{
				createDrawing(tableau[i], couleur[i], translation[i], buffers, program, creationTime[i]);
				glDrawArrays(GL_TRIANGLE_FAN, 0, tableau[i].size() / 4/*4*/);
				//GL_TRIANGLE_FAN
				//GL_LINE_STRIP
			}
		}
	}

	DrawingHandler * DHCircle::getNew()
	{
		return new DHCircle();
	}
}

