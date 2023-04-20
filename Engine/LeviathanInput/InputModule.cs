using Leviathan.Configuration;

namespace Leviathan.InputSystem
{
	internal class InputModule : ILeviathanModule
	{
		internal static Config<InputConfigData>? config;

		public void Load()
		{
			config = new Config<InputConfigData>("input");
			Input.Load(config);
		}

		public void Tick() => Input.Poll();

		public void Unload() { }
	}
}