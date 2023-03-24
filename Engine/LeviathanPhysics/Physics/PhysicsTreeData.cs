using Leviathan.Physics.Shapes;
using Leviathan.Structures.Trees.Quad;

namespace Leviathan.Physics
{
	public class PhysicsTreeData : QuadTreeData<Collider, Rectangle>
	{
		public PhysicsTreeData(Collider _value, Rectangle _bounds) : base(_value, _bounds) { }
	}
}