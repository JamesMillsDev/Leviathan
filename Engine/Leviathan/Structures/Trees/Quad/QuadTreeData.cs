using Leviathan.Mathematics;

namespace Leviathan.Structures.Trees.Quad
{
	public class QuadTreeData<VALUE> : TreeData<VALUE>
	{
		public Rectangle bounds;

		public QuadTreeData(VALUE _value, Rectangle _bounds) : base(_value)
		{
			bounds = _bounds;
		}
	}
}