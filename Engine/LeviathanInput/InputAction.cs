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

		private bool buttonValue;
		private Vector2 axisValue;

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
			
		}
	}
}