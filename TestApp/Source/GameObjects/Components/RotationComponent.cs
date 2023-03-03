using Leviathan;
using Leviathan.GameObjects;

using Raylib_CsLo;

namespace TestApp.Source.GameObjects.Components
{
	public class RotationComponent : Component
	{
		private float speed;
		private KeyboardKey left;
		private KeyboardKey right;
		
		public override void Start(params object[] _data)
		{
			speed = (float) _data[0];
			left = (KeyboardKey) _data[1];
			right = (KeyboardKey) _data[2];
		}

		public override void Tick()
		{
			if(GameObject is { Transform: { } })
			{
				float dir = 0f;
				if(Raylib.IsKeyDown(left))
				{
					dir = -1f;
				}
				else if(Raylib.IsKeyDown(right))
				{
					dir = 1f;
				}

				GameObject.Transform.Rotate(speed * dir * Time.deltaTime);
			}
		}
	}
}