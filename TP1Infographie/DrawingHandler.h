#pragma once
#include <stdio.h>
#include <vector>
#include "Dependencies\glew\glew.h"
#include "Dependencies\freeglut\freeglut.h"
using namespace std;
namespace Drawing
{
	class DrawingHandler
	{
	public:
		std::vector<float> (*setColorFunc)();
		virtual void Click(float x, float y);
		virtual void NewPosition(float x, float y, float z, float w);
		void Undo();
		vector<vector<float>> GetArray();
		vector<float> GetArray(int i);

		virtual void Draw(GLuint* buffers, GLuint program) = 0;

		virtual DrawingHandler* getNew() = 0;

	protected:
		vector<vector<float>> tableau;
		vector<vector<float>> couleur;
		vector<vector<float>> translation;
		vector<vector<float>> rotation;
		vector<float> creationTime;

		void createDrawing(vector<float> tbl, vector<float> colors, vector<float> translation, GLuint* buffers, GLuint program, float creationTime);
	};


}
