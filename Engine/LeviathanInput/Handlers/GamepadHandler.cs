using Leviathan.Mathematics;

using SharpDX.XInput;

namespace Leviathan.InputSystem.Handlers
{
	public class GamepadHandler : IInputHandler
	{
		public HandlerType Type => HandlerType.Gamepad;

		private readonly Controller controller;
		private GamepadButtonFlags buttonFlags;

		private Vector2 leftThumbstickAxis;
		private Vector2 rightThumbstickAxis;

		private float leftTriggerAxis;
		private float rightTriggerAxis;

		public GamepadHandler() => controller = new Controller();

		public void Poll()
		{
			Gamepad gamepad = controller.GetState().Gamepad;
			buttonFlags = gamepad.Buttons;

			leftThumbstickAxis = new Vector2(gamepad.LeftThumbX / short.MaxValue, gamepad.LeftThumbY / short.MaxValue);
			rightThumbstickAxis = new Vector2(gamepad.RightThumbX / short.MaxValue, gamepad.RightThumbY / short.MaxValue);
			leftTriggerAxis = gamepad.LeftTrigger / byte.MaxValue;
			rightTriggerAxis = gamepad.LeftTrigger / byte.MaxValue;
		}

		public bool IsButtonPressed(GamepadButtonFlags _button) => (buttonFlags & _button) == _button;

		public Vector2 GetAxis(GamepadAxis _axis) => _axis switch
		{
			GamepadAxis.None => Vector2.Zero,
			GamepadAxis.LeftStick => leftThumbstickAxis,
			GamepadAxis.RightStick => rightThumbstickAxis,
			GamepadAxis.RightTrigger => new Vector2(0, rightTriggerAxis),
			GamepadAxis.LeftTrigger => new Vector2(0, leftTriggerAxis),
			_ => throw new ArgumentOutOfRangeException(nameof(_axis), _axis, null)
		};
	}
}