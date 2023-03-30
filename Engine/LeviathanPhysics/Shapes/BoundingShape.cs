using Leviathan.Mathematics;

namespace Leviathan.Physics.Shapes
{
	public class BoundingShape
	{
		public IEnumerable<Circle> Circles => circles;
		public int CircleCount => circles.Count;
		
		public IEnumerable<OrientedRectangle> Rectangles => rectangles;
		public int RectangleCount => rectangles.Count;

		private readonly List<Circle> circles = new();
		private readonly List<OrientedRectangle> rectangles = new();

		public void Add(OrientedRectangle _rectangle) => rectangles.Add(_rectangle);
		public void Add(Circle _circle) => circles.Add(_circle);

		public bool Contains(Vector2 _point)
		{
			for(int i = 0; i < circles.Count; i++)
			{
				if(circles[i].Contains(_point))
					return true;
			}
			
			for(int i = 0; i < rectangles.Count; i++)
			{
				if(rectangles[i].Contains(_point))
					return true;
			}

			return false;
		}
	}
}