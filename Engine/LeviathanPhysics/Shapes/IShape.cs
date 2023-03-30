namespace Leviathan.Physics.Shapes
{
	public interface IShape
	{
		public bool Intersects<SHAPE>(SHAPE _other) where SHAPE : IShape;
	}
}