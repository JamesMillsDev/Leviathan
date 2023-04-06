using Leviathan.Events;
using Leviathan.Physics.Components;
using Leviathan.Physics.Structures.Graphs;

namespace Leviathan.Physics
{
	public class PhysicsScene : IEventHandler
	{
		private PhysicsGraph container = null!;

		public void Load()
		{
			if(Application.Window is not { })
				return;

			EventBus.RegisterObject(this);

			// ReSharper disable once InconsistentlySynchronizedField
			container = new PhysicsGraph(Application.Window.ScreenBounds);

			lock(container)
			{
				new Thread(() => PhysicsThread.WorkerFunction(container)).Start();
			}
		}

		public void OnDrawGizmos()
		{
			lock(container)
			{
				container.Visualise();
			}
		}

		public void Unload()
		{
			EventBus.RemoveObject(this);
		}

		[SubscribeEvent]
		// ReSharper disable once UnusedMember.Local
		private void OnObjectSpawned(GameObjectSpawnedEvent _event)
		{
			if(_event.gameObject == null)
				return;

			lock(container)
			{
				foreach(Collider? collider in _event.gameObject.GetComponents<Collider>())
				{
					if(collider is { })
						collider.data = container?.Insert(new PhysicsTreeData(collider, _event.gameObject.Bounds));
				}
			}
		}

		[SubscribeEvent]
		// ReSharper disable once UnusedMember.Local
		private void OnObjectDestroyed(GameObjectDestroyedEvent _event)
		{
			if(_event.gameObject == null)
				return;

			lock(container)
			{
				foreach(Collider? collider in _event.gameObject.GetComponents<Collider>())
				{
					if(collider is { data: { } })
						container?.Remove(collider.data);
				}
			}
		}
	}
}