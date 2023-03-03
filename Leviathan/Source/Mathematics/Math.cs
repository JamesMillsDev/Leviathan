using System.Diagnostics.CodeAnalysis;

namespace Leviathan.Mathematics
{
	[SuppressMessage("ReSharper", "InconsistentNaming")]
	[SuppressMessage("ReSharper", "IdentifierTypo")]
	public static class Math
	{
		public const float PI = 3.14159265358979323846f;
		public const float EPSILON = float.Epsilon;
		public const float RAD2DEG = 180f / PI;
		public const float DEG2RAD = PI / 180f;

		public static float Clamp(float _val, float _min, float _max)
		{
			if(_val < _min)
				_val = _min;
			
			if(_val > _max)
				_val = _max;

			return _val;
		}

		public static float Clamp01(float _val) => Clamp(_val, 0f, 1f);
	}
}