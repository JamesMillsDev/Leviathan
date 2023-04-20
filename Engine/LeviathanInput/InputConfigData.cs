using Leviathan.Configuration;

namespace Leviathan.InputSystem
{
	public class InputConfigData : IConfigData
	{
		public Dictionary<string, object> handlers;
		public Dictionary<string, object> keyboard;
		public Dictionary<string, object> mouse;
		public Dictionary<string, object> gamepad;

		public InputConfigData()
		{
			handlers = new Dictionary<string, object>();
			keyboard = new Dictionary<string, object>();
			mouse = new Dictionary<string, object>();
			gamepad = new Dictionary<string, object>();
		}

		public ConfigData[] GetConfigData() => new[]
		{
			new ConfigData(handlers, "handlers"),
			new ConfigData(keyboard, "keyboard"),
			new ConfigData(mouse, "mouse"),
			new ConfigData(gamepad, "gamepad")
		};
	}
}