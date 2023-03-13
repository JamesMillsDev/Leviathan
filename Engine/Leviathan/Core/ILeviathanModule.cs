namespace Leviathan
{
	internal interface ILeviathanModule
	{
		public void Load();
		public void Render();
		public void Tick();
		public void Unload();
	}
}