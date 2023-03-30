using Leviathan.GameObjects.Components;
using Leviathan.Mathematics;
using Leviathan.Physics.Shapes;

namespace Leviathan.Physics
{
	internal static class PhysicsUtils
	{
		internal static OrientedRectangle ContainingRect(Vector2[] _points, Transform _transform)
		{
			if(_points.Length == 0)
				return default;

			List<Vector2> points = new();
			foreach(Vector2 point in _points)
				points.Add(_transform.TransformVector(point));

			Vector2 min = points[0];
			Vector2 max = points[0];

			for(int i = 1; i < points.Count; i++)
			{
				min.x = points[i].x < min.x ? points[i].x : min.x;
				min.y = points[i].y < min.y ? points[i].y : min.y;
				
				max.x = points[i].x > max.x ? points[i].x : max.x;
				max.y = points[i].y > max.y ? points[i].y : max.y;
			}

			Rectangle local = Rectangle.FromMinMax(min, max);
			return new OrientedRectangle(local.center, local.size * .5f, _transform.Rotation);
		}

		internal static Circle ContainingCircle(Vector2[] _points)
		{
			if(_points.Length == 0)
				return default;
			
			Vector2 center = Vector2.Zero;

			foreach(Vector2 point in _points)
				center += point;

			center *= 1f / _points.Length;

			Circle result = new(center, 1f)
			{
				radius = (center - _points[0]).Magnitude
			};

			for(int i = 1; i < _points.Length; i++)
			{
				float distance = (center - _points[i]).Magnitude;
				if(distance > result.radius)
					result.radius = distance;
			}

			result.radius = LMath.Sqrt(result.radius);

			return result;
		}
	}
}