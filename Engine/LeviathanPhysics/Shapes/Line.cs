using Leviathan.Mathematics;

using System.Diagnostics.CodeAnalysis;

namespace Leviathan.Physics.Shapes
{
	public struct Line : IShape
	{
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

			return LMath.Approximately(_point.y, M * _point.x + B);
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
			Matrix3x3 rotMat = Matrix3x3.CreateZRotation(-_box.Rotation);

			Line local;
			local.start = (start - _box.Center) * rotMat + (Vector3)_box.HalfExtents;
			local.end = (end - _box.Center) * rotMat + (Vector3)_box.HalfExtents;

			Rectangle localRect = new(Vector2.Zero, _box.HalfExtents * 2f);

			return local.Intersects(localRect);
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

			float tMin = LMath.Max(LMath.Min(min.x, max.x), LMath.Min(min.y, max.y));
			float tMax = LMath.Min(LMath.Max(min.x, max.x), LMath.Max(min.y, max.y));

			if(tMin < 0 || tMin > tMax)
				return false;

			float t = tMin < 0 ? tMax : tMin;

			return t > 0f && t * t < SqrLength;
		}
	}
}