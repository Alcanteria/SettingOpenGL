#pragma once
#include "ContextInfo.h"
#include "FrameBufferInfo.h"
#include "WindowInfo.h"
#include <iostream>
#include "Init_GLEW.h"
#include "IListener.h"

namespace Core
{
	namespace Init
	{
		class Init_GLUT
		{
		public:
			static void init(const Core::WindowInfo& window, const Core::ContextInfo& context, const Core::FrameBufferInfo& frameBufferInfo);

		public:
			static void run();
			static void close();

			void enterFullscreen();
			void exitFullscreen();

			// Used to print info about OpenGL
			static void printOpenGLInfo(const Core::WindowInfo& windoInfo, const Core::ContextInfo& contextInfo);

			static void SetListener(Core::IListener*& iListener);

		private:
			static void idleCallBack(void);
			static void displayCallBack(void);
			static void reshapeCallBack(int width, int height);
			static void closeCallBack();

			static Core::IListener* listener;
			static Core::WindowInfo windowInformation;
		};
	}
}