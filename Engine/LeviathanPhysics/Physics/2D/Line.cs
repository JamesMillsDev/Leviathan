using Leviathan.Mathematics;

using System.Diagnostics.CodeAnalysis;

namespace Leviathan.Physics
{
	public struct Line
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

		internal bool Intersects(Rectangle _rect)
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

		public bool Intersects(Box2D _box)
		{
			float theta = -_box.Rotation;
			float[] rotMat =
			{
				LMath.Cos(theta), LMath.Sin(theta),
				-LMath.Sin(theta), LMath.Cos(theta)
			};

			Line local;
			Vector2 rotVec = start - _box.Center;

			if(Matrix3x3.Multiply(out float[]? @out, rotVec, 1, 2, rotMat, 2, 2) && @out == null)
				return false;

			rotVec = @out!;
			local.start = rotVec + _box.HalfExtents;

			rotVec = end - _box.Center;

			if(Matrix3x3.Multiply(out @out, rotVec, 1, 2, rotMat, 2, 2) && @out == null)
				return false;

			rotVec = @out!;
			local.end = rotVec + _box.HalfExtents;

			Rectangle localRect = new(Vector2.Zero, _box.HalfExtents * 2f);

			return local.Intersects(localRect);
		}
	}
}