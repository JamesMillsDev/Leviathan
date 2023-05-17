using Leviathan.Configuration;
using Leviathan.InputSystem.Handlers;

using Newtonsoft.Json;

using SharpDX.DirectInput;

namespace Leviathan.InputSystem
{
	public static class Input
	{
		private static readonly Dictionary<string, Type> moduleIDs = new()
		{
			{ "keyboard", typeof(KeyboardHandler) }
		};

		private static Dictionary<string, InputAction?> actions = new();
		private static readonly List<IInputHandler?> handlers = new();
		private static readonly DirectInput directInput = new();

		public static InputAction? Find(string _id) => actions.TryGetValue(_id, out InputAction? action) ? action : null;

		internal static HANDLER? FindHandler<HANDLER>() where HANDLER : IInputHandler => (HANDLER?) handlers.FirstOrDefault(_handler => _handler?.GetType() == typeof(HANDLER));
		
		internal static void Load(Config<InputConfigData> _config)
		{
			foreach(KeyValuePair<string, Type> id in moduleIDs.Where(_id => _config.GetValue<bool>($"handlers.{_id.Key}")))
				handlers.Add(Activator.CreateInstance(id.Value, directInput) as IInputHandler);
			
			string path = $"{Directory.GetCurrentDirectory()}\\assets\\InputActions.json";
			string json = File.ReadAllText(path);
			
			actions = JsonConvert.DeserializeObject<Dictionary<string, InputAction>>(json)!;
		}

		internal static void Poll()
		{
			foreach(IInputHandler? handler in handlers)
				handler?.Poll();

			foreach(InputAction? action in actions.Values)
				action?.Poll();
		}
	}
}