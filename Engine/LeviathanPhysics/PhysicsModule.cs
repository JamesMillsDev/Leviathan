using Leviathan.Events;
using Leviathan.Physics.Components;

namespace Leviathan.Physics
{
	internal class PhysicsModule : ILeviathanModule, IEventHandler
	{
		private PhysicsGraph? container;

		public void Load()
		{
			if(Application.Window == null)
				return;
			
			EventBus.RegisterObject(this);

			container = new PhysicsGraph(Application.Window.ScreenBounds);
		}

		public void OnDrawGizmos()
		{
			container?.Visualise();
		}

		public void Unload()
		{
			EventBus.RemoveObject(this);
			
			container = null;
		}

		[SubscribeEvent]
		// ReSharper disable once UnusedMember.Local
		private void OnObjectSpawned(GameObjectSpawnedEvent _event)
		{
			if(_event.gameObject == null)
				return;
			
			if(_event.gameObject.TryGetComponent(out Collider? collider) && collider != null)
				collider.data = container?.Insert(new PhysicsTreeData(collider, _event.gameObject.Bounds));
		}

		[SubscribeEvent]
		// ReSharper disable once UnusedMember.Local
		private void OnObjectDestroyed(GameObjectDestroyedEvent _event)
		{
			if(_event.gameObject == null)
				return;
			
			if(_event.gameObject.TryGetComponent(out Collider? collider) && collider is { data: { } })
				container?.Remove(collider.data);
		}
	}
}