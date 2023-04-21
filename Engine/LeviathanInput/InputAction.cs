using Leviathan.InputSystem.Handlers;
using Leviathan.Mathematics;

using Newtonsoft.Json;

namespace Leviathan.InputSystem
{
	[JsonObject(MemberSerialization.OptIn)]
	public class InputAction
	{
		public enum ActionType
		{
			Button,
			Axis
		}

		public Action<InputAction>? onPerformed;
		public Action<InputAction>? onCancelled;

		[JsonProperty] public List<InputMapping> mappings = new();
		[JsonProperty] public ActionType Type { get; set; } = ActionType.Button;
		[JsonProperty] public HandlerType ActiveHandlerType { get; set; } = HandlerType.Keyboard;

		private bool buttonValue;
		private Vector2 axisValue;

		private IInputHandler? currentHandler;

		public VALUE ReadValue<VALUE>()
		{
			return Type switch
			{
				ActionType.Button => (VALUE) Convert.ChangeType(buttonValue, typeof(VALUE)),
				ActionType.Axis => (VALUE) Convert.ChangeType(axisValue, typeof(VALUE)),
				_ => throw new InvalidCastException($"{typeof(VALUE)} is not a valid action type! Valid types are: Vec2, bool")
			};
		}

		internal void Poll()
		{
			PollHandler();
			PollValues();
		}

		private void PollHandler()
		{
			currentHandler = ActiveHandlerType switch
			{
				HandlerType.None => null,
				HandlerType.Keyboard => Input.FindHandler<KeyboardHandler>(),
				HandlerType.Mouse => Input.FindHandler<MouseHandler>(),
				HandlerType.Gamepad => Input.FindHandler<GamepadHandler>(),
				_ => throw new ArgumentOutOfRangeException()
			};
		}

		private void PollValues()
		{
			switch(Type)
			{
				case ActionType.Button:
					HandleButton();
					break;

				case ActionType.Axis:
					HandleAxis();
					break;

				default:
					throw new ArgumentOutOfRangeException();
			}
		}

	#region Value Handling Functions

		private void HandleButton()
		{
			bool oldValue = buttonValue;
			buttonValue = false;

			foreach(InputMapping mapping in mappings)
			{
				switch(mapping.Type)
				{
					case InputMapping.MappingType.GamepadButton:
						if(currentHandler is GamepadHandler gamepad)
							buttonValue |= gamepad.IsButtonPressed(mapping.GamepadButton);
						
						break;

					case InputMapping.MappingType.MouseButton:
						if(currentHandler is MouseHandler mouse)
							buttonValue |= mouse.IsButtonPressed(mapping.MouseButton);
						break;

					case InputMapping.MappingType.KeyboardKey:
						if(currentHandler is KeyboardHandler keyboard)
							buttonValue |= keyboard.IsPressed(mapping.KeyCode);
						break;
				}
			}

			if(buttonValue != oldValue)
			{
				if(buttonValue)
				{
					onPerformed?.Invoke(this);
				}
				else
				{
					onCancelled?.Invoke(this);
				}
			}
		}
		
		private void HandleAxis()
		{
			Vector2 oldValue = axisValue;
			axisValue = Vector2.Zero;

			foreach(InputMapping mapping in mappings)
			{
				switch(mapping.Type)
				{
					case InputMapping.MappingType.GamepadAxis:
						if(currentHandler is GamepadHandler gamepad)
							axisValue += gamepad.GetAxis(mapping.GamepadAxis);
						
						break;

					case InputMapping.MappingType.MouseAxis:
						if(currentHandler is MouseHandler mouse)
							axisValue += mouse.GetAxis(mapping.MouseAxis);
						break;

					case InputMapping.MappingType.KeyboardKeyAxis:
						if(currentHandler is KeyboardHandler keyboard && mapping.Keys != null)
						{
							axisValue += new Vector2()
							{
								x = keyboard.IsPressed(mapping.Keys.Value.right) ? 1 : keyboard.IsPressed(mapping.Keys.Value.left) ? -1 : 0,
								y = keyboard.IsPressed(mapping.Keys.Value.forward) ? 1 : keyboard.IsPressed(mapping.Keys.Value.back) ? -1 : 0,
							};
						}
						break;
				}
			}
			
			axisValue.Normalise();

			if(axisValue != oldValue)
			{
				if(axisValue != Vector2.Zero)
				{
					onPerformed?.Invoke(this);
				}
				else
				{
					onCancelled?.Invoke(this);
				}
			}
		}

	#endregion
	}
}