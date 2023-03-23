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
	}
}