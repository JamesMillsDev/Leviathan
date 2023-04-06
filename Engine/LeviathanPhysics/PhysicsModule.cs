using Leviathan.Events;

namespace Leviathan.Physics
{
	internal class PhysicsModule : ILeviathanModule, IEventHandler
	{
		private readonly PhysicsScene scene = new();

		public void Load() => scene.Load();

		public void OnDrawGizmos() => scene.OnDrawGizmos();

		public void Unload() => scene.Unload();
	}
}