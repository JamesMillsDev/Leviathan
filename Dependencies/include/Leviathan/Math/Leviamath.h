#pragma once

#ifdef DLL_EXPORT
#define DLL __declspec(dllexport)
#else
#define DLL __declspec(dllimport)
#endif

#include <raylib/raylib.h>

/// <summary>A number as close to 0 as possible without actually being 0.</summary>
#define EPSILON 1.401298E-45f

/// <summary>The minimum possible value a float can be.</summary>
#define POSITIVE_INFINITY (1.f / 0.f)

/// <summary>The maximum possible value a float can be.</summary>
#define NEGATIVE_INFINITY (-1.f / 0.f)

/// <summary>Degrees-to-radians conversion constant. Multiply a degree angle by this to get the radians equivalent.</summary>
#define DEG_2_RAD (PI * 2.f / 360.f)

/// <summary>Radians-to-degrees conversion constant. Multiply a radian angle by this to get the degrees equivalent.</summary>
#define RAD_2_DEG (1.f / DEG_2_RAD)

/// <summary>A collection of useful constants and mathematical functions.</summary>
struct Leviamath
{
public:
	/// <summary>Returns the smaller of the two passed values.</summary>
	DLL static float Min(float _a, float _b);

	/// <summary>Returns the larger of the two passed values.</summary>
	DLL static float Max(float _a, float _b);

	/// <summary>Calculates the Sine value for the passed Theta Angle.</summary>
	DLL static float Sin(float _theta);

	/// <summary>Calculates the Cosine value for the passed Theta Angle.</summary>
	DLL static float Cos(float _theta);

	/// <summary>Calculates the Arc Tangent value for the passed x and y.</summary>
	DLL static float Atan2(float _y, float _x);

	/// <summary>Calculates the Logarithmic value for the passed value.</summary>
	DLL static float Log(float _val);

	/// <summary>Raises the passed value to the passed power.</summary>
	/// <param name="_val">The value being raised.</param>
	/// <param name="_power">The power the value is being raised to.</param>
	DLL static float Pow(float _val, float _power);

	/// <summary>Returns value rounded down regardless of decimal value.</summary>
	DLL static float Ceil(float _val);

	/// <summary>Returns value rounded up regardless of decimal value.</summary>
	DLL static float Floor(float _val);

	/// <summary>Returns the square root of the passed value.</summary>
	DLL static float Sqrt(float _val);

	/// <summary>Calculates the Exponential value for the passed value.</summary>
	DLL static float Exp(float _val);

	/// <summary>Gets the sign of the passed value.</summary>
	/// <returns>-1 if the value is a negative number, +1 if the number is a positive number.</returns>
	DLL static float Sign(float _val);

	/// <summary>Gets the Absolute value for the passed value.</summary>
	DLL static float Abs(float _val);

	/// <summary>Rounds a value to the nearest whole number, if it is at exactly 0.5, it will round up.</summary>
	/// <param name="_val">The value we want to accurately round.</param>
	DLL static float Round(float _val);

	/// <summary>Rounds a value to the nearest whole number as an integer, if it is at exactly 0.5, it will round up.</summary>
	/// <param name="_val">The value we want to accurately round.</param>
	DLL static int RoundToInt(float _val);

	DLL static float Lerp(float _a, float _b, float _t);
	DLL static float LerpUnclamped(float _a, float _b, float _t);

	/// <summary>Ensures a value stays within the specified range.</summary>
	/// <example>5 within 0 - 10 returns 5. 19 within 0 - 10 returns 10.</example>
	/// <param name="_val">The number we are clamping.</param>
	/// <param name="_min">The minimum possible value for <paramref name="_value"/>.</param>
	/// <param name="_max">The maximum possible value for <paramref name="_value"/>.</param>
	DLL static float Clamp(float _val, float _min, float _max);

	/// <summary>Ensures the passed value remains within the range 0 - 1.</summary>
	/// <param name="_val">The number we are clamping.</param>
	DLL static float Clamp01(float _val);

	/// <summary>Checks if two floats are almost or exactly the same value.</summary>
	DLL static float Approximately(float _a, float _b);

	/// <summary>Takes a value from one range and changes it to fit another.</summary>
	/// <example>0.5 starts in 0 - 1 | Remaps to 0 in the range -1 - 1.</example>
	/// <param name="_value">The number we are remapping.</param>
	/// <param name="_oldMin">The minimum value of the old range.</param>
	/// <param name="_oldMax">The maximum value of the old range.</param>
	/// <param name="_newMin">The minimum value of the new range.</param>
	/// <param name="_newMax">The maximum value of the new range.</param>
	DLL static float Remap(float _value, float _oldMin, float _oldMax, float _newMin, float _newMax);

};
