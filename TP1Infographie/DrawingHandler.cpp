#include "DrawingHandler.h"
#include <iostream>
#include "Dependencies/glm/glm.hpp"
#include "Dependencies/glm/gtc/matrix_transform.hpp"
#include "Dependencies/glm/gtc/type_ptr.hpp"
namespace Drawing
{
	void DrawingHandler::Click(float x, float y)
	{
		creationTime.push_back(GetTickCount());
		tableau.push_back(vector<float>());
		tableau.back().push_back(0);
		tableau.back().push_back(0);
		tableau.back().push_back(0.f);
		tableau.back().push_back(0.5f);
		std::vector<float> temp = setColorFunc();
		couleur.push_back(vector<float>());
		couleur.back().insert(std::end(couleur.back()), std::begin(temp), std::end(temp));

		translation.push_back(vector<float>());

		translation.back().push_back(x);
		translation.back().push_back(y);
		translation.back().push_back(0);
		translation.back().push_back(0.5f);

		rotation.push_back(vector<float>());

		

	}
	void DrawingHandler::NewPosition(float x, float y, float z, float w)
	{
		if (tableau.size() == 0)
		{
			DrawingHandler::Click(x,y);
		}
		else
		{
			float initX = translation.back()[0];
			float initY = translation.back()[1];
			float initZ = translation.back()[2];
			float initW = 0;


			tableau.back().push_back(x- initX);
			tableau.back().push_back(y- initY);
			tableau.back().push_back(z- initZ);
			tableau.back().push_back(w- initW);
			std::vector<float> temp = setColorFunc();
			couleur.back().insert(std::end(couleur.back()), std::begin(temp), std::end(temp));
			creationTime.back() = GetTickCount();
		}
	}

	void DrawingHandler::Undo()
	{
		if (tableau.size() > 0)
		{
			tableau.pop_back();
			couleur.pop_back();
			translation.pop_back();
			rotation.pop_back();
			creationTime.pop_back();
		}
	}
	vector<vector<float>> DrawingHandler::GetArray()
	{
		return tableau;
	}
	vector<float> DrawingHandler::GetArray(int i)
	{
		return tableau[i];
	}
	void DrawingHandler::createDrawing(vector<float> tbl, vector<float> colors, vector<float> translation, GLuint* buffers, GLuint program, float creationTime)
	{


		glBindBuffer(GL_ARRAY_BUFFER, buffers[0]);
		glBufferData(GL_ARRAY_BUFFER, (tbl.size())*sizeof(float), tbl.data(), GL_STREAM_DRAW);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, 0);




		glBindBuffer(GL_ARRAY_BUFFER, buffers[1]);
		glBufferData(GL_ARRAY_BUFFER, (colors.size())*sizeof(float), colors.data(), GL_STREAM_DRAW);
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, (void*)0);

		glm::mat4 translationMatrix;
		translationMatrix = glm::translate(translationMatrix, glm::vec3(translation[0]*2, translation[1]*2, translation[2]*2));//glm::vec3(sinf((GetTickCount() - creationTime) / 1000), 0.0, 0.0)
		GLint uniTrans = glGetUniformLocation(program, "translationMatrix");
		glUniformMatrix4fv(uniTrans, 1, GL_TRUE, glm::value_ptr(translationMatrix));
		
		glm::mat4 rotationMatrix;
		rotationMatrix = glm::rotate(rotationMatrix, (GetTickCount() - creationTime) / 1000.f*3.14159265359f, glm::vec3(0, 0.0, 1.0));
		GLint uniRot = glGetUniformLocation(program, "rotationMatrix");
		glUniformMatrix4fv(uniRot, 1, GL_TRUE, glm::value_ptr(rotationMatrix));
		
		//Draw
		//GLint uniTrans = glGetUniformLocation(, "trans");
		//glUniformMatrix4fv(uniTrans, 1, GL_FALSE, glm::value_ptr(trans));
		
		
		//glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, 0);

	}

}