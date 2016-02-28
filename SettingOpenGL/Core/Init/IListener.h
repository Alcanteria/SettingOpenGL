#pragma once
namespace Core
{

	class IListener
	{
	public:
		virtual ~IListener() = 0;

		// Draw functions.
		virtual void notifyBeginFrame() = 0;
		virtual void notifyDisplayFrame() = 0;
		virtual void notifyEndFrame() = 0;
		virtual void notifyReshape(int width, int height, int previousWidth, int previousHeight) = 0;
	};

	inline IListener::~IListener()
	{

	}
}