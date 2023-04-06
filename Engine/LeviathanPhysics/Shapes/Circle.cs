using Leviathan.Mathematics;

namespace Leviathan.Physics.Shapes
{
	public struct Circle : IShape
	{
		public Rectangle Bounds => new Rectangle(center, Vector2.One * radius);
		
		public float SqrRadius => radius * radius;

		public Vector2 center;
		public float radius;

		public Circle() : this(Vector2.Zero, 1f) { }

		public Circle(Vector2 _center, float _radius)
		{
			center = _center;
			radius = _radius;
		}

		public bool Contains(Vector2 _point)
		{
			Line line = new(_point, center);

			return line.SqrLength < SqrRadius;
		}

		public bool Intersects<SHAPE>(SHAPE _other) where SHAPE : IShape => _other switch
		{
			Circle circle => circle.Intersects(this),
			Rectangle rectangle => rectangle.Intersects(this),
			OrientedRectangle oriented => oriented.Intersects(this),
			_ => throw new ArgumentOutOfRangeException(nameof(_other), _other, null)
		};

		public bool Intersects(Circle _other)
		{
			Line line = new Line(center, _other.center);
			float radiiSum = radius + _other.radius;

			return line.SqrLength <= radiiSum * radiiSum;
		}

		public bool Intersects(OrientedRectangle _box)
		{
			Vector2 rotVector = center - _box.center;
			Matrix2x2 rotationMat = Matrix2x2.FromAngle(-_box.ThetaRotation);
			
			if(!MatrixMath.Multiply(out float[]? output, rotVector, 1, 2, rotationMat, 2, 2))
				return false;

			Circle localCircle = new(output! + _box.halfExtents, radius);

			Rectangle localRect = new(Vector2.Zero, _box.halfExtents * 2.0f);
			
			return localCircle.Intersects(localRect);
		}

		public bool Intersects(Rectangle _other)
		{
			Vector2 min = _other.Min;
			Vector2 max = _other.Max;

			Vector2 closestPoint = center;

			closestPoint.x = closestPoint.x < min.x ? min.x : closestPoint.x;
			closestPoint.x = closestPoint.x > max.x ? max.x : closestPoint.x;

			closestPoint.y = closestPoint.y < min.y ? min.y : closestPoint.y;
			closestPoint.y = closestPoint.y > max.y ? max.y : closestPoint.y;

			Line line = new Line(center, closestPoint);

			return line.SqrLength <= SqrRadius;
		}
	}
}