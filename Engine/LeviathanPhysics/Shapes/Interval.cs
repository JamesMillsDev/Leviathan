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

				result.min = LMath.Min(projection, result.min);
				result.max = LMath.Max(projection, result.max);
			}
			
			return result;
		}
		
		internal static Interval? Get(OrientedRectangle _box, Vector2 _axis)
		{
			Interval result = new();

			Rectangle rect = new(_box.Center - _box.HalfExtents, _box.HalfExtents * 2);

			Vector2 min = rect.Min;
			Vector2 max = rect.Max;
			
			Vector2[] verts =
			{
				min, max,
				new(min.x, max.y), new(max.x, min.y)
			};
			
			Matrix3x3 rotMat = Matrix3x3.CreateZRotation(-_box.Rotation);
			
			for(int i = 0; i < verts.Length; i++)
				verts[i] = (verts[i] - rect.center) * rotMat + (Vector3) rect.center;

			result.min = result.max = Vector2.Dot(_axis, verts[0]);

			for(int i = 1; i < verts.Length; i++)
			{
				float projection = Vector2.Dot(_axis, verts[i]);

				result.min = LMath.Min(projection, result.min);
				result.max = LMath.Max(projection, result.max);
			}
			
			return result;
		}
		
		internal float min;
		internal float max;
	}
}