using Leviathan.Mathematics;

using Newtonsoft.Json;

namespace Leviathan.Input
{
	[JsonObject(MemberSerialization.OptIn)]
	public class InputAction
	{
		public enum ActionType
		{
			Button,
			Axis
		}
		
		[JsonProperty] public List<InputMapping> mappings = new();
		[JsonProperty] public ActionType Type { get; set; } = ActionType.Button;

		public Action<InputAction>? onPerformed;
		public Action<InputAction>? onCancelled;

		private bool buttonValue;
		private Vec2 axisValue;

		public VALUE ReadValue<VALUE>()
		{
			return Type switch
			{
				ActionType.Button => (VALUE) Convert.ChangeType(buttonValue, typeof(VALUE)),
				ActionType.Axis => (VALUE) Convert.ChangeType(axisValue, typeof(VALUE)),
				_ => throw new InvalidCastException($"{typeof(VALUE)} is not a valid action type! Valid types are: Vec2, bool")
			};
		}

		internal void Tick()
		{
			bool changeOccured = mappings.Any(_mapping => _mapping.Tick(0));

			switch(Type)
			{
				case ActionType.Button:
					HandleButton(changeOccured);
					break;
				case ActionType.Axis:
					HandleAxis(changeOccured);
					break;
				default:
					throw new ArgumentOutOfRangeException();
			}
		}

		private void HandleButton(bool _changeOccured)
		{
			buttonValue = false;
			
			foreach(InputMapping mapping in mappings)
				buttonValue |= mapping.GetButtonValue();

			if(_changeOccured)
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

		private void HandleAxis(bool _changeOccured)
		{
			axisValue = Vec2.zero;
			
			foreach(InputMapping mapping in mappings)
				axisValue += mapping.GetAxisValue();
			
			axisValue.Normalise();

			if(_changeOccured)
			{
				if(axisValue != Vec2.zero)
				{
					onPerformed?.Invoke(this);
				}
				else
				{
					onCancelled?.Invoke(this);
				}
			}
		}
	}
}