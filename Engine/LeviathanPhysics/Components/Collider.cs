using Leviathan.GameObjects;
using Leviathan.Physics.Shapes;

namespace Leviathan.Physics.Components
{
	public abstract class Collider : Component
	{
		public Rectangle Bounds => Shape!.Bounds;
		
		protected abstract IShape? Shape { get; set; }
		
		public bool isTrigger = false;
		
		internal PhysicsTreeData? data;
		internal List<Collider> collisions = new();

		internal bool CheckCollision(Collider _other)
		{
			if(Shape is { } && _other.Shape is { })
			{
				return Shape.Intersects(_other.Shape);
			}

			return false;
		}
	}
}