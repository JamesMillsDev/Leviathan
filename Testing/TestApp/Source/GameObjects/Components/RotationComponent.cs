using Leviathan;
using Leviathan.GameObjects;
using Leviathan.InputSystem;
using Leviathan.Mathematics;

namespace TestApp.GameObjects.Components
{
	public class RotationComponent : Component
	{
		private float speed;
		private InputAction rotateAction;

		public override void Start(params object[] _data)
		{
			speed = (float) _data[0];
			rotateAction = Input.Find((string) _data[1])!;
		}

		public override void Tick()
		{
			if(GameObject is { Transform: { } })
			{
				float dir = rotateAction.ReadValue<Vector2>().x;

				GameObject.Transform.Rotate(speed * dir * Time.deltaTime);
			}
		}
	}
}