using Leviathan.Debugging;

using Newtonsoft.Json;

namespace Leviathan.Input.Obsolete
{
	[Obsolete("Rebuilding in favour of new SharpX version")]
	public class InputSystem : Singleton<InputSystem>
	{
		private static readonly Logger logger = new Logger("InputSystem");

		internal static void Tick()
		{
			if(Instance == null)
			{
				logger.LogException(new NullReferenceException("Not yet initialised!"));
				return;
			}

			foreach(InputAction action in Instance.actions.Values)
				action.Tick();
		}

		public static InputAction? Find(string _id)
		{
			if(Instance == null)
			{
				logger.LogException(new NullReferenceException("Not yet initialised!"));
				return null;
			}

			return Instance.actions.TryGetValue(_id, out InputAction? action) ? action : null;
		}

		private Dictionary<string, InputAction> actions = new();

		protected override void OnCreate()
		{
			string path = $"{Directory.GetCurrentDirectory()}\\assets\\InputActions.json";
			string json = File.ReadAllText(path);
			
			actions = JsonConvert.DeserializeObject<Dictionary<string, InputAction>>(json)!;
		}
	}
}