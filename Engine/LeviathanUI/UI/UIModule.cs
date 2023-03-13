namespace Leviathan.UI
{
	// ReSharper disable once InconsistentNaming
	public class UIModule : ILeviathanModule
	{
		public void Load() => UIManager.CreateInstance();

		public void Render() => UIManager.Render();

		public void Tick() => UIManager.Tick();

		public void Unload() => UIManager.DestroyInstance();
	}
}