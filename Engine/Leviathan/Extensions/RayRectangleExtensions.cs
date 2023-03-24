using Leviathan.Mathematics;

using Raylib_cs;

namespace Leviathan.Extensions
{
	public static class RayRectangleExtensions
	{
		public static Vector2 Min(this Rectangle _rect) => new Vector2(_rect.x, _rect.y);
		public static Vector2 Max(this Rectangle _rect) => new Vector2(_rect.x + _rect.width, _rect.y + _rect.height);

		public static bool Contains(this Rectangle _rect, Rectangle _other)
		{
			Vector2 aMin = _rect.Min();
			Vector2 aMax = _rect.Max();

			Vector2 bMin = _other.Min();
			Vector2 bMax = _other.Max();

			return bMin.x <= aMax.x && aMin.x <= bMax.x && bMin.y <= aMax.y && aMin.y <= bMax.y;
		}

		public static Rectangle FromMinMax(Vector2 _min, Vector2 _max)
		{
			Vector2 size = _max - _min;

			return new Rectangle(_min.x, _min.y, size.x, size.y);
		}
	}
}