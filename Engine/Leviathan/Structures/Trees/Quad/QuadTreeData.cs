using Raylib_cs;

namespace Leviathan.Structures.Trees.Quad
{
	public class QuadTreeData<VALUE, BOUNDS> : TreeData<VALUE>
	{
		public BOUNDS bounds;

		public QuadTreeData(VALUE _value, BOUNDS _bounds) : base(_value)
		{
			bounds = _bounds;
		}
	}
}