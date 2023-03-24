using Leviathan.GameObjects;
using Leviathan.Physics.Shapes;

namespace Leviathan.Physics
{
	public abstract class Collider : Component
	{
		internal PhysicsTreeData? data;

		protected IShape? shape;

		protected Collider(IShape _shape) => shape = _shape;
	}
}