using Leviathan.Debugging;
using Leviathan.Mathematics;
using Leviathan.Physics.Shapes;

namespace Leviathan.Physics.Components
{
	public class CircleCollider : Collider
	{
		protected Circle? Circle => Shape as Circle?;
		protected override IShape? Shape { get; set; }

		public override void Start(params object[] _data)
		{
			if(GameObject is { Transform: { } })
				Shape = new Circle(GameObject.Transform.Position, GameObject.Transform.Scale.Magnitude * 0.5f);
		}

		public override void Tick()
		{
			if(GameObject is { Transform: { } } && Circle is { })
			{
				Circle c = Circle.Value;

				c.center = GameObject.Transform.Position;
				c.radius = GameObject.Transform.Scale.Magnitude * 0.5f;

				Shape = c;
			}
		}

		public override void OnRenderGizmos()
		{
			if(Circle.HasValue)
				Gizmos.DrawWireCircle(Circle.Value.center, Circle.Value.radius, Color.Green);
		}
	}
}