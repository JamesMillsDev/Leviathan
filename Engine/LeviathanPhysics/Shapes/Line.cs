using Leviathan.Mathematics;

using System.Diagnostics.CodeAnalysis;

namespace Leviathan.Physics.Shapes
{
	public struct Line : IShape
	{
		public Rectangle Bounds => Rectangle.FromMinMax(start, end);
		
		public float Length => (end - start).Magnitude;
		public float SqrLength => (end - start).SqrMagnitude;

		public Vector2 start;
		public Vector2 end;

		public Line(Vector2 _start, Vector2 _end)
		{
			start = _start;
			end = _end;
		}

		[SuppressMessage("ReSharper", "InconsistentNaming")]
		public bool Contains(Vector2 _point)
		{
			float dx = end.x - start.x;
			float dy = end.y - start.y;
			float M = dy / dx;
			float B = start.y - M * start.x;

			return Leviamath.Approximately(_point.y, M * _point.x + B);
		}

		public bool Intersects<SHAPE>(SHAPE _other) where SHAPE : IShape => _other switch
		{
			Circle circle => Intersects(circle),
			Rectangle rectangle => Intersects(rectangle),
			OrientedRectangle oriented => Intersects(oriented),
			_ => throw new ArgumentOutOfRangeException(nameof(_other), _other, null)
		};

		public bool Intersects(Circle _circle)
		{
			Vector2 ab = end - start;
			float t = Vector2.Dot(_circle.center - start, ab) / Vector2.Dot(ab, ab);

			if(t is < 0f or > 1f)
				return false;

			Vector2 closestPoint = start + ab * t;
			Line circleToClosest = new(_circle.center, closestPoint);

			return circleToClosest.SqrLength < _circle.SqrRadius;
		}

		public bool Intersects(OrientedRectangle _box)
		{
			Matrix2x2 rotationMat = Matrix2x2.FromAngle(-_box.ThetaRotation);
			Vector2 rotVector = start - _box.center;

			Line localLine = new();
			
			if(!MatrixMath.Multiply(out float[]? output, rotVector, 1, 2, rotationMat, 2, 2))
				return false;

			localLine.start = output! + _box.halfExtents;
			rotVector = end - _box.center;
			
			if(!MatrixMath.Multiply(out output, rotVector, 1, 2, rotationMat, 2, 2))
				return false;

			localLine.end = output! + _box.halfExtents;

			Rectangle localRect = new(Vector2.Zero, _box.halfExtents * 2.0f);
			
			return localRect.Intersects(localLine);
		}

		public bool Intersects(Rectangle _rect)
		{
			if(_rect.Contains(start) || _rect.Contains(end))
				return true;

			Vector2 norm = (end - start).Normalized;
			norm.x = norm.x != 0 ? 1f / norm.x : 0;
			norm.y = norm.y != 0 ? 1f / norm.y : 0;

			Vector2 min = (_rect.Min - start) * norm;
			Vector2 max = (_rect.Max - start) * norm;

			float tMin = Leviamath.Max(Leviamath.Min(min.x, max.x), Leviamath.Min(min.y, max.y));
			float tMax = Leviamath.Min(Leviamath.Max(min.x, max.x), Leviamath.Max(min.y, max.y));

			if(tMin < 0 || tMin > tMax)
				return false;

			float t = tMin < 0 ? tMax : tMin;

			return t > 0f && t * t < SqrLength;
		}
	}
}