using Leviathan.Debugging;
using Leviathan.Mathematics;
using Leviathan.Physics.Shapes;

namespace Leviathan.Physics.Components
{
	public class BoxCollider2D : Collider
	{
		protected OrientedRectangle? Box => Shape as OrientedRectangle?;
		protected override IShape? Shape { get; set; }

		public override void Start(params object[] _data)
		{
			if(GameObject is { Transform: { } })
				Shape = new OrientedRectangle(GameObject.Transform.Position, GameObject.Transform.Scale * 0.5f, GameObject.Transform.Rotation);
		}

		public override void Tick()
		{
			if(GameObject is { Transform: { } } && Box is { })
			{
				OrientedRectangle box = Box.Value;

				box.center = GameObject.Transform.Position;
				box.halfExtents = GameObject.Transform.Scale * 0.5f;
				box.rotation = GameObject.Transform.Rotation;

				Shape = box;
			}
		}

		public override void OnRenderGizmos()
		{
			if(Box.HasValue)
				Gizmos.DrawWireRectangle(new Rectangle(Box.Value.center, Box.Value.halfExtents * 2.0f), Color.Green, Box.Value.rotation);
		}
	}
}