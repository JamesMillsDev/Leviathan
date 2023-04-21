using Leviathan.InputSystem.Handlers;

using Newtonsoft.Json;

using SharpDX.DirectInput;
using SharpDX.XInput;

namespace Leviathan.InputSystem
{
	[JsonObject]
	public struct InputMapping
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
		public struct KeyAxisMask
		{
			public Key forward;
			public Key back;
			public Key right;
			public Key left;
		}

		public MappingType Type { get; set; } = MappingType.KeyboardKey;
		public GamepadAxis GamepadAxis { get; set; } = GamepadAxis.None;
		public GamepadButtonFlags GamepadButton { get; set; } = GamepadButtonFlags.None;
		public Key KeyCode { get; set; } = Key.Unknown;
		public KeyAxisMask? Keys { get; set; } = null;
		public int MouseButton { get; set; } = 0;
		public MouseAxis MouseAxis { get; set; } = MouseAxis.None;
		
		public InputMapping() { }
	}
}