#include "Init_GLUT.h"

using namespace Core::Init;

void Init_GLUT::init(const Core::WindowInfo& windowInfo, const Core::ContextInfo& contextInfo, const Core::FrameBufferInfo& frameBufferInfo)
{
	// Need to create these fake arguments.
	int fakeargc = 1;
	char *fakeargv[] = { "fake", NULL };
	glutInit(&fakeargc, fakeargv);

	if (contextInfo.core)
	{
		glutInitContextVersion(contextInfo.major_version, contextInfo.minor_version);
		glutInitContextProfile(GLUT_CORE_PROFILE);
	}
	else
	{
		// Versions don't matter in compatibility mode
		glutInitContextProfile(GLUT_COMPATIBILITY_PROFILE);
	}

	// Set window properties.
	glutInitDisplayMode(frameBufferInfo.flags);
	glutInitWindowPosition(windowInfo.position_x, windowInfo.position_y);
	glutInitWindowSize(windowInfo.width, windowInfo.height);

	// Create the window with the passed name value.
	glutCreateWindow(windowInfo.name.c_str());

	std::cout << "GLUT: Initialized." << std::endl;

	// Rendering callback shit.
	glutIdleFunc(idleCallBack);
	glutCloseFunc(closeCallBack);
	glutDisplayFunc(displayCallBack);
	glutReshapeFunc(reshapeCallBack);

	Init::Init_GLEW::Init();

	glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_GLUTMAINLOOP_RETURNS);

	printOpenGLInfo(windowInfo, contextInfo);
}

void Init_GLUT::run()
{
	std::cout << "GLUT:\tStart Running." << std::endl;
	glutMainLoop();
}

void Init_GLUT::close()
{
	std::cout << "GLUT:\tFinished." << std::endl;
	glutLeaveMainLoop();
}

void Init_GLUT::idleCallBack(void)
{
	// Not doing anything yet, just call resisplay.
	glutPostRedisplay();
}

void Init_GLUT::displayCallBack()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glutSwapBuffers();
}

void Init_GLUT::reshapeCallBack(int width, int height)
{

}

void Init_GLUT::closeCallBack()
{
	close();
}

void Init_GLUT::enterFullscreen()
{
	glutFullScreen();
}

void Init_GLUT::exitFullscreen()
{
	glutLeaveFullScreen();
}

void Init_GLUT::printOpenGLInfo(const Core::WindowInfo& windowInfo, const Core::ContextInfo& contextInfo)
{
	const unsigned char* renderer = glGetString(GL_RENDERER);
	const unsigned char* vendor = glGetString(GL_VENDOR);
	const unsigned char* version = glGetString(GL_VERSION);

	std::cout << "***************************************************" << std::endl;
	std::cout << "GLUT:\tInitialise" << std::endl;
	std::cout << "GLUT:\tVendor : " << vendor << std::endl;
	std::cout << "GLUT:\tRenderer : " << renderer << std::endl;
	std::cout << "GLUT:\tOpenGL Version: " << version << std::endl;
}