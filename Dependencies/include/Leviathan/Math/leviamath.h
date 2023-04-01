#pragma once

/// <summary>A collection of useful constants and mathematical functions.</summary>
struct leviamath
{
public:
	/// <summary>Degrees-to-radians conversion constant. Multiply a degree angle by this to get the radians equivalent.</summary>
	static const float deg2rad;

	/// <summary>Radians-to-degrees conversion constant. Multiply a radian angle by this to get the degrees equivalent.</summary>
	static const float rad2deg;

	/// <summary>The standard mathematical constant, PI (3.14).</summary>
	static const float pi;

	/// <summary>A number as close to 0 as possible without actually being 0.</summary>
	static const float epsilon;

	/// <summary>The minimum possible value a float can be.</summary>
	static const float positiveInfinity;

	/// <summary>The maximum possible value a float can be.</summary>
	static const float negativeInfinity;

	/// <summary>Returns the smaller of the two passed values.</summary>
	static float min(float _a, float _b);

	/// <summary>Returns the larger of the two passed values.</summary>
	static float max(float _a, float _b);

	/// <summary>Calculates the Sine value for the passed Theta Angle.</summary>
	static float sin(float _theta);

	/// <summary>Calculates the Cosine value for the passed Theta Angle.</summary>
	static float cos(float _theta);

	/// <summary>Calculates the Arc Tangent value for the passed x and y.</summary>
	static float atan2(float _y, float _x);

	/// <summary>Calculates the Logarithmic value for the passed value.</summary>
	static float log(float _val);

	/// <summary>Raises the passed value to the passed power.</summary>
	/// <param name="_val">The value being raised.</param>
	/// <param name="_power">The power the value is being raised to.</param>
	static float pow(float _val, float _power);

	/// <summary>Returns value rounded down regardless of decimal value.</summary>
	static float ceil(float _val);

	/// <summary>Returns value rounded up regardless of decimal value.</summary>
	static float floor(float _val);

	/// <summary>Returns the square root of the passed value.</summary>
	static float sqrt(float _val);

	/// <summary>Calculates the Exponential value for the passed value.</summary>
	static float exp(float _val);

	/// <summary>Gets the sign of the passed value.</summary>
	/// <returns>-1 if the value is a negative number, +1 if the number is a positive number.</returns>
	static float sign(float _val);

	/// <summary>Gets the Absolute value for the passed value.</summary>
	static float abs(float _val);

	/// <summary>Rounds a value to the nearest whole number, if it is at exactly 0.5, it will round up.</summary>
	/// <param name="_value">The value we want to accurately round.</param>
	static float round(float _val);

	/// <summary>Rounds a value to the nearest whole number as an integer, if it is at exactly 0.5, it will round up.</summary>
	/// <param name="_value">The value we want to accurately round.</param>
	static int roundToInt(float _val);

	static float lerp(float _a, float _b, float _t);
	static float lerpUnclamped(float _a, float _b, float _t);

	/// <summary>Ensures a value stays within the specified range.</summary>
	/// <example>5 within 0 - 10 returns 5. 19 within 0 - 10 returns 10.</example>
	/// <param name="_value">The number we are clamping.</param>
	/// <param name="_min">The minimum possible value for <paramref name="_value"/>.</param>
	/// <param name="_max">The maximum possible value for <paramref name="_value"/>.</param>
	static float clamp(float _val, float _min, float _max);

	/// <summary>Ensures the passed value remains within the range 0 - 1.</summary>
	/// <param name="_value">The number we are clamping.</param>
	static float clamp01(float _val);

	/// <summary>Checks if two floats are almost or exactly the same value.</summary>
	static float approximately(float _a, float _b);

	/// <summary>Takes a value from one range and changes it to fit another.</summary>
	/// <example>0.5 starts in 0 - 1 | Remaps to 0 in the range -1 - 1.</example>
	/// <param name="_value">The number we are remapping.</param>
	/// <param name="_oldMin">The minimum value of the old range.</param>
	/// <param name="_oldMax">The maximum value of the old range.</param>
	/// <param name="_newMin">The minimum value of the new range.</param>
	/// <param name="_newMax">The maximum value of the new range.</param>
	static float remap(float _value, float _oldMin, float _oldMax, float _newMin, float _newMax);

};