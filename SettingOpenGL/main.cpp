#pragma once
#include "Core\Init\Init_GLUT.h"
#include "Managers\Scene_Manager.h"

using namespace Core;
using namespace Init;

int main(int argc, char **argv){

	WindowInfo window(std::string("The Real Thing"), 400, 200, 800, 600, true);

	ContextInfo context(4, 5, true);
	FrameBufferInfo frameBufferInfo(true, true, true, true);
	Init_GLUT::init(window, context, frameBufferInfo);

	IListener* scene = new Managers::Scene_Manager();
	Init::Init_GLUT::SetListener(scene);

	Init_GLUT::run();

	delete scene;

	return 0;
}

