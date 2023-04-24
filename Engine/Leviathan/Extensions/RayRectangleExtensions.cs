using Leviathan.Mathematics;

using Rectangle = Raylib_CsLo.Rectangle;

namespace Leviathan.Extensions
{
	public static class RayRectangleExtensions
	{
		public static Vector2 Size(this Rectangle _rect) => new Vector2(_rect.width, _rect.height);

		public static Vector2 Center(this Rectangle _rect)
		{
			Vector2 halfSize = _rect.Size() * 0.5f;

			return new Vector2(_rect.x + halfSize.x, _rect.y + halfSize.y);
		}
		
		public static Vector2 Min(this Rectangle _rect)
		{
			Vector2 size = _rect.Size();
			Vector2 center = _rect.Center();

			Vector2 p1 = center;
			Vector2 p2 = center + size;
			
			return Vector2.Min(p1, p2);
		}

		public static Vector2 Max(this Rectangle _rect)
		{
			Vector2 size = _rect.Size();
			Vector2 center = _rect.Center();

			Vector2 p1 = center;
			Vector2 p2 = center + size;
			
			return Vector2.Max(p1, p2);
		}

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