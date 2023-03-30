using Leviathan.Mathematics;

using Newtonsoft.Json;

using Raylib_cs;

namespace Leviathan.Input
{
	[JsonObject]
	public class InputMapping
	{
		public enum MappingType
		{
			None = -1,
			GamepadAxis,
			GamepadButton,
			MouseButton,
			MouseAxis,
			KeyboardKey,
			KeyboardKeyAxis
		}
		
		[JsonObject]
		public struct KeyboardAxisMask
		{
			public KeyCode forward;
			public KeyCode back;
			public KeyCode right;
			public KeyCode left;
		}

		[JsonProperty] public MappingType Type { get; set; } = MappingType.KeyboardKey;
		[JsonProperty] public GamepadAxis GamepadAxis { get; set; } = GamepadAxis.None;
		[JsonProperty] public GamepadButton GamepadButton { get; set; } = GamepadButton.None;
		[JsonProperty] public KeyCode Key { get; set; } = KeyCode.None;
		[JsonProperty] public KeyboardAxisMask Keys { get; set; }
		[JsonProperty] public MouseButton MouseButton { get; set; } = MouseButton.None;
		[JsonProperty] public MouseAxis MouseAxis { get; set; } = MouseAxis.None;

		private Vector2 gamepadAxisValue;
		private Vector2 keyAxisValue;
		private bool gamepadButtonValue;
		private bool keyboardKeyValue;
		private bool mouseButtonValue;
		private Vector2 mouseAxisValue;

		internal Vector2 GetAxisValue() => Type switch
		{
			MappingType.GamepadAxis => gamepadAxisValue,
			MappingType.MouseAxis => mouseAxisValue,
			MappingType.KeyboardKeyAxis => keyAxisValue,
			_ => throw new ArgumentOutOfRangeException()
		};

		internal bool GetButtonValue() => Type switch
		{
			MappingType.GamepadButton => gamepadButtonValue,
			MappingType.KeyboardKey => keyboardKeyValue,
			MappingType.MouseButton => mouseButtonValue,
			_ => throw new ArgumentOutOfRangeException()
		};

		internal bool Tick(int _gamepadId)
		{
			switch(Type)
			{
				case MappingType.GamepadAxis:
					Vector2 oldGamepadAxisVal = gamepadAxisValue;
					
					TickGamepadAxis(_gamepadId);

					return oldGamepadAxisVal != gamepadAxisValue;
				
				case MappingType.GamepadButton:
					bool oldGamepadButtonVal = gamepadButtonValue;
					
					TickGamepadButton(_gamepadId);

					return oldGamepadButtonVal != gamepadButtonValue;
				
				case MappingType.MouseButton:
					bool oldMouseButtonVal = mouseButtonValue;
					
					TickMouseButton();

					return oldMouseButtonVal != mouseButtonValue;
				
				case MappingType.MouseAxis:
					Vector2 oldMouseAxisVal = mouseAxisValue;
					
					TickMouseAxis();

					return oldMouseAxisVal != mouseAxisValue;
				
				case MappingType.KeyboardKey:
					bool oldKeyVal = keyboardKeyValue;
					
					TickKeyboard();

					return oldKeyVal != keyboardKeyValue;
				
				case MappingType.KeyboardKeyAxis:
					Vector2 oldKeyAxisVal = keyAxisValue;
					
					TickKeyboardKeyAxis();

					return oldKeyAxisVal != keyAxisValue;
			}

			return false;
		}

		private void TickGamepadAxis(int _gamepadId) => gamepadAxisValue = GamepadAxis switch
		{
			GamepadAxis.RightStick => new Vector2(Raylib.GetGamepadAxisMovement(_gamepadId, Raylib_cs.GamepadAxis.GAMEPAD_AXIS_RIGHT_X), Raylib.GetGamepadAxisMovement(_gamepadId, Raylib_cs.GamepadAxis.GAMEPAD_AXIS_RIGHT_Y)),
			GamepadAxis.LeftStick => new Vector2(Raylib.GetGamepadAxisMovement(_gamepadId, Raylib_cs.GamepadAxis.GAMEPAD_AXIS_LEFT_X), Raylib.GetGamepadAxisMovement(_gamepadId, Raylib_cs.GamepadAxis.GAMEPAD_AXIS_LEFT_Y)),
			GamepadAxis.RightTrigger => new Vector2(0, Raylib.GetGamepadAxisMovement(_gamepadId, Raylib_cs.GamepadAxis.GAMEPAD_AXIS_RIGHT_TRIGGER)),
			GamepadAxis.LeftTrigger => new Vector2(0, Raylib.GetGamepadAxisMovement(_gamepadId, Raylib_cs.GamepadAxis.GAMEPAD_AXIS_LEFT_TRIGGER)),
			_ => gamepadAxisValue
		};

		private void TickGamepadButton(int _gamepadId) => gamepadButtonValue = GamepadButton switch
		{
			GamepadButton.North => Raylib.IsGamepadButtonPressed(_gamepadId, Raylib_cs.GamepadButton.GAMEPAD_BUTTON_RIGHT_FACE_UP),
			GamepadButton.East => Raylib.IsGamepadButtonPressed(_gamepadId, Raylib_cs.GamepadButton.GAMEPAD_BUTTON_RIGHT_FACE_RIGHT),
			GamepadButton.South => Raylib.IsGamepadButtonPressed(_gamepadId, Raylib_cs.GamepadButton.GAMEPAD_BUTTON_RIGHT_FACE_DOWN),
			GamepadButton.West => Raylib.IsGamepadButtonPressed(_gamepadId, Raylib_cs.GamepadButton.GAMEPAD_BUTTON_RIGHT_FACE_LEFT),
			GamepadButton.DPadUp => Raylib.IsGamepadButtonPressed(_gamepadId, Raylib_cs.GamepadButton.GAMEPAD_BUTTON_LEFT_FACE_UP),
			GamepadButton.DPadRight => Raylib.IsGamepadButtonPressed(_gamepadId, Raylib_cs.GamepadButton.GAMEPAD_BUTTON_LEFT_FACE_RIGHT),
			GamepadButton.DPadDown => Raylib.IsGamepadButtonPressed(_gamepadId, Raylib_cs.GamepadButton.GAMEPAD_BUTTON_LEFT_FACE_DOWN),
			GamepadButton.DPadLeft => Raylib.IsGamepadButtonPressed(_gamepadId, Raylib_cs.GamepadButton.GAMEPAD_BUTTON_LEFT_FACE_LEFT),
			GamepadButton.RightStick => Raylib.IsGamepadButtonPressed(_gamepadId, Raylib_cs.GamepadButton.GAMEPAD_BUTTON_RIGHT_THUMB),
			GamepadButton.LeftStick => Raylib.IsGamepadButtonPressed(_gamepadId, Raylib_cs.GamepadButton.GAMEPAD_BUTTON_LEFT_THUMB),
			GamepadButton.RightBumper => Raylib.IsGamepadButtonPressed(_gamepadId, Raylib_cs.GamepadButton.GAMEPAD_BUTTON_RIGHT_TRIGGER_1),
			GamepadButton.LeftBumper => Raylib.IsGamepadButtonPressed(_gamepadId, Raylib_cs.GamepadButton.GAMEPAD_BUTTON_LEFT_TRIGGER_1),
			GamepadButton.RightTrigger => Raylib.IsGamepadButtonPressed(_gamepadId, Raylib_cs.GamepadButton.GAMEPAD_BUTTON_RIGHT_TRIGGER_2),
			GamepadButton.LeftTrigger => Raylib.IsGamepadButtonPressed(_gamepadId, Raylib_cs.GamepadButton.GAMEPAD_BUTTON_LEFT_TRIGGER_2),
			GamepadButton.Select => Raylib.IsGamepadButtonPressed(_gamepadId, Raylib_cs.GamepadButton.GAMEPAD_BUTTON_MIDDLE_LEFT),
			GamepadButton.Pause => Raylib.IsGamepadButtonPressed(_gamepadId, Raylib_cs.GamepadButton.GAMEPAD_BUTTON_MIDDLE_RIGHT),
			GamepadButton.Center => Raylib.IsGamepadButtonPressed(_gamepadId, Raylib_cs.GamepadButton.GAMEPAD_BUTTON_MIDDLE),
			_ => gamepadButtonValue
		};

		private void TickKeyboard() => keyboardKeyValue = Raylib.IsKeyDown((KeyboardKey) Key);

		private void TickKeyboardKeyAxis()
		{
			keyAxisValue = new Vector2
			{
				x = Raylib.IsKeyDown((KeyboardKey) Keys.right) ? 1 : Raylib.IsKeyDown((KeyboardKey) Keys.left) ? -1 : 0,
				y = Raylib.IsKeyDown((KeyboardKey) Keys.forward) ? 1 : Raylib.IsKeyDown((KeyboardKey) Keys.back) ? -1 : 0
			};
		}

		private void TickMouseButton() => mouseButtonValue = Raylib.IsMouseButtonDown((Raylib_cs.MouseButton) MouseButton);

		private void TickMouseAxis() => mouseAxisValue = MouseAxis switch
		{
			MouseAxis.X => new Vector2(Raylib.GetMouseDelta().X, 0),
			MouseAxis.Y => new Vector2(0, Raylib.GetMouseDelta().Y),
			MouseAxis.Scroll => new Vector2(0, Raylib.GetMouseWheelMove()),
			_ => mouseAxisValue
		};
	}
}