namespace Leviathan.Physics.Shapes
{
	public interface IShape
	{
		public Rectangle Bounds { get; }
		
		public bool Intersects<SHAPE>(SHAPE _other) where SHAPE : IShape;
	}
}