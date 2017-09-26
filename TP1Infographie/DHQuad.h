#pragma once
#include "DrawingHandler.h"
namespace Drawing
{
	class DHQuad : public DrawingHandler
	{
		void Click(float x, float y);
		void NewPosition(float x, float y, float z, float w);
		void Draw(GLuint* buffers, GLuint program);
		DrawingHandler* getNew();
	};
}