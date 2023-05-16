#pragma once

class Time
{
public:
	/// <summary>The amount that scaled time values are affected.</summary>
	static float timeScale;

	/// <summary>The time between frames affected by <see cref="deltaTime"/>. See: <see cref="Raylib.GetFrameTime"/>.</summary>
	static float deltaTime;

	/// <summary>The total running time of the application. Affected by <see cref="timeScale"/>.</summary>
	static float time;

	/// <summary>The time between frames not affected by <see cref="deltaTime"/>. See: <see cref="Raylib.GetFrameTime"/>.</summary>
	static float unscaledDeltaTime;

	/// <summary>The total running time of the application. Unaffected by <see cref="timeScale"/>.</summary>
	static float unscaledTime;

private:
	friend class Application;

	static void Tick();

};