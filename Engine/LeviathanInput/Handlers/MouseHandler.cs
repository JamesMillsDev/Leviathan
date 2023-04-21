using Leviathan.Mathematics;

using SharpDX.DirectInput;

namespace Leviathan.InputSystem.Handlers
{
	public class MouseHandler : IInputHandler
	{
		public HandlerType Type => HandlerType.Mouse;

		private readonly Mouse mouse;

		public MouseHandler(DirectInput _input)
		{
			mouse = new Mouse(_input);
			mouse.Acquire();
		}
		
		public void Poll()
		{
			mouse.Poll();
		}

		public bool IsButtonPressed(int _id) => mouse.GetCurrentState().Buttons[_id];

		public Vector2 GetAxis(MouseAxis _axis) => _axis switch
		{
			MouseAxis.None => Vector2.Zero,
			MouseAxis.X => new Vector2(mouse.GetCurrentState().X / int.MaxValue, 0),
			MouseAxis.Y => new Vector2(0, mouse.GetCurrentState().Y / int.MaxValue),
			MouseAxis.Scroll => new Vector2(0, mouse.GetCurrentState().Z / int.MaxValue),
			_ => throw new ArgumentOutOfRangeException(nameof(_axis), _axis, null)
		};
	}
}