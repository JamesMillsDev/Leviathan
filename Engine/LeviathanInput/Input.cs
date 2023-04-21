using Leviathan.Configuration;
using Leviathan.Events;
using Leviathan.InputSystem.Handlers;

using Newtonsoft.Json;

using SharpDX.DirectInput;

namespace Leviathan.InputSystem
{
	public class Input : Singleton<Input>, IEventHandler
	{
		private static string Path => $"{Directory.GetCurrentDirectory()}\\assets\\InputActions.json";
		private static readonly Dictionary<HandlerType, Type> moduleIDs = new()
		{
			{ HandlerType.Keyboard, typeof(KeyboardHandler) },
			{ HandlerType.Mouse, typeof(MouseHandler) },
			{ HandlerType.Gamepad, typeof(GamepadHandler) },
		};

		private static Dictionary<string, InputAction?> actions = new();
		private static readonly List<IInputHandler?> handlers = new();
		private static readonly DirectInput directInput = new();
		

		public static InputAction? Find(string _id) => actions.TryGetValue(_id, out InputAction? action) ? action : null;

		internal static HANDLER? FindHandler<HANDLER>() where HANDLER : IInputHandler => (HANDLER?) handlers.FirstOrDefault(_handler => _handler?.GetType() == typeof(HANDLER));
		
		internal static void Load(Config<InputConfigData> _config)
		{
			CreateInstance();
			EventBus.RegisterObject(Instance!);
			
			foreach(KeyValuePair<HandlerType, Type> id in moduleIDs.Where(_id => _config.GetValue<bool>($"handlers.{_id.Key.ToString().ToLower()}")))
				handlers.Add(Activator.CreateInstance(id.Value, directInput) as IInputHandler);
			
			string json = File.ReadAllText(Path);
			
			actions = JsonConvert.DeserializeObject<Dictionary<string, InputAction>>(json)!;
		}

		internal static void Poll()
		{
			foreach(IInputHandler? handler in handlers)
				handler?.Poll();

			foreach(InputAction? action in actions.Values)
				action?.Poll();
		}

		internal static void Unload()
		{
			actions.Clear();
			
			handlers.Clear();
			
			EventBus.RemoveObject(Instance!);
			DestroyInstance();
		}

		[SubscribeEvent]
		private void OnConfigReload(ConfigReloadEvent _event)
		{
			string json = File.ReadAllText(Path);
			
			Dictionary<string, InputAction> newActions = JsonConvert.DeserializeObject<Dictionary<string, InputAction>>(json)!;

			foreach(KeyValuePair<string,InputAction> pair in newActions)
			{
				if(actions.TryGetValue(pair.Key, out InputAction? action) && action != null)
				{
					action.mappings = pair.Value.mappings;
					action.Type = pair.Value.Type;
					action.ActiveHandlerType = pair.Value.ActiveHandlerType;
				}
			}
		}
	}
}