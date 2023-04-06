using Leviathan.Mathematics;

namespace Leviathan.Physics.Shapes
{
	public struct Rectangle : IShape
	{
		public static Rectangle FromMinMax(Vector2 _min, Vector2 _max) => new Rectangle(_min, _max - _min);
		
		public Rectangle Bounds => this;
		
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
		
		public bool Intersects<SHAPE>(SHAPE _other) where SHAPE : IShape => _other switch
		{
			Circle circle => Intersects(circle),
			Rectangle rectangle => Intersects(rectangle),
			OrientedRectangle oriented => Intersects(oriented),
			_ => throw new ArgumentOutOfRangeException(nameof(_other), _other, null)
		};

		public bool Intersects(Circle _other) => _other.Intersects(this);

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

		public bool Intersects(OrientedRectangle _box)
		{
			Vector2[] axisToTest =
			{
				Vector2.Right, Vector2.Up,
				Vector2.Zero, Vector2.Zero
			};
			
			Matrix2x2 rotationMat = Matrix2x2.FromAngle(_box.ThetaRotation);
			
			Vector2 axis = new Vector2(_box.halfExtents.x, 0).Normalized;
			if(!MatrixMath.Multiply(out float[]? output, axis, 1, 2, rotationMat, 2, 2))
				return false;

			axisToTest[2] = output!;
			
			axis = new Vector2(0, _box.halfExtents.y).Normalized;
			if(!MatrixMath.Multiply(out output, axis, 1, 2, rotationMat, 2, 2))
				return false;

			axisToTest[3] = output!;

			foreach(Vector2 test in axisToTest)
			{
				if(!Interval.OverlapOnAxis(this, _box, test))
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