using Leviathan;
using Leviathan.GameObjects;

using Raylib_CsLo;

namespace TestApp.Source.GameObjects.Components
{
	public class MovementComponent : Component
	{
		private float speed;

		public override void Start(params object[] _data)
		{
			speed = (float) _data[0];
		}

		public override void Tick()
		{
			if(GameObject is { Transform: { } })
			{
				float dir = 0f;
				if(Raylib.IsKeyDown(KeyboardKey.KEY_W))
				{
					dir = 1f;
				}
				else if(Raylib.IsKeyDown(KeyboardKey.KEY_S))
				{
					dir = -1f;
				}

				GameObject.Transform.Position += GameObject.Transform.Forward * Time.deltaTime * speed * dir;
			}
		}
	}
}