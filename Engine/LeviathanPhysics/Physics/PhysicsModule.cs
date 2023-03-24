namespace Leviathan.Physics
{
	internal class PhysicsModule : ILeviathanModule
	{
		private PhysicsTree? container;

		public void Load()
		{
			if(Application.Window == null)
				return;
			
			container = new PhysicsTree(Application.Window.ScreenBounds);
		}

		public void Render() { }

		public void Tick() { }

		public void Unload()
		{
			container = null;
		}
	}
}