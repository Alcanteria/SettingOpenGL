#pragma once
#include "Shader_Manager.h"
#include "../Core/Init/IListener.h"

namespace Managers
{
	class Scene_Manager : public Core::IListener
	{
	public :
		Scene_Manager();
		~Scene_Manager();

		virtual void notifyBeginFrame();
		virtual void notifyDisplayFrame();
		virtual void notifyEndFrame();
		virtual void notifyReshape(int width, int height, int previousWidth, int previousHeight);

	private:
		Managers::Shader_Manager* shader_manager;
	};
}