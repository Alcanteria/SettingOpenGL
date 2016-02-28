#include "Scene_Manager.h"
using namespace Managers;

Scene_Manager::Scene_Manager()
{
	glEnable(GL_DEPTH_TEST);

	shader_manager = new Shader_Manager();
	shader_manager->CreateProgram("colorShader", "Shaders\\Vertex_Shader.glsl", "Shaders\\Fragment_Shader.glsl");
}

Scene_Manager::~Scene_Manager()
{
	delete shader_manager;
}

void Scene_Manager::notifyBeginFrame()
{

}

void Scene_Manager::notifyDisplayFrame()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.0, 0.0, 0.0, 1.0);
}

void Scene_Manager::notifyEndFrame()
{

}

void Scene_Manager::notifyReshape(int width, int height, int previousWidth, int previousHeight)
{

}