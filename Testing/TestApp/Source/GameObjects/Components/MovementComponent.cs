using Leviathan;
using Leviathan.GameObjects;
using Leviathan.Input;
using Leviathan.Mathematics;

namespace TestApp.GameObjects.Components
{
	public class MovementComponent : Component
	{
		private float speed;

		private float? movement = 0;

		public override void Start(params object[] _data)
		{
			speed = (float) _data[0];

			InputAction? action = InputSystem.Find("movement");
			if(action != null)
			{
				action.onPerformed += OnMovementPerformed;
				action.onCancelled += OnMovementCancelled;
			}
		}

		public override void Tick()
		{
			if(GameObject is { Transform: { } })
			{
				if(movement is null or 0)
					return;

				GameObject.Transform.Position += GameObject.Transform.Forward * Time.deltaTime * speed * movement.Value;
			}
		}

		private void OnMovementPerformed(InputAction? _action)
		{
			movement = _action?.ReadValue<Vec2>().y;
		}

		private void OnMovementCancelled(InputAction? _action)
		{
			movement = 0;
		}
	}
}