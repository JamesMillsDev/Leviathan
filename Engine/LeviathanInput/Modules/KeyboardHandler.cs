using SharpDX.DirectInput;

namespace Leviathan.InputSystem.Handlers
{
	public class KeyboardHandler : IInputHandler
	{
		private readonly Keyboard keyboard;

		private readonly List<Key> pressed = new();
		private readonly List<Key> released = new();

		public KeyboardHandler(DirectInput _input)
		{
			keyboard = new Keyboard(_input);
			keyboard.Acquire();
		}

		public bool IsPressed(Key _key) => pressed.Contains(_key);
		public bool IsReleased(Key _key) => released.Contains(_key);
		
		public void Poll()
		{
			keyboard.Poll();

			List<Key> lastPressed = new(pressed);

			released.Clear();
			pressed.Clear();

			foreach(Key key in keyboard.GetCurrentState().PressedKeys)
				pressed.Add(key);

			foreach(Key key in lastPressed.Where(_key => !pressed.Contains(_key)))
				released.Add(key);
		}
	}
}