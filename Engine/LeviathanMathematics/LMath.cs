namespace Leviathan.Mathematics
{
	public static class LMath
	{
		/// <summary> Degrees-to-radians conversion constant. Multiply a degree angle by this constant to get the radians equivalent. </summary>
		public const float DEG_2_RAD = MathF.PI * 2f / 360f;

		/// <summary> Radians-to-degrees conversion constant. Multiply a radian angle by this constant to get the degrees equivalent. </summary>
		public const float RAD_2_DEG = 1f / DEG_2_RAD;

		/// <summary> The smallest possible float value greater than 0. </summary>
		public const float EPSILON = float.Epsilon;

		/// <summary> Finds the lower of two floats </summary>
		public static float Min(float _a, float _b) => _a < _b ? _a : _b;

		/// <summary> Finds the higher of two floats </summary>
		public static float Max(float _a, float _b) => _a > _b ? _a : _b;

		/// <summary> Rounds to the nearest number away from zero </summary>
		/// <param name="_a"> The number to be rounded </param>
		public static float Round(float _a) => MathF.Round(_a, MidpointRounding.AwayFromZero);

		/// <summary> Clamps a float value between a minimum and maximum range (inclusive) </summary>
		/// <param name="_value"> The value to be clamped </param>
		public static float Clamp(float _value, float _min, float _max)
		{
			if(_value < _min)
				_value = _min;

			if(_value > _max)
				_value = _max;

			return _value;
		}

		/// <summary> Clamps a float value between 0 and 1 (inclusive)</summary>
		/// <param name="_value"> The value to be clamped </param>
		public static float Clamp01(float _value) => _value switch
		{
			< 0f => 0f,
			> 1f => 1f,
			_ => _value
		};

		/// <summary> Checks if two floats are almost or exactly the same value </summary>
		public static bool Approximately(float _a, float _b) => Abs(_b - _a) < Max(0.000001f * Max(Abs(_a), Abs(_b)), EPSILON * 8f);

		/// <summary> Re-evaluates a value to its equivalent relative position within a new range </summary>
		/// <example> x = 1 within 0 - 2, but x = 2 within 1 - 3 </example>
		/// <param name="_value"> Value to be changed </param>
		/// <param name="_oldMin"> Minimum value for old range </param>
		/// <param name="_oldMax"> Maximum value for old range </param>
		/// <param name="_newMin"> Minimum value for new range </param>
		/// <param name="_newMax"> Maximum value for new range </param>
		public static float Remap(float _value, float _oldMin, float _oldMax, float _newMin, float _newMax) => (_value - _oldMin) / (_oldMax - _oldMin) * (_newMax - _newMin) + _newMin;

		/// <summary>
		/// Returns an integer representing the sign of the given value
		/// </summary>
		/// <returns> 1 for positive, 0 for zero, -1 for negative </returns>
		public static int Sign(float _a) => MathF.Sign(_a);

		/// <summary> Raises a number to the given power </summary>
		public static float Pow(float _a, float _power) => MathF.Pow(_a, _power);

		/// <summary> Returns the hypotenuse given two values of a right-angled triangle </summary>
		/// <remarks> a^2 = b^2 + c^2 </remarks>
		public static float Hypotenuse(float _a, float _b) => MathF.Sqrt(MathF.Pow(_a, 2) + MathF.Pow(_b, 2));

		/// <summary> Returns a value representing the missing side given one side and the hypotenuse </summary>
		/// <param name="_hypotenuse"> The hypotenuse of a given right-angled triangle </param>
		public static float ReverseHypotenuse(float _hypotenuse, float _b) => Sqrt(Pow(_hypotenuse, 2) - Pow(_b, 2));

		/// <summary> Returns the angle (in radians) given the length of two sides </summary>
		/// <param name="_a"> Opposite side to desired angle</param>
		/// <param name="_b"> Hypotenuse to desired angle </param>
		/// <returns> _a / _b </returns>
		public static float ASin(float _a, float _b) => MathF.Asin(_a / _b);

		/// <summary> Returns the angle given a value </summary>
		/// <returns> Angle in radians </returns>
		public static float ASin(float _a) => MathF.Asin(_a);

		/// <summary> Returns the sine of the specified angle </summary>
		/// <param name="_angle"> Angle in radians </param>
		public static float Sin(float _angle) => MathF.Sin(_angle);

		/// <summary> Returns the angle (in radians) given the length of two sides </summary>
		/// <param name="_a"> Adjacent side to desired angle</param>
		/// <param name="_b"> Hypotenuse to desired angle </param>
		/// <returns> _a / _b </returns>
		public static float ACos(float _a, float _b) => MathF.Acos(_a / _b);

		/// <summary> Returns the angle given a value </summary>
		/// <returns> Angle in radians </returns>
		public static float ACos(float _a) => MathF.Acos(_a);

		/// <summary> Returns the Cosine of the specified angle </summary>
		/// <param name="_angle"> Angle in radians</param>
		public static float Cos(float _angle) => MathF.Cos(_angle);
		
		/// <summary> Returns the angle given a value </summary>
		/// <returns> Angle in radians </returns>
		public static float Atan(float _a) => MathF.Atan(_a);

		/// <summary> Returns the angle (in radians) given the length of two sides </summary>
		/// <param name="_y"> Opposite side to desired angle</param>
		/// <param name="_x"> Adjacent to desired angle </param>
		/// <returns> _a / _b </returns>
		public static float Atan2(float _y, float _x) => MathF.Atan2(_y, _x);

		/// <summary> Returns the Tangent of the specified angle </summary>
		/// <remarks> <paramref name="_angle"/> normally cannot equal multiples of 90 degrees or π/2 , The EXACT value of tan(90) is undefined </remarks>
		/// <param name="_angle"> Angle in radians</param>
		public static float Tan(float _angle) => MathF.Tan(_angle);

		public static float Abs(float _val) => MathF.Abs(_val);
		
		public static float Sqrt(float _val) => MathF.Sqrt(_val);
	}
}