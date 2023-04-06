using Raylib_cs;

namespace Leviathan.Mathematics
{
	public struct Rectangle
	{
		public static Rectangle FromMinMax(Vector2 _min, Vector2 _max) => new Rectangle(_min, _max - _min);
		
		public Vector2 Min
		{
			get
			{
				Vector2 p1 = center;
				Vector2 p2 = center + size;

				return Vector2.Min(p1, p2);
			}
		}

		public Vector2 Max
		{
			get
			{
				Vector2 p1 = center;
				Vector2 p2 = center + size;

				return Vector2.Max(p1, p2);
			}
		}

		public Vector2 center;
		public Vector2 size;

		public Rectangle() : this(Vector2.Zero, Vector2.One) { }

		public Rectangle(Vector2 _center, Vector2 _size)
		{
			center = _center;
			size = _size;
		}

		public bool Contains(Vector2 _point)
		{
			Vector2 min = Min;
			Vector2 max = Max;

			return min.x <= _point.x &&
			       min.y <= _point.y &&
			       _point.x <= max.x &&
			       _point.y <= max.y;
		}

		public bool Intersects(Rectangle _other) => Raylib.CheckCollisionRecs(this, _other);

		public Rectangle Scaled(float _scalar) => new(center, size * _scalar);

		public static implicit operator Raylib_cs.Rectangle(Rectangle _rect) => new(_rect.Min.x, _rect.Min.y, _rect.size.x, _rect.size.y);
		public static implicit operator Rectangle(Raylib_cs.Rectangle _rect)
		{
			Vector2 min = new Vector2(_rect.x, _rect.y);
			Vector2 max = min + new Vector2(_rect.width, _rect.height);
			
			return FromMinMax(min, max);
		}
	}
}