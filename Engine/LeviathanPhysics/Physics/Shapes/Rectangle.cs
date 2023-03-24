using Leviathan.Mathematics;

namespace Leviathan.Physics.Shapes
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

		public bool Intersects(Rectangle _other)
		{
			Vector2[] axisToTest = { Vector2.Right, Vector2.Up };

			foreach(Vector2 axis in axisToTest)
			{
				if(!Interval.OverlapOnAxis(this, _other, axis))
					return false;
			}

			return true;
		}

		public bool Intersects(OrientedRectangle _other)
		{
			Vector2 axis = new Vector2(_other.HalfExtents.x, 0).Normalized;
			Matrix3x3 rotMat = Matrix3x3.CreateZRotation(-_other.Rotation);
			
			Vector2[] axisToTest = { Vector2.Right, Vector2.Up, axis * rotMat, Vector2.Zero };

			axis = new Vector2(0, _other.HalfExtents.y).Normalized;
			axisToTest[3] = axis * rotMat;
			
			foreach(Vector2 a in axisToTest)
			{
				if(!Interval.OverlapOnAxis(this, _other, a))
					return false;
			}

			return true;
		}

		public static implicit operator Raylib_cs.Rectangle(Rectangle _rect) => new(_rect.Min.x, _rect.Min.y, _rect.size.x, _rect.size.y);
		public static implicit operator Rectangle(Raylib_cs.Rectangle _rect)
		{
			Vector2 min = new Vector2(_rect.x, _rect.y);
			Vector2 max = min + new Vector2(_rect.width, _rect.height);
			
			return FromMinMax(min, max);
		}
	}
}