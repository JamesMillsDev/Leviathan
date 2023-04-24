using Leviathan.Mathematics;

using Raylib_CsLo;

namespace Leviathan.Physics.Components
{
	public unsafe class BoxCollider : Collider
	{
		private PhysicsBodyData* body;

		public override void Start(params object[] _data)
		{
			if(GameObject is { Transform: { } })
			{
				float width = GameObject.Transform.Scale.x;
				float height = GameObject.Transform.Scale.y;
				float density = (float) _data[0];

				body = Physac.CreatePhysicsBodyRectangle(GameObject.Transform.Position, width, height, density);
				body->useGravity = false;
			}
		}

		public override void Tick()
		{
			if(body != null && GameObject is { Transform: { } })
			{
				if(body->enabled)
				{
					GameObject.Transform.Position = body->position;
					GameObject.Transform.SetRotation(body->orient);
				}
				else
				{
					body->position = GameObject.Transform.Position;
					Physac.SetPhysicsBodyRotation(body, GameObject.Transform.Rotation * Leviamath.DEG_2_RAD);
					
				}
			}
		}
	}
}