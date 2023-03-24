using Leviathan.GameObjects;
using Leviathan.Physics.Shapes;

namespace Leviathan.Physics.Components
{
	public abstract class Collider : Component
	{
		internal PhysicsTreeData? data;

		protected abstract IShape? Shape { get; set; }
	}
}