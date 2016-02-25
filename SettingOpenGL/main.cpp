#pragma once
#include "Core\Shader_Loader.h"
#include "Core\GameModels.h"
#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include <vector>

#include "Dependencies\glew\glew.h"
#include "Dependencies\freeglut\freeglut.h"

#include <iostream>

#include "Core\Shader_Loader.h"

Models::GameModels* gameModels;
GLuint program;


void RenderScene(void){

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.0, 0.0, 1.0, 1.0);

	glBindVertexArray(gameModels->GetModel("triangle1"));
	glUseProgram(program);
	glDrawArrays(GL_TRIANGLES, 0, 3);
	glutSwapBuffers();
}

void closeCallback()
{
	std::cout << "GLUT:\t Finished" << std::endl;
	glutLeaveMainLoop();
}

void Init()
{
	
	glEnable(GL_DEPTH_TEST);

	gameModels = new Models::GameModels();
	gameModels->CreateTriangleModel("triangle1");

	// Load and compile shaders.
	Core::Shader_Loader shaderLoader;
	program = shaderLoader.CreateProgram("Shaders\\Vertex_Shader.glsl", "Shaders\\Fragment_Shader.glsl");
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

int main(int argc, char **argv){

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(500, 500);
	glutInitWindowSize(800, 600);
	glutCreateWindow("Drawing our first triangle!");
	glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_GLUTMAINLOOP_RETURNS);

	glewInit();
	if (glewIsSupported("GL_VERSION_4_5"))
	{
		std::cout << "Open GL Version is 4.5\n";
	}
	else
	{
		std::cout << "Open GL 4.5 not supported\n";
	}

	Init();

	// Register callbacks.
	glutDisplayFunc(RenderScene);
	glutCloseFunc(closeCallback);

	glutMainLoop();

	delete gameModels;
	glDeleteProgram(program);
	return 0;
}

