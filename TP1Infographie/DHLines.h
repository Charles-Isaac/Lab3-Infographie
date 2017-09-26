#pragma once
#include "DrawingHandler.h"
namespace Drawing
{
	class DHLines : public DrawingHandler
	{
		void Draw(GLuint* buffers, GLuint program);
		DrawingHandler* getNew();
	};
}