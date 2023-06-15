#include <Leviathan/Time.h>

#include <raylib/raylib.h>

namespace Leviathan
{
	float Time::timeScale = 1.f;
	float Time::deltaTime;
	float Time::time;
	float Time::unscaledDeltaTime;
	float Time::unscaledTime;

	void Time::Tick()
	{
		// Make sure time is between 0 and 1
		if (timeScale < 0.f)
			timeScale = 0.f;

		if (timeScale > 1.f)
			timeScale = 1.f;

		// Get the amount of time between frames and update the time by it 
		deltaTime = GetFrameTime() * timeScale;
		time += deltaTime;

		// Get the amount of time between frames and update the unscaledTime by it
		unscaledDeltaTime = GetFrameTime();
		unscaledTime += unscaledDeltaTime;
	}
}