using Leviathan.Mathematics;
using Leviathan.Physics.Components;
using Leviathan.Structures.Trees.Quad;

namespace Leviathan.Physics
{
	public class PhysicsTreeData : QuadTreeData<Collider>
	{
		public PhysicsTreeData(Collider _value, Rectangle _bounds) : base(_value, _bounds) { }
	}
}