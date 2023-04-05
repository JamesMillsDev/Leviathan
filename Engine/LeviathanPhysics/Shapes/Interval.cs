using Leviathan.Mathematics;

namespace Leviathan.Physics.Shapes
{
	internal struct Interval
	{
		internal static bool OverlapOnAxis(Rectangle _a, Rectangle _b, Vector2 _axis)
		{
			Interval? a = Get(_a, _axis);
			Interval? b = Get(_b, _axis);

			if(!a.HasValue || !b.HasValue)
				return false;

			return b.Value.min <= a.Value.max && a.Value.min <= b.Value.max;
		}
		
		internal static bool OverlapOnAxis(Rectangle _a, OrientedRectangle _b, Vector2 _axis)
		{
			Interval? a = Get(_a, _axis);
			Interval? b = Get(_b, _axis);

			if(!a.HasValue || !b.HasValue)
				return false;

			return b.Value.min <= a.Value.max && a.Value.min <= b.Value.max;
		}
		
		internal static Interval? Get(Rectangle _rect, Vector2 _axis)
		{
			Interval result = new();

			Vector2 min = _rect.Min;
			Vector2 max = _rect.Max;

			Vector2[] verts =
			{
				new(min.x, min.y), new(min.x, max.y),
				new(max.x, max.y), new(max.x, max.y)
			};

			result.min = result.max = Vector2.Dot(_axis, verts[0]);

			for(int i = 1; i < verts.Length; i++)
			{
				float projection = Vector2.Dot(_axis, verts[i]);

				result.min = Leviamath.Min(projection, result.min);
				result.max = Leviamath.Max(projection, result.max);
			}
			
			return result;
		}
		
		internal static Interval? Get(OrientedRectangle _box, Vector2 _axis)
		{
			Rectangle rect = new(_box.center - _box.halfExtents, _box.halfExtents * 2.0f);

			Vector2 min = rect.Min;
			Vector2 max = rect.Max;

			Vector2[] verts =
			{
				min, max,
				new(min.x, max.y), new(max.x, min.y)
			};

			Matrix2x2 rotationMat = Matrix2x2.FromAngle(_box.ThetaRotation);

			for(int i = 0; i < verts.Length; i++)
			{
				Vector2 rotVector = verts[i] - _box.center;
				
				if(!MatrixMath.Multiply(out float[]? output, rotVector, 1, 2, rotationMat, 2, 2))
					return null;

				rotVector = output!;
				verts[i] = rotVector + _box.center;
			}

			Interval result;

			result.min = result.max = Vector2.Dot(_axis, verts[0]);

			for(int i = 1; i < verts.Length; i++)
			{
				float proj = Vector2.Dot(_axis, verts[i]);

				result.min = proj < result.min ? proj : result.min;
				result.max = proj > result.max ? proj : result.max;
			}
			
			return result;
		}
		
		internal float min;
		internal float max;
	}
}