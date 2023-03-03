using Raylib_CsLo;

using System.Diagnostics.CodeAnalysis;

using Math = Leviathan.Mathematics.Math;

namespace Leviathan
{
	/// <summary>Contains all variables associated with time such as the global <see cref="deltaTime"/>.</summary>
	[SuppressMessage("Usage", "CA2211:Non-constant fields should not be visible")]
	[SuppressMessage("ReSharper", "FieldCanBeMadeReadOnly.Global")]
	[SuppressMessage("ReSharper", "ConvertToConstant.Global")]
	public static class Time
	{
		/// <summary>The amount that scaled time values are affected.</summary>
		public static float timeScale = 1f;

		/// <summary>The time between frames affected by <see cref="deltaTime"/>. See: <see cref="Raylib.GetFrameTime"/>.</summary>
		public static float deltaTime;

		/// <summary>The total running time of the application. Affected by <see cref="timeScale"/>.</summary>
		public static float time;

		/// <summary>The time between frames not affected by <see cref="deltaTime"/>. See: <see cref="Raylib.GetFrameTime"/>.</summary>
		public static float unscaledDeltaTime;

		/// <summary>The total running time of the application. Unaffected by <see cref="timeScale"/>.</summary>
		public static float unscaledTime;

		/// <summary>Updates the time values for the system. Only called by <see cref="Application"/>.</summary>
		internal static void Tick()
		{
			// Make sure time is between 0 and 1
			timeScale = Math.Clamp01(timeScale);

			// Get the amount of time between frames and update the time by it 
			deltaTime = Raylib.GetFrameTime() * timeScale;
			time += deltaTime;

			// Get the amount of time between frames and update the unscaledTime by it
			unscaledDeltaTime = Raylib.GetFrameTime();
			unscaledTime += unscaledDeltaTime;
		}
	}
}