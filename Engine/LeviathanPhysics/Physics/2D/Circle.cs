using Leviathan.Mathematics;

namespace Leviathan.Physics
{
	public struct Circle
	{
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

		public bool Intersects(Circle _other)
		{
			Line line = new Line(center, _other.center);
			float radiiSum = radius + _other.radius;

			return line.SqrLength <= radiiSum * radiiSum;
		}

		public bool Intersects(OrientedRectangle _other)
		{
			Matrix3x3 rotMat = Matrix3x3.CreateZRotation(-_other.Rotation);
			
			Vector2 r = (center - _other.Center) * rotMat;

			Circle lCircle = new(r + _other.HalfExtents, radius);
			Rectangle lRect = new(Vector2.Zero, _other.HalfExtents * 2f);

			return lCircle.Intersects(lRect);
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